#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <string>
using namespace std;


class Graph{
    private:
        int n;
        vector< vector<int> > g;
    public:
        vector<int> node_name;

        Graph(int v);
        void addEdge(int a, int b);
        vector<int>& adj(int x);
        int size();
        void transpose(Graph &t);
        vector<int> in_deg();
        vector<int> out_deg();
        vector<double> multiply_as_adj_matrix(vector<double> &x);
        vector<double> eigenvector(int max_iter = 100);
        double eigenvalue();
};

Graph readGraph(string &file);


#endif