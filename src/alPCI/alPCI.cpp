#include <algorithm>
#include <iostream>
#include <cassert>
#include "alPCI.h"

// Definition in doi: 10.1109/TNSE.2017.2775152
// The alPCI of a node v is the maximum number k, such that there are
// at least k direct neighbors of v with the number of links towards 
// all layers greater than or equal to k.
vector<int> alPCI(MultilayerNetwork &m){
    // compute the number of links towards each layer for each node
    vector<vector<vector<pair<int, int>>>> count (m.nodes(), 
        vector< vector <pair<int, int> > > (m.layers(), vector <pair<int, int> > (m.layers())));

    for(int i = 0; i < m.nodes(); i++) {
        for(int l = 0; l < m.layers(); l++) {
            for(int j = 0; j < m.layers(); j++)
                count[i][l][j] = make_pair(j, 0);
            for(Edge &e : m.adj(i, l)) {
                count[i][l][e.layer].second++;
            }
            sort(count[i][l].begin(), count[i][l].end(), [](auto &a, auto &b){
                return a.second > b.second;
            });
        }
    }
    
    vector<int> score(m.nodes(), 0);
    vector<int> v;
    // for each node in each layer
    for(int i = 0; i < m.nodes(); i++) {
        for(int l = 0; l < m.layers(); l++) {
            v.resize(m.adj(i, l).size(), 0);
            int n = m.layers() - 1;
            
            // v[k] contains the number of links that the ith neighbor of i,j 
            // called x, y
            // has towards at least n layers, i.e. count[x][y][n-1] contains the 
            // number of links that x, y has towards at least n layers
            int index = 0;
            for(Edge &e : m.adj(i, l)){
                v[index] = count[e.node][e.layer][n].second;
                index++;
            }
            //sort them in increasing order
            sort(v.begin(), v.end());
            
            // the maximum v[j] for which v[j] >= v.size() - j represents the alPCI_n of i,l
            // i.e. the maximum number k for which k = (v.size() - j) neighbors of i,l have at least k 
            // links towards at least n layers
            int j = v.size() - 1;
            while(j >= 0 && v[j] < v.size() - j)
                j--;
            score[i] += j >= 0 ? v[j] : 0;  
        }
    }
    return score;
}