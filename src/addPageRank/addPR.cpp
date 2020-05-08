#include <algorithm>
#include <cmath>
#include "addPR.h"
#include "../aggPageRank/aggPR.h"

vector<double> layerPageRank(Graph &out_edges, vector<double> bias, double alpha, 
    double beta, double gamma){

    vector<double> rank(out_edges.size(), 1.0L/out_edges.size());
    Graph in_edges = out_edges.transpose();
    vector<double> pows(out_edges.size());             // bias[i]^gamma
    vector<double> out_biases(out_edges.size(), 0.0L); // sum of biases of nodes reachable from i
    double sum = 0; // sum of bias vector
    // fill vectors
    for(int i = 0; i < bias.size(); i++){
        pows[i] = pow(bias[i], gamma);
        sum += pows[i];
        for(int j : out_edges.adj(i))
            out_biases[i] += bias[j];
    }

    // iteratively compute pageRank
    bool done = false;
    while (!done) {
        vector<double> new_rank(out_edges.size(), (1.0L - alpha) / out_edges.size());
        for(int i = 0; i < out_edges.size(); i++){
            new_rank[i] *= pows[i];
            for(int v : in_edges.adj(i)) {
                new_rank[i] += pow(bias[i], beta) * rank[v] / out_biases[v];
            }
        }
        rank = new_rank;
        done = difference(rank, new_rank) < DIFF_EPSILON;
    }
    
    return rank;

}

/**
 * Implementation of doi:10.1371/journal.pone.0078293
 */
vector<double> multiplexPageRank(MultilayerNetwork &m, double alpha, double beta, double gamma) {
    vector<double> x(m.nodes());
    vector<Graph> ll = m.to_vector();           // layers of the network
    vector<double> eigenvalues(m.layers());     // eigenvalues of layer_i
    vector<int> indexes(ll.size());             // indexes of layers

    for(int i = 0; i < ll.size(); i++){
        indexes[i] = i;
        eigenvalues[i] = ll[i].eigenvalue();
    }
    // sort indexes by decreasing eigenvalue
    sort(indexes.begin(), indexes.end(), [eigenvalues](int i, int j){
        return eigenvalues[i] > eigenvalues[j];
    });
    x.assign(x.size(), 1);
    for(int i : indexes) {
        x = layerPageRank(ll[i], x, alpha, beta, gamma);
    }
    return x;
}

vector<double> additivePageRank(MultilayerNetwork &m, double alpha) {
    return multiplexPageRank(m, alpha, 0.0L, 1.0L);
}