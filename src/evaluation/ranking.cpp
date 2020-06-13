#include <iostream>
#include "../utils/common.h"

#define EPS 1e-06

int sign(double x){
    return almost_eq(x, 0.0L) ? 0 :  (x > 0 ? 1 : -1);
}

double kendallsTau(vector<double> &x, vector<double> &y){
    int count = 0;
    int tie_alg = 0, tie_sim = 0;
    for (int i = 1; i < x.size(); i++)
        for (int j = 0; j < i; j++){
            // count += sign(x[i] - x[j]) * sign(y[i] - y[j]);
            int s1 = sign(x[i] - x[j]);
            if(s1 == 0) tie_alg++;
            int s2 = sign(y[i] - y[j]);
            if(s2 == 0) tie_sim++;
            count += s1 * s2;
        }
    // cerr << "tie_alg: " << tie_alg << ", tie_sim: " << tie_sim << endl;
    return 2 * count / double(x.size() * (x.size() - 1));
}

double kendallsTau(vector<int> &x, vector<double> &y){
    vector<double> nx(x.size());
    for(int i = 0; i < x.size(); i++)
        nx[i] = double(x[i]);
    return kendallsTau(nx, y);
}


double kendallsTau(vector<double> &x, vector<double> &y, vector<double> &tie_break){
    int count = 0;
    for (int i = 1; i < x.size(); i++)
        for (int j = 0; j < i; j++){
            int s1 = sign(x[i] - x[j]);
            if(s1 == 0) s1 = sign(tie_break[i] - tie_break[j]);
            int s2 = sign(y[i] - y[j]);
            if(s2 == 0) s2 = sign(tie_break[i] - tie_break[j]);
            count += s1 * s2;
        }
        
    return 2 * count / double(x.size() * (x.size() - 1));
}