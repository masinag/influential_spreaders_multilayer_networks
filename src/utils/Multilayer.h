#ifndef MULTILAYER_H
#define MULTILAYER_H
#include <vector>

using namespace std;

class MultilayerNetwork {
    vector<vector<vector<vector<int> > > > g;    
    public:
        int l, n, m;
        MultilayerNetwork(int l, int n, int m);
        void addEdge(int a, int la, int b, int lb);
};

MultilayerNetwork readMultilayer();

#endif