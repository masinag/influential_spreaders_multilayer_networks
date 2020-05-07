#ifndef AGGREGATE_H
#define AGGREGATE_H
#include <vector>
using namespace std;


class Graph{
    private:
        int n;
        vector< vector<int> > g;
    public:
        Graph(int v);
        void addEdge(int a, int b);
        vector<int>& adj(int x);
        int size();
        Graph transpose();
        vector<int> in_deg();
        vector<int> out_deg();
        vector<double> multiply_as_adj_matrix(vector<double> &x);
        vector<double> eigenvector();
        double eigenvalue();
};

Graph readAggregate();


#endif