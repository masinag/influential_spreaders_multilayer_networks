#include <iostream>
#include "sumCore.h"
#include "../aggCore/aggCore.h"
using namespace std;
/**
 * we calculate the shells for each layer separately and then add
 * those values; we name this version as the sumCore index.
*/
vector<int> sumCore(MultilayerNetwork& g){
    vector<Graph> m = g.to_vector();
    vector<int> core(g.nodes(), 0);
    for(Graph &l : m){
        vector<int> layer_core = fast_k_core(l);
        for(int i = 0; i < layer_core.size(); i++)
            core[i] += layer_core[i];
    }
    return core;
}
