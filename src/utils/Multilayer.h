#ifndef MULTILAYER_H
#define MULTILAYER_H
#include <vector>
#include <string>
#include <unordered_set>
#include "Graph.h"

using namespace std;

class Node{
    public:
        int node, layer;
        Node(int n, int l);
        bool operator==(const Node &n) const;
};

// class for hash function 
class NodeHash { 
    public: 
        size_t operator()(const Node &t) const;
}; 

class MultilayerNetwork {
    vector<vector< vector< Node > > >g;    
    vector<unordered_set<int>> layer_nodes, node_layers;
    public:
        int l, n;
        MultilayerNetwork(int l, int n);
        void addEdge(int a, int la, int b, int lb);
        void addNode(int n, int l);
        vector<Node>& adj(int n, int l);
        int nodes();
        unordered_set<int>& nodes(int layer);
        int layers();
        unordered_set<int>& layers(int node);
        
        int total_nodes();

        Graph getAggregate();
        vector<Graph> to_vector();
        vector<vector<int>> in_degree();
        vector<vector<int>> out_degree();
        void transpose(MultilayerNetwork &gt);
};

MultilayerNetwork readMultilayer(string &file);

#endif