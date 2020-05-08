#ifndef AGG_PR_H
#define AGG_PR_H

#include <vector>
#include "../utils/Aggregate.h"
#define DIFF_EPSILON 0.0001

using namespace std;

double difference(vector<double> &v, vector<double> &w);
vector<double> pageRank(Graph &out_edges, double alpha = 0.85);

#endif