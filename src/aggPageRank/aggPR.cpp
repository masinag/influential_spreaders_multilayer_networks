#include <cmath>
#include <cstdio>
#include "aggPR.h"
#include "../utils/common.h"

using namespace std;

/**
 * PageRank original paper: http://ilpubs.stanford.edu:8090/422/1/1999-66.pdf
 * the number of iterations is proportional to log(n)
 */
vector<double> pageRank(Graph &out_edges, double alpha, int max_iter){
    vector<double> rank(out_edges.size(), 1.0L/out_edges.size());
    Graph in_edges(out_edges.size());
    out_edges.transpose(in_edges);
    bool done = false;
    int j;

    for(j = 0; j < max_iter && !done; j++) {
        vector<double> new_rank(out_edges.size(), (1.0L - alpha)/out_edges.size());
        for(int i = 0; i < out_edges.size(); i++){
            for(int v : in_edges.adj(i)) {
            // for(int v : out_edges.adj(i)) {
                new_rank[i] += alpha * rank[v] / out_edges.adj(v).size();
                // new_rank[i] += alpha * rank[v]/out_edges.adj(i).size();
            }
        }
        // stochasticize(new_rank);
        done = almost_eq(rank, new_rank);
        rank = new_rank;
    }
    // printf("%d iterations\n", j);
    return rank;
    
}


