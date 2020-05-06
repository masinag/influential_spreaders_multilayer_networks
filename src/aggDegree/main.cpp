#include <iostream>
#include "aggDeg.h"
#include "../utils/common.h"
int main() {
    Graph g = readAggregate();
    vector<int> deg = degree(g);
    vector<int> sorted = sort_nodes(deg);
    for(int i = 0; i < deg.size(); i++) {
        cout << sorted[i] << ", score: " << deg[sorted[i]] << endl;
    }
    return 0;
}