#ifndef VER_PR_H
#define VER_PR_H

#include <vector>
#include "../utils/Multilayer.h"
using namespace std;

vector<double> verPageRank(MultilayerNetwork& g, double alpha = 0.85, int max_iter = 200);

#endif