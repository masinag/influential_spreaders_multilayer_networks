#ifndef COMMON_H
#define COMMON_H
#include <vector>
using namespace std;

vector<int> sort_nodes(vector<double> &scores);
vector<int> sort_nodes(vector<int> &scores);
bool almost_eq(double a, double b);

#endif