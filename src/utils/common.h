#ifndef COMMON_H
#define COMMON_H
#include <vector>
using namespace std;

vector<int> sort_nodes(vector<double> &scores);
vector<int> sort_nodes(vector<int> &scores);
void normalize(vector<double> &x);
void stochasticize(vector<double> &x);
bool almost_eq(double a, double b);
bool almost_eq(vector<double> &a, vector<double> &b);

#endif