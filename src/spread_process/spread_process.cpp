#include <queue>
#include <random>
#include <iostream>
#include <cassert>
#include "../utils/Multilayer.h"
#include "../utils/Graph.h"
#include "../utils/common.h"

#define PROCESSES 1
#define S 0
#define I 1
#define R 2

using namespace std;

uniform_real_distribution<double> random_double(0, 1);
default_random_engine re;

// lamda = avg(deg_i) / avg(deg_i^2)
double get_epidemic_threshold(Graph &g){
    // calculate in_degree of each node
    vector<int> in_deg = g.in_deg();
    int sum_deg = 0, sum_sq_deg = 0;
    for(int d : in_deg) {
        sum_deg += d;
        sum_sq_deg += d*(d-1);
    }
    return (double(sum_deg) / double(g.size()))  / 
           (double(sum_sq_deg) / double(g.size()));
}

// around epidemic threshold of each layer
vector<double> get_intra_layer_ep(MultilayerNetwork &g){
    vector<Graph> layers = g.to_vector();
    vector<double> intra_layer_ep(g.layers(), 0);
    // cout << "intra-layer: ";
    for(int i = 0; i < g.layers(); i++){
        intra_layer_ep[i] = get_epidemic_threshold(layers[i]) + 0.0L;
        // cout << "[" << i << "] : " << intra_layer_ep[i] << " ";
    }
    // cout << endl;
    
    return intra_layer_ep;
}


// around epidemic threshold of aggregated network
double get_inter_layer_ep(MultilayerNetwork &g){
    Graph agg = g.getAggregate();
    double lambda = get_epidemic_threshold(agg) + 0.0L;
    // cout << "inter-layer: " << lambda << endl;
    return lambda;

}

// Returns the percentage of nodes infected by a spreading process (SIR) starting
// from the given node.
// The diffusion process ends when there are no nodes left in the I state.
// Hence, influence is measured by the number of nodes in the
// R state at the end of a diffusion process.
double spreading_process(MultilayerNetwork &g, vector<double> &intra_layer_ep, 
    double inter_layer_ep, int node){
    vector<vector<int>> status(g.nodes(), vector<int>(g.layers(), S));
    queue<pair<int, int>> infected;
    for(int l : g.layers(node)){
        infected.push(make_pair(node, l));
        status[node][l] = I;
    }
    int recovered_number = g.layers();
    while(!infected.empty()){
        // pick a node and spread the infection to its neighbors in all layers 
        int node = infected.front().first;
        int layer = infected.front().second;
        infected.pop();
        status[node][layer] = R;
        recovered_number++;
        for(Edge v : g.adj(node, layer)){
            if(status[v.node][v.layer] == S){
                double inf_prob = random_double(re);
                if ((v.layer == layer && inf_prob <= intra_layer_ep[layer]) || // intra-layer link
                    (v.layer != layer && inf_prob <= inter_layer_ep)){ // inter-layer link
                    status[v.node][v.layer] = I;
                    infected.push(make_pair(v.node, v.layer));
                }
            }
        }
        
    }
    return double(recovered_number) / double(g.nodes() * g.layers());
}

vector<double> spreading_processes_SIR(MultilayerNetwork &g, vector<double> &intra_layer_ep, 
    double inter_layer_ep, int processes){
    vector<double> infected_percentage(g.nodes(), 0);
    // average of #processes infectious processes
    for(int p = 0; p < processes; p++){
        for(int n = 0; n < g.nodes(); n++){
            infected_percentage[n] += spreading_process(g, intra_layer_ep, inter_layer_ep, n);
        }
    }
    for(int i = 0; i < g.nodes(); i++)
        infected_percentage[i] /= processes;
    return infected_percentage;
}

int main(int argc, char const *argv[]){
    if(argc < 2) {
        cerr << "File name not found" << endl;
        exit(EXIT_FAILURE);
    }
    string file = argv[1];
    MultilayerNetwork g = readMultilayer(file);
    vector<double> intra_layer_ep = get_intra_layer_ep(g);
    double inter_layer_ep = get_inter_layer_ep(g);
    vector<double> sp = spreading_processes_SIR(g, intra_layer_ep, inter_layer_ep, PROCESSES);
    vector<int> sorted = sort_nodes(sp);
    for(int i : sorted){
        cout << i << " score: " << sp[i] << endl; 
    }
    return 0;
}
