#include <iostream>
#include "mlPCI.h"
#include "../utils/common.h"

int main(int argc, char const *argv[]) {
    if(argc < 2) {
        cerr << "File name not found" << endl;
        exit(EXIT_FAILURE);
    }
    string file = argv[1];
    MultilayerNetwork m = readMultilayer(file);
    vector<int> mlPCI_score = mlPCI(m);
    vector<int> sorted = sort_nodes(mlPCI_score);
    for(int i = 0; i < mlPCI_score.size(); i++) {
        cout << sorted[i] << ", score: " << mlPCI_score[sorted[i]] << endl;
    }
    return 0;
}
