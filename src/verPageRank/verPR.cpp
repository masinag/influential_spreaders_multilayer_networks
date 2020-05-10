#include <cstdio>
#include "verPR.h"
#include "../utils/common.h"

vector<double> verPageRank(MultilayerNetwork& g, double alpha, int max_iter){
    double c = (1.0L - alpha) / (g.nodes() * g.layers());
    vector<vector<double>> rank(g.nodes(), vector<double>(g.layers(), c)), 
        new_rank(g.nodes(), vector<double>(g.layers()));
    
    MultilayerNetwork gt(g.layers(), g.nodes());
    g.transpose(gt);
    bool done = false;
    int j;
    for(j = 0; j < max_iter && !done; j++){
        new_rank.assign(g.nodes(), vector<double>(g.layers(), c));
        for(int i = 0; i < g.nodes(); i++){
            for(int l = 0; l < g.layers(); l++) {
                for(Edge v : gt.adj(i, l)) {
                // for(Edge v : g.adj(i, l)) {
                    new_rank[i][l] += alpha * rank[v.node][v.layer] / g.adj(v.node, v.layer).size();
                    // new_rank[i][l] += alpha * rank[v.node][v.layer] / g.adj(i, l).size();
                }
            }
        }
        done = almost_eq(rank, new_rank);
        rank = new_rank;
    }
    printf("%d iterations\n", j);
    vector<double> agg_rank(g.nodes(), 0.0L);
    for(int i = 0; i < g.nodes(); i++){
        for(int j = 0; j < g.layers(); j++) {
            agg_rank[i] += rank[i][j];
        }
    }
    return agg_rank;
}