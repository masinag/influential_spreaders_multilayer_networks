#include <fstream>
#include <cassert>
#include <iostream>
#include "ranking.h"
#include "io.h"


string DATASETS_DIRS[2] = {"../../data/multiplex/extracted/", "../../data/multilayer/generated"};

string SIMULATIONS_DIR = "../../results/simulations/";
string ALGORITHMS_DIR = "../../results/algorithms/";
string RANKING_DIR = "../../results/rankings/";

string AVG_FILE = "avg";

bool endswith(string &value, string ending){
    return equal(ending.rbegin(), ending.rend(), value.rbegin());
}

vector<double> compute_avg(string &path, int n){
    int count = 0;
    vector<int> score;
    vector<string> files;
    read_directory(path, files);
    int num_nodes, sum_nodes;
    
    for (string &filename : files){
        if (endswith(filename, ".sim")){
            if(n-- == 0) break;

            count += 1;
            ifstream in(path + "/" + filename);
            in >> num_nodes >> sum_nodes;
            if(score.size() == 0)
                score.resize(num_nodes, 0);
            int k;
            for(int i = 0; i < num_nodes; i++){
                in >> k;
                score[i] += k;
            }
        }
    }
    vector<double> x(score.size());
    for(int i = 0; i<score.size(); i++)
        x[i] = double(score[i]) / count; 
    return x;
}

double absdiff(vector<double> &a, vector<double> &b){
    double x = 0.0L;
    for(int i = 0; i < a.size(); i++)
        x += abs(a[i] - b[i]);
    return x;
}



int main(int argc, char const *argv[]) {

    string argv_str(argv[0]);
    string base = argv_str.substr(0, argv_str.find_last_of("/"));

    // # for each dataset output the kendall"s Tau
    for (string &dir : DATASETS_DIRS){
        vector<string> nets;
        string dir_path = base + "/" + dir;
        read_directory(dir_path, nets);
        for (string &net : nets){
            string net_name;
            // cerr << ">" << net << endl;
            if(endswith(net, ".edges"))
                net_name = net.substr(0, net.size() - 6);
            else
                net_name = net;
            cerr << net_name << endl;
            // string net_path = base + "/" + ALGORITHMS_DIR + net_name;
            vector<string> lambda_dirs;
            string sim_net_path = base + "/" + SIMULATIONS_DIR + net_name;
            // cerr << sim_net_path << endl;
            read_directory(sim_net_path, lambda_dirs);
            for (string lambda_dir : lambda_dirs){
                cerr << lambda_dir << endl;
                string sim_net_lambda_path = sim_net_path + "/" + lambda_dir;
                vector<double> avg100 = compute_avg(sim_net_lambda_path, 100);
                vector<double> avg50 = compute_avg(sim_net_lambda_path, 80);
                cerr << lambda_dir  << ": " << absdiff(avg100, avg50) << " / " << avg100.size() << endl;
            }
        }
    }
    return 0;

}
