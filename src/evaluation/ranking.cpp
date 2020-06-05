#include "../utils/common.h"

#define EPS 1e-06

int sign(double x){
    return almost_eq(x, 0.0L) ? 0 :  (x > 0 ? 1 : -1);
}

double kendallsTau(vector<double> &x, vector<double> &y){
    int count = 0;
    for (int i = 1; i < x.size(); i++)
        for (int j = 0; j < i; j++)
            count += sign(x[i] - x[j]) * sign(y[i] - y[j]);
        
    return 2 * count / double(x.size() * (x.size() - 1));
}

double kendallsTau(vector<int> &x, vector<double> &y){
    vector<double> nx(x.size());
    for(int i = 0; i < x.size(); i++)
        nx[i] = double(x[i]);
    return kendallsTau(nx, y);
}
