#include <fstream>
#include <iostream>
#include <unordered_map>
#include "Multilayer.h"

#define MAX_LAYERS 100

using namespace std;

Node::Node(int n, int l){
    node = n;
    layer = l;
}

bool Node::operator==(const Node &n) const {
    return this->node * MAX_LAYERS + this->layer == n.node * MAX_LAYERS + n.layer;
}

size_t NodeHash::operator()(const Node &t) const {
    return t.node * MAX_LAYERS + t.layer;
}

MultilayerNetwork readMultilayer(string &file){
    int l, n, m, a, la, b, lb;
    ifstream in(file);
    in >> l >> n >> m;
    MultilayerNetwork res(l, n);
    while (in >> a >> la >> b >> lb){
        res.addEdge(a, la, b, lb);
    }
    return res;
}

MultilayerNetwork::MultilayerNetwork(int l, int n){
    this -> n = n;
    this -> l = l;
    this -> g.resize(n, vector< vector < Node > > (l));
    node_layers.resize(n);
    layer_nodes.resize(l);
    //g.resize(n, vector<vector<vector<int>>>(l, vector<vector<int>>(n, vector<int>(l, 0))));
    // might need to add links between same nodes in different layers
}

int MultilayerNetwork::nodes(){
    return n;
}
unordered_set<int>& MultilayerNetwork::nodes(int layer){
    return layer_nodes[layer];
}

int MultilayerNetwork::layers(){
    return l;
}
unordered_set<int>& MultilayerNetwork::layers(int node){
    return node_layers[node];
}

int MultilayerNetwork::total_nodes(){
    int tot = 0;
    for(int l = 0; l < layers(); l++)
        tot += nodes(l).size();
    return tot;
}


vector<Node>& MultilayerNetwork::adj(int n, int l){
    return g[n][l];
}


void MultilayerNetwork::addEdge(int a, int la, int b, int lb){
    g[a][la].push_back(Node(b, lb));
    node_layers[a].insert(la);
    node_layers[b].insert(lb);
    layer_nodes[la].insert(a);
    layer_nodes[lb].insert(b);
}


Graph MultilayerNetwork::getAggregate(){
    Graph res(this->n);
    for(int n = 0; n < nodes(); n++){
        for(int l : layers(n)){
            for(Node e : g[n][l]) {
                res.addEdge(n, e.node);
            }
        }
    }
    return res;
}

vector<Graph> MultilayerNetwork::to_vector(){
    vector<Graph> res(layers());
    for(int l = 0; l < layers(); l++){
        res[l] = Graph(nodes(l).size());
        // map each node of the layer with an id
        int i = 0;
        unordered_map<int, int> id_map;
        for(int n : nodes(l)){
            id_map[n] = i;
            res[l].node_name[i] = n;
            i++;
        }
        // add the edges using the ids
        for(int n : nodes(l)) {
            for (Node e : g[n][l]){
                if(e.layer == l)
                    res[l].addEdge(id_map[n], id_map[e.node]);
            }
        }
    }
    return res;
}

vector<vector<int>> MultilayerNetwork::in_degree(){
    vector<vector<int>> deg(nodes(), vector<int> (layers(), 0));
   
    for(int i = 0; i < nodes(); i++){
        for(int l : layers(i)){
            for(Node &e : g[i][l]) {
                deg[e.node][e.layer]++;
            }
        }
    }
    return deg;
}
vector<vector<int>> MultilayerNetwork::out_degree(){
    vector<vector<int>> deg(nodes(), vector<int>(layers(), 0));
    for(int i = 0; i < nodes(); i++){
        for(int l : layers(i)){
            deg[i][l] = adj(i, l).size();
        }
    }
    return deg;
}


void MultilayerNetwork::transpose(MultilayerNetwork &gt){
    for(int i = 0; i < nodes(); i++) {
        for(int l : layers(i)) {
            for(Node &e : g[i][l]){
                gt.addEdge(e.node, e.layer, i, l);}
        }
    }
}

