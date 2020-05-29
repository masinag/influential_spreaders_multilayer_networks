#include "ranking.h"
#include "common.h"
/**
 * numer := 0
 * for i := 2..N do
 *      for j := 1..(i − 1) do
 *          numer := numer + sign(x[i] − x[j]) × sign(y[i] − y[j])
 * return numer
 * + 1 *  (sp[i] > sp[j]) && rank[i] > rank[j] else -1 (?)
 * x[i] > x[j] && y[i] > y[j]
 */

int sign(double x){
    return almost_eq(x, 0) ? 0 : x > 0 ? 1 : -1;
}

double kendallsTau(vector<double> &x, vector<double> &y){
    int count = 0;
    for(int i = 1; i < x.size(); i++)
        for(int j = 0; j < i; j++)
            count += sign(x[i] - x[j]) * sign(y[i] - y[j]);
    return double(2 * count) / double((x.size()) * (x.size() - 1));
}

double kendallsTau(vector<int> &x, vector<double> &y){
    vector<double> new_x(x.size());
    for(int i = 0; i < x.size(); i++)
        new_x[i] = double(x[i]);
    return kendallsTau(new_x, y);
}

double imprecision(vector<int> &rank_sim, vector<int> &rank_alg, vector<double> &sp, double p){
    int count = p * rank_alg.size();
    double avg_sp_alg = 0.0L, avg_sp_sim = 0.0L;
    for(int i = 0; i < count; i++){
        avg_sp_alg += sp[rank_alg[i]];
        avg_sp_sim += sp[rank_sim[i]];
    }
    return 1 - avg_sp_alg / avg_sp_sim;
}