#include <iostream>
#include "lsPCI.h"
#include "../utils/common.h"

int main(int argc, char const *argv[]) {
    MultilayerNetwork m = readMultilayer();
    vector<int> lsPCI_score = lsPCI(m);
    vector<int> sorted = sort_nodes(lsPCI_score);
    for(int i = 0; i < lsPCI_score.size(); i++) {
        cout << sorted[i] << ", score: " << lsPCI_score[sorted[i]] << endl;
    }
    return 0;
}
