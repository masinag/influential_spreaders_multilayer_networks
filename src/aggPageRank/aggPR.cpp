#include <cmath>
#include "aggPR.h"

using namespace std;

double difference(vector<double> &v, vector<double> &w){
    double res = 0;
    for (int i = 0; i < v.size(); i++)
        res += v[i] - w[i];
    return abs(res);
}
/**
 * PageRank original paper: http://ilpubs.stanford.edu:8090/422/1/1999-66.pdf
 * the number of iterations is proportional to log(n)
 */
vector<double> pageRank(Graph &out_edges, double alpha){
    vector<double> rank(out_edges.size(), 1.0L/out_edges.size());
    Graph in_edges = out_edges.transpose();
    bool done = false;

    while (!done) {
        vector<double> new_rank(out_edges.size(), (1.0L - alpha)/out_edges.size());
        for(int i = 0; i < out_edges.size(); i++){
            for(int v : in_edges.adj(i)) {
                new_rank[i] += rank[v]/out_edges.adj(v).size();
            }
        }
        rank = new_rank;
        done = difference(rank, new_rank) < DIFF_EPSILON;
    }
    
    return rank;
    
}


