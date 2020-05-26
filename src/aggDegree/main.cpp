#include <iostream>
#include "aggDeg.h"
#include "../utils/common.h"

int main(int argc, char const *argv[]) {
    if(argc < 2) {
        cerr << "File name not found" << endl;
        exit(EXIT_FAILURE);
    }
    string file = argv[1];
    Graph g = readGraph(file);
    vector<int> deg = degree(g);
    vector<int> sorted = sort_nodes(deg);
    for(int i = 0; i < deg.size(); i++) {
        cout << sorted[i] << ", score: " << deg[sorted[i]] << endl;
    }
    return 0;
}