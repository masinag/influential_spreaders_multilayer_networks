#include <iostream>
#include <cassert>
#include "aggCore.h"
#include "../utils/common.h"

int main(int argc, char const *argv[]) {
    Graph g = readAggregate();
    vector<int> core = k_core(g);
    vector<int> fcore = fast_k_core(g);
    vector<int> sorted = sort_nodes(core);
    for(int i = 0; i < core.size(); i++) {
        assert(core[i] == fcore[i]);
        cout << sorted[i] << ", score: " << core[sorted[i]] << endl;
    }
    return 0;
}
