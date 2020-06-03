#include <iostream>
#include "multiCore.h"
#include "../utils/common.h"

int main(int argc, char const *argv[]) {
    if(argc < 2) {
        cerr << "File name not found" << endl;
        exit(EXIT_FAILURE);
    }
    string file = argv[1];
    MultilayerNetwork m = readMultilayer(file);
    MultilayerNetwork t(m.layers(), m.nodes());
    m.transpose(t);
    vector<int> core = multiCore(m);
    vector<int> fcore = fastMultiCore(m);
    vector<int> sorted = sort_nodes(core);
    for(int i = 0; i < core.size(); i++) {
        if (fcore[i] != core[i])
            cout << "error!" << endl;
        // cout << sorted[i] << ", score: " << core[sorted[i]] << endl;
    }
    return 0;
}