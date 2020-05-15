#include <iostream>
#include "sumCore.h"
#include "../utils/common.h"

int main(int argc, char const *argv[]) {
    if(argc < 2) {
        cerr << "File name not found" << endl;
        exit(EXIT_FAILURE);
    }
    string file = argv[1];
    MultilayerNetwork m = readMultilayer(file);
    vector<int> core = sumCore(m);
    vector<int> sorted = sort_nodes(core);
    for(int i = 0; i < core.size(); i++) {
        cout << sorted[i] << ", score: " << core[sorted[i]] << endl;
    }
    return 0;
}