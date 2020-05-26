#include <cstdio>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <cmath>
#include "addPR.h"
#include "../aggPageRank/aggPR.h"
#include "../utils/common.h"

vector<double> layerPageRank(Graph &out_edges, vector<double> bias, double alpha, 
    double beta, double gamma, int max_iter){

    vector<double> rank(bias.size(), 1.0L/bias.size());
    Graph in_edges(out_edges.size());
    out_edges.transpose(in_edges);
    vector<double> pows(bias.size());             // bias[i]^gamma
    vector<double> out_biases(bias.size(), 0.0L); // sum of biases of nodes reachable from i
    // cout << "instatn" << endl;
    double sum = 0; // sum of bias vector
    // fill vectors
    for(int i = 0; i < bias.size(); i++){
        // cout << i << endl;
        pows[i] = pow(bias[i], gamma);
        sum += pows[i];
    }
    for(int i = 0; i < out_edges.size(); i++){
        for(int j : out_edges.adj(i)){
            int id_i = out_edges.node_name[i];
            int id_j = out_edges.node_name[j];
            out_biases[id_i] += pow(bias[id_j], beta);
        }
    }

    // iteratively compute pageRank
    bool done = false;
    int j;
    // x_i / (N * avg(x_j)) = (x_i^y / sum(x_j^y))
    for (j = 0; j < max_iter && !done; j++) {
        // initialize new_rank
        vector<double> new_rank(bias.size(), (1.0L - alpha) / sum);
        for(int i = 0; i < bias.size(); i++)
            new_rank[i] *= pows[i];

        // compute PR of a node based on links towards it
        for(int i = 0; i < out_edges.size(); i++){
            for(int v : in_edges.adj(i)) {
                int id_i = out_edges.node_name[i];
                int id_v = out_edges.node_name[v];
            // for(int v : out_edges.adj(i)) {
                new_rank[id_i] += alpha * pow(bias[id_i], beta) * rank[id_v] / out_biases[id_v];
                // new_rank[i] += alpha * pow(bias[i], beta) * rank[v] / out_biases[i];
            }
        }
        // stochasticize(new_rank);
        done = almost_eq(rank, new_rank);
        rank = new_rank;
    }
    printf("%d iterations\n", j);
    return rank;

}

/**
 * Implementation of doi:10.1371/journal.pone.0078293
 */
vector<double> multiplexPageRank(MultilayerNetwork &m, double alpha, double beta, double gamma) {
    vector<double> x(m.nodes(), 1.0L);
    vector<Graph> ll = m.to_vector();           // layers of the network
    vector<double> eigenvalues(m.layers());     // eigenvalues of layer_i
    vector<int> indexes(ll.size());             // indexes of layers

    for(int i = 0; i < ll.size(); i++){
        indexes[i] = i;
        eigenvalues[i] = ll[i].eigenvalue();
        // cout << "eigenvalue " << i << ": " << eigenvalues[i];
    }
    // sort indexes by decreasing eigenvalue
    sort(indexes.begin(), indexes.end(), [eigenvalues](int i, int j){
        return eigenvalues[i] > eigenvalues[j];
    });
    
    for(int i : indexes) {
        x = layerPageRank(ll[i], x, alpha, beta, gamma);
        // stochasticize(x);
    }
    return x;
}

vector<double> additivePageRank(MultilayerNetwork &m, double alpha) {
    return multiplexPageRank(m, alpha, 0.0L, 1.0L);
}