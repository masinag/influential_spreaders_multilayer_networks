#include <algorithm>
#include <iostream>
#include <cassert>
#include "mlPCI.h"
// Definition in doi: 10.1109/TNSE.2017.2775152
// The mlPCI n index of a node v is the maximum number k, such that there are
// at least k direct neighbors of v with the number of links towards at least n 
// layers greater than or equal to k.
// To combine the distinct n values of mlPCI n into a single dimension,
// we propose a simple aggregation. In particular, for a node v
// we define mlPCI(v) as follows:
// mlPCI(v) = sum_n(mlPCI_n(v))
vector<int> mlPCI(MultilayerNetwork &m){
    // compute the number of links towards each layer for each node
    vector<vector<vector<int>>> count (m.nodes(), 
        vector< vector <int > > (m.layers(), vector <int > (m.layers(), 0)));

    for(int i = 0; i < m.nodes(); i++) {
        for(int l : m.layers(i)) {
            for(Node &e : m.adj(i, l)) {
                count[i][l][e.layer]++;
            }
            sort(count[i][l].begin(), count[i][l].end(), greater<int>());
        }
    }
    
    vector<int> score(m.nodes(), 0);
    // vector<int> v;
    // for each node in each layer
    for(int i = 0; i < m.nodes(); i++) {
        for(int l : m.layers(i)) {

            vector<int> v(m.adj(i, l).size(), 0);
            // for each n
            for(int n = 0; n < m.layers(); n++){
                // v[k] contains the number of links that the ith neighbor of i,j 
                // called x, y
                // has towards at least n layers, i.e. count[x][y][n-1] contains the 
                // number of links that x, y has towards at least n layers
                int index = 0;
                for(Node &e : m.adj(i, l)){
                    // if(e.node != i)
                        v[index] = count[e.node][e.layer][n];
                    // else
                    //     v[index] = 0;
                    index++;
                }
                //sort them in increasing order
                sort(v.begin(), v.end(), greater<int>());
                
                // k = max_j(min(j+1, v[j])) represents the maximum number
                // k for which at least k neighbors have at least k links
                // towards n layers
                int k = 0;
                for(int j = 0; j < v.size(); j++)
                    k = max(k, min(j+1, v[j]));
                score[i] += k;
            }            
        }
    }
    return score;
}