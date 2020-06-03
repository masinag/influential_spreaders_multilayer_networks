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

// O(m + n) algorithm with bin-sort
vector<int> fastMultiCore(MultilayerNetwork& g){
    int n, md, start, num;
    vector<vector<int>> in_deg = g.in_degree();

    n = g.nodes();
    vector<int> vert(g.nodes()),  // will contain the nodes sorted by their in_deg
                pos(g.nodes()),   // will cointain the position of node i in vert
    // deg will contain the minimum in_degree of i in any layer
                deg(g.nodes()); // will contain the core of node i
    for(int i = 0; i < g.nodes(); i++)
        deg[i] = *min_element(in_deg[i].begin(), in_deg[i].end());

    md = *max_element(deg.begin(), deg.end()); // max degree
    vector<int> bin(md + 1, 0); // will contain the position in vert of the first
                                // vertex with degree i

    // sort the vertices in increasing order of their degrees using bin-sort
    // compute values of bin
    for(int v = 0; v < n; v++)
        bin[deg[v]]++;
    start = 0;
    for (int d = 0; d <= md; d++){
        num = bin[d];
        bin[d] = start;
        start += num;
    }
    // put nodes in vert
    for(int v = 0; v < n; v++){
        pos[v] = bin[deg[v]];
        vert[pos[v]] = v;
        bin[deg[v]]++;
    }

    // restore correct values of bin
    for(int d = md; d > 0; d--)
        bin[d] = bin[d-1];

    // Core decomposition: the core number of current vertex v is the current 
    // degree of that vertex.
    bin[0] = 1;
    for(int i = 0; i < n; i++){
        int v = vert[i];
        for(int l : g.layers(v)){
            for(Node &u : g.adj(v, l)) {
                if (deg[u.node] > deg[v]) { // u is not visited yet
                    // decrement its in_degree in this layer
                    in_deg[u.node][u.layer]--;
                    // if it has become the minimum over all layers, update the vectors
                    if(in_deg[u.node][u.layer] < deg[u.node]){
                        // decrement degree of u and move it to the previous bin
                        int du = deg[u.node], pu = pos[u.node];
                        int pw = bin[du];
                        int w = vert[pw];
                        if (u.node != w) { // if u is not the first node of its bin, switch
                            pos[u.node] = pw;
                            vert[pu] = w;
                            pos[w] = pu;
                            vert[pw] = u.node;
                        }
                        bin[du]++; // bin[du] has one node less -> increase start
                        deg[u.node]--;  // u is the last of the previous bin
                    }
                }
            }
        }
    }
    return deg;
}