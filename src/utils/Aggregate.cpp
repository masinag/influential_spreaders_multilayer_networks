#include <vector>
#include <algorithm>
#include <iostream>
#include "Aggregate.h"

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