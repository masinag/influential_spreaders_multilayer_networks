#include <vector>
#include <algorithm>
#include <iostream>
#include "common.h"

using namespace std;

vector<int> sort_nodes(vector<double> &scores){
    // vector< pair <double, int> > tmp(scores.size());
    // for(int i = 0; i < scores.size(); i++)
    //     tmp[i] = make_pair(scores[i], i);
    vector<int> res(scores.size());
    for(int i = 0; i < scores.size(); i++)
        res[i] = i;
    sort(res.begin(), res.end(), [scores](int a, int b) {
        return scores[a] > scores[b];
    });
    return res;
}