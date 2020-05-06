#ifndef AGG_CORE_H
#define AGG_CORE_H

#include <vector>
#include "../utils/Aggregate.h"
using namespace std;

vector<int> fast_k_core(Graph& g);
vector<int> k_core(Graph& g);

#endif