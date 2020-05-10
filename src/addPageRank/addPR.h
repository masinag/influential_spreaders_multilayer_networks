#ifndef ADD_PR_H
#define ADD_PR_H

#include "../utils/Multilayer.h"

vector<double> additivePageRank(MultilayerNetwork &m, double alpha = 0.85);
vector<double> multiplexPageRank(MultilayerNetwork &m, double alpha, double beta, double gamma);
vector<double> layerPageRank(Graph &g, vector<double> bias, double alpha, 
    double beta, double gamma, int max_iter = 100);

#endif