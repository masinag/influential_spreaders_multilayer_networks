#include <algorithm>
#include <iostream>
#include <cassert>
#include "laPCI.h"

// Definition in doi: 10.1109/TNSE.2017.2775152
// The laPCI of a node v is the maximum number k, such that there are
// at least k direct neighbors of v with the number of links greater than 
// or equal to k.
vector<int> laPCI(MultilayerNetwork &m){
    // compute the number of out-links of each node
    vector<vector<int>> count = m.out_degree();
    
    vector<int> score(m.nodes(), 0);
    // for each node in each layer
    for(int i = 0; i < m.nodes(); i++) {
        for(int l : m.layers(i)) {
            vector<int> v(m.adj(i, l).size(), 0);
            int index = 0;
            for(Node &e : m.adj(i, l)){
                // if (e.node != i)
                    v[index] = count[e.node][e.layer];
                // else
                //     v[index] = 0;
                index++;
            }
            //sort them in increasing order
            sort(v.begin(), v.end(), greater<int>());

            // k = max_j(min(j+1, v[j])) represents the maximum number
            // k for which at least k neighbors have at least k out-links
            int k = 0;
            for(int j = 0; j < v.size(); j++)
                k = max(k, min(j+1, v[j]));
            score[i] += k;
        }
    }
    return score;
}