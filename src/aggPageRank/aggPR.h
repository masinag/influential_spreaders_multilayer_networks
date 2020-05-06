#ifndef AGG_PR_H
#define AGG_PR_H

#include <vector>
#include "../utils/Aggregate.h"
using namespace std;

vector<double> pageRank(Graph &out_edges, double alpha = 0.85);

#endif