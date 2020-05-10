#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "common.h"
#define DOUBLE_EPS 1.0e-6

using namespace std;

vector<int> sort_nodes(vector<double> &scores){
    vector<int> res(scores.size());
    for(int i = 0; i < scores.size(); i++)
        res[i] = i;
    sort(res.begin(), res.end(), [scores](int a, int b) {
        return scores[a] > scores[b];
    });
    return res;
}

vector<int> sort_nodes(vector<int> &scores){
    vector<int> res(scores.size());
    for(int i = 0; i < scores.size(); i++)
        res[i] = i;
    sort(res.begin(), res.end(), [scores](int a, int b) {
        return scores[a] > scores[b];
    });
    return res;
}

bool almost_eq(double a, double b){
    return abs(a-b) <= DOUBLE_EPS;
}

void normalize(vector<double> &x){
    double mag = 0.0L;
    for(double v : x)
        mag += v*v;
    mag = sqrt(mag);
    if (mag > 0.0L) {
        for(double &v : x)
            v /= mag;
    }
}

void stochasticize(vector<double> &x){
    double sum = 0.0L;
    for(double v : x)
        sum += v;
    printf("Sum: %.5f\n", sum);
    if (sum > 0.0L) {
        for(double &v : x)
            v /= sum;
    }   
}

bool almost_eq(vector<double> &a, vector<double> &b){
    double err = 0.0L;
    for(int i = 0; i < a.size(); i++){
        err += abs(a[i] - b[i]);
    }
    // printf("err: %.5f < %.5f\n", err, VECTOR_EPS * a.size());
    return err <= DOUBLE_EPS * a.size();
}

bool almost_eq(vector<vector<double>> &a, vector<vector<double>> &b) {
    double err = 0.0L;
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < a[i].size(); j++){
            err += abs(a[i][j] - b[i][j]);
        }
    }
    return err <= DOUBLE_EPS * a.size() * a[0].size();
}