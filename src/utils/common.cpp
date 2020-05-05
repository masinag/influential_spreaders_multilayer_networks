#include <vector>
#include <algorithm>
#include <iostream>
#include "common.h"

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