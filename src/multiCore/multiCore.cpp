#include <queue>
#include <algorithm>
#include "multiCore.h"

typedef pair<int, int> ii;

/**
 * k-core percolation on multiplex networks
 * https://journals.aps.org/pre/pdf/10.1103/PhysRevE.90.032816?casa_token=wMEzie2-J5QAAAAA%3AN_aq7pXWDrsSAOmcdEcCn4FR5OZERh1MaNUenv4Is5BJ6sfGRRXCN78DVDjBK4r2f6WEeK5ahbkTgw
 * We define the k-core of a multiplex network as its largest  
 * subgraph in which each vertex  has at least k_i edges  
 * of each type i
 * [...]
 * To obtain the k-core of a multiplex network, we use the 
 * following pruning algorithm: At each step we remove every
 * vertex if for at least one type of edge i, q_i<k_i.
 */
vector<int> multiCore(MultilayerNetwork& m) {
    // for each node we keep the in-degree in each layer and we push
    // in in a priority queue with the min-degree
    vector<vector<int>> in_deg = m.in_degree();
    vector<int> min_deg(m.nodes()), core(m.nodes());

    priority_queue<ii, vector<ii>, greater<ii>> q;
    for(int i = 0; i < m.nodes(); i++) {
        min_deg[i] = *min_element(in_deg[i].begin(), in_deg[i].end());
        q.push(ii(min_deg[i], i));
    }
    int c = 0;

    while(!q.empty()) {
        while(!q.empty() && q.top().first <= c) {
            ii t = q.top();
            q.pop();
            int node = t.second, d = t.first;
            if (d == min_deg[node]) { // the node was not removed yet
                core[node] = c;
                // remove it and its outgoing edges
                for(int l : m.layers(node)) {
                    for(Node &e : m.adj(node, l)) {
                        if(min_deg[e.node] > min_deg[node]){ // if the neighbor was not removed yet
                            in_deg[e.node][e.layer]--;
                            if(in_deg[e.node][e.layer] < min_deg[e.node]){
                                min_deg[e.node] = in_deg[e.node][e.layer];
                                q.push(ii(min_deg[e.node], e.node));
                            }
                        }
                    }
                }
            }
        }
        c++;
    }
    return core;
}


