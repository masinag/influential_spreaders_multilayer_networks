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
    MultilayerNetwork res(l, n);
    while (cin >> a >> la >> b >> lb){
        res.addEdge(a, la, b, lb);
    }
    return res;
}

MultilayerNetwork::MultilayerNetwork(int l, int n){
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

vector<Graph> MultilayerNetwork::to_vector(){
    vector<Graph> res(layers(), Graph(nodes()));
    for(int l = 0; l < layers(); l++){ 
        for(int n = 0; n < nodes(); n++) {
            for (Edge e : g[n][l]){
                if(e.layer == l)
                    res[l].addEdge(n, e.node);
            }
        }
    }
    return res;
}

vector<vector<int>> MultilayerNetwork::in_degree(){
    vector<vector<int>> deg(nodes(), vector<int>(layers(), 0));
    for(int i = 0; i < nodes(); i++){
        for(int l = 0; l < layers(); l++){
            for(Edge &e : g[i][l]) {
                deg[e.node][e.layer]++;
            }
        }
    }
    return deg;
}


void MultilayerNetwork::transpose(MultilayerNetwork &gt){
    for(int i = 0; i < nodes(); i++) {
        for(int l = 0; l < layers(); l++) {
            for(Edge &e : g[i][l]){
                gt.addEdge(e.node, e.layer, i, l);}
        }
    }
}