#include <iostream>
#include "aggPR.h"

#include "../utils/common.h"

int main() {
    Graph g = readAggregate();
    vector<double> rank = pageRank(g);
    vector<int> sorted = sort_nodes(rank);
    for(int i = 0; i < rank.size(); i++) {
        cout << sorted[i] << ", score: " << rank[sorted[i]] << endl;
    }
    return 0;
}