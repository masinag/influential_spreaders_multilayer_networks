#include <queue>
#include <random>
#include <iostream>
#include <cassert>
#include "../utils/Multilayer.h"
#include "../utils/Aggregate.h"

#define PROCESSES 1
#define S 0
#define I 1
#define R 2

using namespace std;

uniform_real_distribution<double> random_double(0, 1);
default_random_engine re;

// lamda = avg(deg_i) / avg(deg_i^2)
double getEpidemicThreshold(Graph &g){
    // calculate in_degree of each node
    vector<int> in_deg(g.size(), 0);
    for (int i = 0; i < g.size(); i++){
        for(int v : g.adj(i))
            in_deg[v]++;
    }
    int sum_deg = 0, sum_sq_deg = 0;
    for(int d : in_deg) {
        sum_deg += d;
        sum_sq_deg += d*d;
    }
    return (double(sum_deg) / double(g.size()))  / 
           (double(sum_sq_deg) / double(g.size()));
}

// around epidemic threshold of each layer
vector<double> getIntraLayerEP(MultilayerNetwork &g){
    
}
double spread(Graph &g, int node, double lambda){
    vector<int> status(g.size(), S);
    int infected_number = 0;
    queue<int> infected;
    infected.push(node);
    status[node] = I;
    while(!infected.empty()){
        // pick a node and spread the infection to its neighbors in all layers 
        int e = infected.front();
        infected.pop();
        status[e] = R;
        infected_number++;
        for(int v : g.adj(e)){
            if(status[v] == S){
                double inf_prob = random_double(re);
                if (inf_prob <= lambda) {
                    status[v] = I;
                    infected.push(v);
                }
            }
        }
        
    }
    // cout << infected_number << endl;
    return double(infected_number) / double(g.size());
}

double avg_spread(Graph &g, double lambda){
    double sum = 0, m = 0;
    for(int i = 0; i < g.size(); i++){
        double s = spread(g, i, lambda);
        sum += s;
        m = max(m, s);
    }
    return sum / g.size();
    // return m;
}

// around epidemic threshold of aggregated network
double getInterLayerEP(MultilayerNetwork &g){
    Graph agg = g.getAggregate();
    
    double lambda = getEpidemicThreshold(agg);
    cout << lambda << endl;   
    cout << "lambda: " << avg_spread(agg, lambda) << endl;
    cout << "lambda+0.1: " << avg_spread(agg, lambda+0.1) << endl;
    cout << "lambda+0.2: " << avg_spread(agg, lambda+0.2) << endl;
    cout << "lambda+0.3: " << avg_spread(agg, lambda+0.3) << endl;
    cout << "lambda+0.3: " << avg_spread(agg, lambda+0.3) << endl;
    cout << "lambda+0.4: " << avg_spread(agg, lambda+0.4) << endl;
    cout << "lambda+0.5: " << avg_spread(agg, lambda+0.5) << endl;
    cout << "lambda+0.6: " << avg_spread(agg, lambda+0.6) << endl;
    cout << "lambda+0.7: " << avg_spread(agg, lambda+0.7) << endl;
    cout << "lambda+0.8: " << avg_spread(agg, lambda+0.8) << endl;
    cout << "lambda+0.9: " << avg_spread(agg, lambda+0.9) << endl;
    cout << "lambda+1: " << avg_spread(agg, lambda+1) << endl;

}

// Returns the percentage of nodes infected by a spreading process (SIR) starting
// from the given node.
// The diffusion process ends when there are no nodes left in the I state.
// Hence, influence is measured by the number of nodes in the
// R state at the end of a diffusion process.
double spreading_process(MultilayerNetwork &g, vector<double> &intra_layer_ep, 
    double inter_layer_ep, int node){
    vector<int> status(g.nodes(), S);
    int infected_number = 0;
    queue<int> infected;
    infected.push(node);
    status[node] = I;
    while(!infected.empty()){
        // pick a node and spread the infection to its neighbors in all layers 
        int e = infected.front();
        infected.pop();
        status[e] = R;
        infected_number++;
        assert(infected_number <= g.nodes());
        for (int l = 0; l < g.layers(); l++){
            for(Edge v : g.adj(e, l)){
                if(status[v.node] == S){
                    double inf_prob = random_double(re);
                    if ((v.layer == l && inf_prob <= intra_layer_ep[l]) || // intra-layer link
                        (v.layer != l && inf_prob <= inter_layer_ep)){ // inter-layer link
                        status[v.node] = I;
                        infected.push(v.node);
                    }
                }
            }
        }
    }
    return double(infected_number) / double(g.nodes());
}

vector<double> spreading_processesSIR(MultilayerNetwork &g, vector<double> &intra_layer_ep, 
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
    printf("Reading multiplex\n");
    MultilayerNetwork g = readMultilayer();
    printf("Multiplex read\n");
    // vector<double> intra_layer_ep = getIntraLayerEP(g);
    double inter_layer_ep = getInterLayerEP(g);
    //vector<double> sp = spreading_processesSIR(g, intra_layer_ep, inter_layer_ep, PROCESSES);
    return 0;
}
