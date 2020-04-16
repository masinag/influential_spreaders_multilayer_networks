#include <vector>
#include <iostream>
#include "Multilayer.h"

using namespace std;

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
    //g.resize(n, vector<vector<vector<int>>>(l, vector<vector<int>>(n, vector<int>(l, 0))));
    // might need to add links between same nodes in different layers
}

void MultilayerNetwork::addEdge(int a, int la, int b, int lb){
    g[a][la][b][lb] = 1;
}