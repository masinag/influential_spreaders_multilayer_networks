#include <queue>
#include <random>
#include <iostream>
#include <cassert>
#include "../utils/Multilayer.h"
#include "../utils/Graph.h"
#include "../utils/common.h"
#include "io.h"

#define S 0
#define I 1
#define R 2

using namespace std;


uniform_real_distribution<double> random_double(0, 1);
random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

// lambda = avg(deg_i) / avg(deg_i^2)
double get_epidemic_threshold(Graph &g){
    // calculate in_degree of each node
    vector<int> in_deg = g.in_deg();
    int sum_deg = 0, sum_sq_deg = 0;
    for(int d : in_deg) {
        sum_deg += d;
        sum_sq_deg += d*d;
    }
    return (double(sum_deg))  / 
           (double(sum_sq_deg));
}

// around epidemic threshold of each layer
vector<double> get_intra_layer_ep(MultilayerNetwork &g){
    vector<Graph> layers = g.to_vector();
    vector<double> intra_layer_ep(g.layers(), 0);
    // cout << "intra-layer: ";
    for(int i = 0; i < g.layers(); i++){
        intra_layer_ep[i] = get_epidemic_threshold(layers[i]);
        // cout << "[" << i << "] : " << intra_layer_ep[i] << " ";
    }
    // cout << endl;
    
    return intra_layer_ep;
}


// around epidemic threshold of aggregated network
double get_inter_layer_ep(MultilayerNetwork &g){
    Graph agg = g.getAggregate();
    double lambda = get_epidemic_threshold(agg);
    // cout << "inter-layer: " << lambda << endl;
    return lambda;

}

// Returns the percentage of nodes infected by a spreading process (SIR) starting
// from the given node.
// The diffusion process ends when there are no nodes left in the I state.
// Hence, influence is measured by the number of nodes in the
// R state at the end of a diffusion process.
int spreading_process(MultilayerNetwork &g, vector<double> &intra_layer_ep, 
    double inter_layer_ep, int node){
    vector<vector<int>> status(g.nodes(), vector<int>(g.layers(), S));
    queue<Node> infected;
    for(int l : g.layers(node)){
        status[node][l] = I;
        infected.push(Node(node, l));
    }
    int recovered_number = 0;
    while(!infected.empty()){
        // pick a node and spread the infection to its neighbors in all layers 
        int node = infected.front().node;
        int layer = infected.front().layer;
        infected.pop();
        status[node][layer] = R;
        recovered_number++;
        for(Node &v : g.adj(node, layer)){
            if(status[v.node][v.layer] == S){
                double inf_prob = random_double(gen);
                if ((v.layer == layer && inf_prob <= intra_layer_ep[layer]) || // intra-layer link
                    (v.layer != layer && inf_prob <= inter_layer_ep)){ // inter-layer link
                    status[v.node][v.layer] = I;
                    infected.push(v);
                }
            }
        }
        
    }
    return recovered_number;
}

vector<int> spreading_processes_SIR(MultilayerNetwork &g, vector<double> &intra_layer_ep, 
    double inter_layer_ep){
    vector<int> infected_number(g.nodes(), 0);
    for(int n = 0; n < g.nodes(); n++){
        infected_number[n] = spreading_process(g, intra_layer_ep, inter_layer_ep, n);
    }
    return infected_number;
}

int main(int argc, char const *argv[]){
    vector<string> files;

    string argv_str(argv[0]);
    string base = argv_str.substr(0, argv_str.find_last_of("/"));
    
    if(argc < 2) {
        int i = 0;
        for (string &dataset: data_dirs){
            string path = base + "/" + dataset;
            read_directory(path, files);
            for(; i < files.size(); i++){
                files[i] = path + files[i]; 
            }
        }
    } else {
        files.push_back (argv[1]);
    }

    vector<int> ns;
    int tmp_n;
    vector<string> ii;
    vector<string> ij;
    string add, tmp_l;
    // cout << "Number of simulations per network: ";
    while((cout << "More sim? [y/n] ") && (cin >> add) && add == "y"){
        cout << "lambda ii: ";
        cin >> tmp_l;
        ii.push_back(tmp_l);
        cout << "lambda ij: ";
        cin >> tmp_l;
        ij.push_back(tmp_l);
        cout << "number of sim for " << ii[ii.size()-1] << "ii" << ij[ij.size() - 1] << "ij" << ": ";
        cin >> tmp_n;
        ns.push_back(tmp_n);
    }
    string log_file = get_log_file(base);
    // unordered_set<string> already_done = {
    //     "SLN_2_0.3_0.3_0.3",
    //     "SLN_2_0.8_0.8_0.8",
    //     "DLN_2_0.8_0.3_0.8",
    //     "DLN_2_0.8_0.8_0.3",
    //     "SLN_2_0.8_0.3_0.3",
    //     "SLN_2_0.3_0.8_0.8",
    //     "DLN_2_0.3_0.8_0.3",
    //     "DLN_2_0.3_0.3_0.8",
    //     "SLN_2_0.3_0.8_0.3",
    //     "SLN_2_0.8_0.3_0.8",
    //     "DLN_2_0.3_0.8_0.8",
    //     "DLN_2_0.8_0.8_0.8"
    // };

    for (string& network_path: files){
        string network_name = get_network_name(network_path);
        // if(already_done.find(network_name) == already_done.end()) continue;
        write_log(log_file, "# " + network_name);

        MultilayerNetwork g = readMultilayer(network_path);
        vector<double> intra_layer_ep = get_intra_layer_ep(g);
        double inter_layer_ep = get_inter_layer_ep(g);
        write_log(log_file, "Network read");
        write_log(log_file, "inter_layer_ep : " +  to_string(inter_layer_ep));
        write_log(log_file, "intra_layer_eps:");
        for(double x : intra_layer_ep) write_log(log_file, to_string(x));
        for(int k = 0; k < ii.size(); k++){
            string lambda_dir = ii[k] + "ii" + ij[k] + "ij";
            write_log(log_file, "> " + lambda_dir);
            vector<double> tmp_intra_layer_ep(intra_layer_ep.size());
            for(int x = 0; x < tmp_intra_layer_ep.size(); x++)
                tmp_intra_layer_ep[x] = intra_layer_ep[x] * stod(ii[k]);
            for(int i = 0; i < ns[k]; i++){
                vector<int> sp = spreading_processes_SIR(g, tmp_intra_layer_ep, inter_layer_ep * stod(ij[k]));
                // vector<double> sp;
                write_simulation_results(g.total_nodes(), sp, base, network_name, lambda_dir, i);
                write_log(log_file, "Simulation " + to_string(i +1) + " out of " + 
                    to_string(ns[k]) + " done");
            }

        }
    }
    return 0;
}
