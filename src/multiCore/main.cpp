#include <iostream>
#include "multiCore.h"
#include "../utils/common.h"

int main(int argc, char const *argv[]){
    MultilayerNetwork g = readMultilayer();
    MultilayerNetwork t = g.transpose();
    vector<int> core = multiCore(g);
    vector<int> sorted = sort_nodes(core);
    for(int i = 0; i < core.size(); i++) {
        cout << sorted[i] << ", score: " << core[sorted[i]] << endl;
    }
    return 0;
}