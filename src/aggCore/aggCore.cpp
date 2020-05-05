/**
 * K-Core implementation
 * http://arXiv.org/abs/cs/0310049v1
 */

#include <iostream>
#include <algorithm>
#include <cassert>
#include <queue>
#include "../utils/Aggregate.h"
#include "../utils/common.h"
using namespace std;
typedef pair<int, int> ii;

// O(m + n) algorithm with bin-sort
vector<int> fast_k_core(Graph& g){
    int n, md, start, num;
    n = g.size();
    vector<int> vert(g.size()),  // will contain the nodes sorted by their in_deg
                pos(g.size()),   // will cointain the position of node i in vert
                deg = g.in_deg(); // will contain the core of node i
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
        for(int u : g.adj(v)) {
            if (deg[u] > deg[v]) { // u is not visited yet
                // decrement degree of u and move it to the previous bin
                int du = deg[u], pu = pos[u];
                int pw = bin[du];
                int w = vert[pw];
                if (u != w) { // if u is not the first node of its bin, switch
                    pos[u] = pw;
                    vert[pu] = w;
                    pos[w] = pu;
                    vert[pw] = u;
                }
                bin[du]++; // bin[du] has one node less -> increase start
                deg[u]--;  // u is the last of the previous bin
            }
        }
    }

    return deg;
    
}

// O(m*log(n)) algorithm with priority queue
vector<int> k_core(Graph& g){
    vector<int> core(g.size());
    vector<int> in_deg = g.in_deg();
    priority_queue<ii, vector<ii>, greater<ii>> q;
    for(int i = 0; i < g.size(); i++)
        q.push(ii(in_deg[i], i));
    int c = 0; // core
    while(!q.empty()){
        while(!q.empty() && q.top().first <= c) {
            ii t = q.top();
            int n = t.second, d = t.first;
            q.pop();
            if(d == in_deg[n]){
                core[n] = c;
                for(int v : g.adj(n))
                    if (in_deg[v] > in_deg[n]){
                        in_deg[v]--;
                        q.push(ii(in_deg[v], v));
                    }
            }
        }
        c++;
    }
    return core;
    
}

int main(int argc, char const *argv[]) {
    Graph g = readAggregate();
    vector<int> core = k_core(g);
    vector<int> fcore = fast_k_core(g);
    vector<int> sorted = sort_nodes(core);
    assert(core.size() == sorted.size());
    for(int i = 0; i < core.size(); i++) {
        if(core[i] != fcore[i])
            printf("%d: %d vs %d\n", i, core[i], fcore[i]);
    //     assert(sorted[i] < core.size());
    //     cout << sorted[i] << ", score: " << core[sorted[i]] << endl;
    }
    return 0;
}
