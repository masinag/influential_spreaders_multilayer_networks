#include <iostream>
#include <cassert>
#include "ranking.h"
#include "../utils/common.h"

int main(int argc, char const *argv[]) {
    int tests, size;
    cout << "Tests: ";
    cin >> tests;
    cout << "Vector size: ";
    cin >> size;

    srand((unsigned)time(NULL));
    double max_diff = 0.0L;
    while(tests--) {
        vector<double> a(size);
        vector<double> b(size);
        for(double &i : a) i = double(rand() % 2) / double(1 + rand() % 10);
        for(double &i : b) i = double(rand() % 2) / double(1 + rand() % 10);
        double x = kendallsTau(a, b);
        double y = kendall(a, b);
        if (!almost_eq(x, y)) {
            // cout << x << " - " << y << endl;
            max_diff = max(max_diff, abs(x-y));
        }
    }
    cout << "Max diff: " << max_diff;
    return 0;
}
