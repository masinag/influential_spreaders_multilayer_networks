#include <vector>
#include <algorithm>
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