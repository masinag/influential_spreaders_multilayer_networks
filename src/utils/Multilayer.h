#ifndef MULTILAYER_H
#define MULTILAYER_H
#include <vector>
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
        int l, n, m;
        MultilayerNetwork(int l, int n, int m);
        void addEdge(int a, int la, int b, int lb);
        void addNode(int n, int l);
        vector<Edge> adj(int n, int l);
        int nodes();
        int layers();
        

        Graph getAggregate();
};

MultilayerNetwork readMultilayer();

#endif