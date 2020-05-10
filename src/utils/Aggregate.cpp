#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <iostream>
#include "Aggregate.h"
#include "common.h"

using namespace std;

Graph::Graph(int v){
    this -> n = v;
    g.resize(v);
}
void Graph::addEdge(int a, int b){
    if (find(g[a].begin(), g[a].end(), b) == g[a].end())
        g[a].push_back(b);
}
vector<int>& Graph::adj(int x){
    return g[x];
}

int Graph::size(){ return n; }

Graph Graph::transpose(){
    Graph t(n);
    for(int i = 0; i < n; i++)
        for (int v : adj(i))
            t.addEdge(v, i);
    
    return t;
}

Graph readAggregate(){
    int l, n, m, a, la, b, lb;
    cin >> l >> n >> m;
    Graph res(n);
     
    while (cin >> a >> la >> b >> lb){
        res.addEdge(a, b);
    }

    return res;
}

vector<int> Graph::in_deg(){
    vector<int> in_deg(size(), 0);
    for(int i = 0; i < size(); i++){
        for(int v : adj(i))
            in_deg[v]++;
    }
    return in_deg;
}

vector<int> Graph::out_deg(){
    vector<int> out_deg(size(), 0);
    for(int i = 0; i < size(); i++){
        out_deg[i] = g[i].size();
    }
    return out_deg;
}

vector<double> Graph::multiply_as_adj_matrix(vector<double> &x){
    vector<double> res(size(), 0);
    for(int i = 0; i < size(); i++) {
        for(int v : adj(i)) {
            res[i] += x[v];
        }
    }
    return res;
}

/**
 * Computes the eigenvector of the adjacency matrix associated to the 
 * maximum eigenvalue through the power iteration method.
 */
vector<double> Graph::eigenvector(int max_iter){
    vector<double> x(size(), 1.0L/double(size()));
    vector<double> xlast(size());
    double s = 1.0L;
    bool found = false;

    for(int j = 0; j < max_iter && !found; j++) {
        xlast = x;
        x = multiply_as_adj_matrix(xlast);
        normalize(x);
        found = almost_eq(x, xlast);
    }
    return x;
}

/**
 * Return the maximum eigenvalue of the adjacency matrix associated to
 * the adjacency matrix of the graph
 */
double Graph::eigenvalue(){
    vector<double> e = eigenvector();
    vector<double> x = multiply_as_adj_matrix(e);
    vector<double> r (e.size());
    for(int i = 0; i < e.size(); i++){
        if(almost_eq(e[i], 0.0L)) {
            r[i] = 0.0L;
        } else {
            r[i] = x[i] / e[i];
        }
    }
    return *max_element(r.begin(), r.end());
}