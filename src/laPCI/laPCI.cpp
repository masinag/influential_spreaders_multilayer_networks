#include <algorithm>
#include <iostream>
#include <cassert>
#include "alPCI.h"

// Definition in doi: 10.1109/TNSE.2017.2775152
// The laPCI of a node v is the maximum number k, such that there are
// at least k direct neighbors of v with the number of links greater than 
// or equal to k.
vector<int> laPCI(MultilayerNetwork &m){
    // compute the number of out-links of each node
    vector<vector<int>> count = m.out_degree();
    
    vector<int> score(m.nodes(), 0);
    vector<int> v;
    // for each node in each layer
    for(int i = 0; i < m.nodes(); i++) {
        for(int l = 0; l < m.layers(); l++) {
            v.resize(m.adj(i, l).size(), 0);
            int index = 0;
            for(Edge &e : m.adj(i, l)){
                v[index] = count[e.node][e.layer];
                index++;
            }
            //sort them in increasing order
            sort(v.begin(), v.end());
            
            // the maximum v[j] for which v[j] >= v.size() - j represents the alPCI of i,l
            // i.e. the maximum number k for which k = (v.size() - j) neighbors of i,l have at least k 
            // out-links
            int j = v.size() - 1;
            while(j >= 0 && v[j] < v.size() - j)
                j--;
            score[i] += j >= 0 ? v[j] : 0;
        }
    }
    return score;
}