#ifndef RANKING_H
#define RANKING_H
#include <vector>
using namespace std;

double kendallsTau(vector<double> &x, vector<double> &y);
double kendallsTau(vector<int> &x, vector<double> &y);
double imprecision(vector<int> &s1, vector<int> &s2, vector<double> &sp, double p);

#endif