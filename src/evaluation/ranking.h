#ifndef RANKING_H
#define RANKING_H

#include <vector>
using namespace std;


// double kendallsTau(vector<double> &x, vector<double> &y);
// double kendallsTau(vector<int> &x, vector<double> &y);
double kendall(vector<double> &x, vector<double> &y);
double kendallsTau(vector<double> &x, vector<double> &y, vector<double> &tie_break);

#endif