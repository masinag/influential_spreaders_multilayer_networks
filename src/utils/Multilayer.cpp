#include <vector>
#include <iostream>
#include "Multilayer.h"

using namespace std;

Edge::Edge(int n, int l){
    node = n;
    layer = l;
}

MultilayerNetwork readMultilayer(){
    int l, n, m, a, la, b, lb;
    cin >> l >> n >> m;
    MultilayerNetwork res(l, n, m);
    while (cin >> a >> la >> b >> lb){
        res.addEdge(a, la, b, lb);
    }
    return res;
}

MultilayerNetwork::MultilayerNetwork(int l, int n, int m){
    this -> n = n;
    this -> l = l;
    this -> g.resize(n, vector< vector < Edge > > (l));
    //g.resize(n, vector<vector<vector<int>>>(l, vector<vector<int>>(n, vector<int>(l, 0))));
    // might need to add links between same nodes in different layers
}

int MultilayerNetwork::nodes(){
    return n;
}

int MultilayerNetwork::layers(){
    return l;
}

vector<Edge> MultilayerNetwork::adj(int n, int l){
    return g[n][l];
}


void MultilayerNetwork::addEdge(int a, int la, int b, int lb){
    g[a][la].push_back(Edge(b, lb));
}


Graph MultilayerNetwork::getAggregate(){
    Graph res(this->n);
    for(int n = 0; n < nodes(); n++){
        for(int l = 0; l < layers(); l++){
            for(Edge e : g[n][l]) {
                res.addEdge(n, e.node);
            }
        }
    }
    return res;
}