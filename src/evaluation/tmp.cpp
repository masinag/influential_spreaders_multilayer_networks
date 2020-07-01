#include <cassert>
#include <unordered_map>
#include <algorithm>
#include "../utils/Multilayer.h"

string mlpath = "../../data/multilayer/generated/";

void compare(Graph &g1, Graph &g2){
    assert(g1.size() == g2.size());
    unordered_map<int, int> map1, map2;
    for(int i = 0; i < g1.size(); i++){
        map1[g1.node_name[i]] = i;
        map2[g2.node_name[i]] = i;
    }
    for(int i = 0; i < g1.size(); i++){
        assert(g1.adj(i).size() == g2.adj(map2[g1.node_name[i]]).size());
        int v1 = i;
        int v2 = map2[g1.node_name[v1]];
        vector<int> ad1, ad2;
        for(int v = 0; v < g1.adj(i).size(); v++){
            
            int a1 = g1.adj(v1)[v];
            int a2 = g2.adj(v2)[v];
            ad1.push_back(g1.node_name[a1]);
            ad2.push_back(g2.node_name[a2]);
            // int n1 = g1.node_name[v1];
            // if(g1.node_name[g1.adj(i)[v]] == g2.node_name[g2.adj(map2[g1.node_name[i]])[v]])
            // if( == g2.node_name[a2])
                // printf("Ok\n");
            // else printf("Hell no!\n");
        }
        sort(ad1.begin(), ad1.end());
        sort(ad2.begin(), ad2.end());
        assert(ad1 == ad2);
    }
}
void compare_layers(MultilayerNetwork &m1, MultilayerNetwork &m2){
    assert(m1.nodes() == m2.nodes());
    assert(m1.layers() == m2.layers());
    for (int n = 0; n < m1.nodes(); n++){
        assert(m1.layers(n) == m2.layers(n));
        for(int l : m1.layers(n)){
            vector<int> a1, a2;
            for(Node &e : m1.adj(n, l))
                if(e.layer == l) a1.push_back(e.node);

            for(Node &e : m2.adj(n, l))
                if(e.layer == l) a2.push_back(e.node);
            sort(a1.begin(), a1.end());
            sort(a2.begin(), a2.end());
            assert(a1 == a2);
        }
    }
}
int main(int argc, char const *argv[])
{
    string s1 = mlpath + "SLN_2_0.8_0.8_0.8.edges";
    string s2 = mlpath + "SLN_2_0.8_0.8_0.3.edges";
    MultilayerNetwork m1 = readMultilayer(s1);
    MultilayerNetwork m2 = readMultilayer(s2);
    // compare_layers(m1, m2);
    vector<Graph> ll1 = m1.to_vector();
    vector<Graph> ll2 = m2.to_vector();

    for(int i = 0; i < m1.layers(); i++){
        compare(ll1[i], ll2[i]);
    }
    return 0;
}
