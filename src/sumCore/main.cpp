#include <iostream>
#include "sumCore.h"
#include "../utils/common.h"

int main(int argc, char const *argv[]){
    MultilayerNetwork g = readMultilayer();
    vector<int> core = sumCore(g);
    vector<int> sorted = sort_nodes(core);
    for(int i = 0; i < core.size(); i++) {
        cout << sorted[i] << ", score: " << core[sorted[i]] << endl;
    }
    return 0;
}