#include <iostream>
#include "alPCI.h"
#include "../utils/common.h"

int main(int argc, char const *argv[]) {
    if(argc < 2) {
        cerr << "File name not found" << endl;
        exit(EXIT_FAILURE);
    }
    string file = argv[1];
    MultilayerNetwork m = readMultilayer(file);
    vector<int> alPCI_score = alPCI(m);
    vector<int> sorted = sort_nodes(alPCI_score);
    for(int i = 0; i < alPCI_score.size(); i++) {
        cout << sorted[i] << ", score: " << alPCI_score[sorted[i]] << endl;
    }
    return 0;
}
