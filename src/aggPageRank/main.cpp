#include <iostream>
#include "aggPR.h"

#include "../utils/common.h"

int main(int argc, char const *argv[]) {
    if(argc < 2) {
        cerr << "File name not found" << endl;
        exit(EXIT_FAILURE);
    }
    string file = argv[1];
    Graph g = readAggregate(file);
    vector<double> rank = pageRank(g);
    vector<int> sorted = sort_nodes(rank);
    for(int i = 0; i < rank.size(); i++) {
        cout << sorted[i] << ", score: " << rank[sorted[i]] << endl;
    }
    return 0;
}