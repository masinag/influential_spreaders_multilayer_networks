#include <stack>
#include <queue>
#include <cassert>
#include "verBC.h"

/**
 * Implementation of http://dx.doi.org/10.1145/2615569.2615687
 * The versatility betwenness centrality of a node v in a multilayer network
 * is defined as the sum for each couple of nodes (s, t) of the ratio 
 * between the number of paths between s and t in any layer that pass through 
 * v regardless of the layer and the total number of paths between s and t
 * in any layer.
 */
vector<double> verBetweennessCentrality(MultilayerNetwork &m){
    queue<Node> q;
    stack<Node> bfs_stack;
    vector<double> bc(m.nodes(), 0.0L);
    vector<vector<double>> delta(m.nodes(), vector<double> (m.layers()));
    vector<vector<vector<Node>>> pred(m.nodes(), vector<vector<Node>>(m.layers()));
    vector<vector<int>> sigma(m.nodes(), vector<int>(m.layers()));
    vector<vector<int>> dist(m.nodes(), vector<int>(m.layers()));
    vector<int> dist_m(m.nodes());
    vector<int> sigma_m(m.nodes());
    vector<unordered_set<int>>v_order(m.nodes());

    for(int s = 0; s < m.nodes(); s++){
        // initialize data_structures
        for(int i = 0; i < m.nodes(); i++){
            for(int l : m.layers(i)){
                pred[i][l].clear();
                sigma[i][l] = (i == s) ? 1 : 0;
                dist[i][l]  = (i == s) ? 0 : -1;                
            }
            dist_m[i] = (i == s) ? 0 : -1;
            v_order[i].clear();
        }
        assert(bfs_stack.empty());
        assert(q.empty());
        // start bfs
        for(int l : m.layers(s))
            q.push(Node(s, l));
        
        while(!q.empty()){
            Node v = q.front();
            q.pop();
            bfs_stack.push(v);
            
            // visit neighbors
            for (Node &w : m.adj(v.node, v.layer)){
                if(dist[w.node][w.layer] < 0) { // first visit to this node in this layers
                    q.push(w);
                    dist[w.node][w.layer] = dist[v.node][v.layer] + 1;
                    if (dist_m[w.node] < 0 || dist_m[w.node] == dist[w.node][w.layer]) { // node reached with min dist in any layer
                      dist_m[w.node] = dist[w.node][w.layer];
                      v_order[w.node].insert(w.layer);
                    }
                }

                if (dist[w.node][w.layer] == dist[v.node][v.layer] + 1){ // node reached with min dist in any layer
                    sigma[w.node][w.layer] += sigma[v.node][v.layer];
                    pred[w.node][w.layer].push_back(v);
                }
            }
        }
        // compute the total number of shortest-paths which reach each destination
        // regardless of the layer
        for(int w = 0; w < m.nodes(); w++){
            sigma_m[w] = 0;
            for(int layer : v_order[w]) {
                sigma_m[w] += sigma[w][layer];
            }
            // reset deltas
            for(int l = 0; l < m.layers(); l++){
                delta[w][l] = 0.0L;
            }
        }

        // compute dependencies of s from each node
        while (!bfs_stack.empty()){
            Node w = bfs_stack.top();
            bfs_stack.pop();
            for(Node &v : pred[w.node][w.layer]){ // for each predecessor of w in some shortest path to w
                double ratio = double(sigma[v.node][v.layer]) / double(sigma[w.node][w.layer]);
                assert(sigma[w.node][w.layer] > 0);

                if (v_order[w.node].find(w.layer) != v_order[w.node].end()){ // the node w in this layer is reached by a shortest-path
                    delta[v.node][v.layer] += ratio * (double(sigma[w.node][w.layer]) / double(sigma_m[w.node]) + delta[w.node][w.layer]);
                } else {
                    delta[v.node][v.layer] += ratio * delta[w.node][w.layer];
                }

            }
            if(w.node != s){
                bc[w.node] += delta[w.node][w.layer];
            }
        }

    }

    return bc;

}