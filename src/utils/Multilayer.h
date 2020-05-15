#ifndef MULTILAYER_H
#define MULTILAYER_H
#include <vector>
#include <string>
#include "Aggregate.h"

using namespace std;

class Edge{
    public:
        int node, layer;
        Edge(int n, int l);
};

class MultilayerNetwork {
    vector<vector< vector< Edge > > >g;    
    public:
        int l, n;
        MultilayerNetwork(int l, int n);
        void addEdge(int a, int la, int b, int lb);
        void addNode(int n, int l);
        vector<Edge> adj(int n, int l);
        int nodes();
        int layers();
        

        Graph getAggregate();
        vector<Graph> to_vector();
        vector<vector<int>> in_degree();
        vector<vector<int>> out_degree();
        void transpose(MultilayerNetwork &gt);
};

MultilayerNetwork readMultilayer(string &file);

#endif