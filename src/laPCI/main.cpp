#include <iostream>
#include "laPCI.h"
#include "../utils/common.h"

int main(int argc, char const *argv[]) {
    MultilayerNetwork m = readMultilayer();
    vector<int> laPCI_score = laPCI(m);
    vector<int> sorted = sort_nodes(laPCI_score);
    for(int i = 0; i < laPCI_score.size(); i++) {
        cout << sorted[i] << ", score: " << laPCI_score[sorted[i]] << endl;
    }
    return 0;
}
