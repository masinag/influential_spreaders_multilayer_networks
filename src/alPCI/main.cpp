#include <iostream>
#include "alPCI.h"
#include "../utils/common.h"

int main(int argc, char const *argv[]) {
    MultilayerNetwork m = readMultilayer();
    vector<int> alPCI_score = alPCI(m);
    vector<int> sorted = sort_nodes(alPCI_score);
    for(int i = 0; i < alPCI_score.size(); i++) {
        cout << sorted[i] << ", score: " << alPCI_score[sorted[i]] << endl;
    }
    return 0;
}
