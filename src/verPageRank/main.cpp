#include <iostream>
#include "verPR.h"
#include "../utils/common.h"

int main(int argc, char const *argv[]){
    MultilayerNetwork g = readMultilayer();
    vector<double> rank = verPageRank(g);
    vector<int> sorted = sort_nodes(rank);
    for(int i = 0; i < rank.size(); i++) {
        cout << sorted[i] << ", score: " << rank[sorted[i]] << endl;
    }
    return 0;
}