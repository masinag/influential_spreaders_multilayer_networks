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

// ALGORITHMS = ["addPageRank", "verPageRank", "laPCI", "mlPCI", "lsPCI", "aggPageRank", 
//         "multiCore", "sumCore", "aggCore", "alPCI", "aggDegree", "verBetweenness"]

bool endswith(string &value, string ending){
    return equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void read_alg_scores(string &net_path, vector<string> &alg_names, vector<vector<double>> &alg_scores){
    vector<string> files;
    // cerr << net_path << endl;
    read_directory(net_path, files);
    // cerr << "alg dir read" << endl;
    for (string &alg : files){
        if (endswith(alg, ".alg")){
            cerr << "\t" << alg << endl; 
            ifstream in(net_path + "/" + alg);
            char t;
            int n;

            in >> t >> n;
            alg_names.push_back(alg.substr(0, alg.size() - 4));
            alg_scores.push_back(vector<double>(n, 0));
            
            vector<double> &score = alg_scores[alg_scores.size() - 1];
            // cerr << "scores initialized for " << alg << endl;
            for(int i = 0; i < n; i++)
                in >> score[i];
            // cerr<< "scores read" << endl;
        }
    }
}

void compute_avg(string &path){
    int count = 0;
    vector<int> score;
    vector<string> files;
    read_directory(path, files);
    for (string &filename : files){
        if (endswith(filename, ".sim")){
            count += 1;
            ifstream in(path + "/" + filename);
            int num_nodes, sum_nodes;
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
    ofstream out(path + "/" + AVG_FILE);

    out << score.size() << endl;
    for (int s : score)
        out << (double(s) / count) << endl;
}

vector<double> read_sim_scores(string &path){
    ifstream in(path + "/" + AVG_FILE);
    int n;
    in >> n;
    vector<double> score(n, 0);
    for(int i = 0; i < n; i++)
        in >> score[i];
    
    return score;
}

vector<double> evaluate(vector<double> &sim_score, vector<vector<double>> &alg_scores){
    vector<double> scores(alg_scores.size(), 0);
    int i = 0;
    for(vector<double> &s : alg_scores){
        // cout << "s:" << s.size() << ", " << "sim:" << sim_score.size() << endl;
        assert(s.size() == sim_score.size());
        scores[i] = kendallsTau(s, sim_score);
        i++;
    }   
    return scores;
}


void write_rankings(string &base, string &net, string &lambda_dir, vector<string> &alg_names, vector<double> &ktt){
    string rank_dir = base + "/" + RANKING_DIR;
    cerr << "# " << rank_dir << endl;
    if(!dir_exists(rank_dir)){
        create_dir(rank_dir);
    }
    string ranking_net_dir = rank_dir + net;

    if(!dir_exists(ranking_net_dir)){
        create_dir(ranking_net_dir);
    }

    ofstream out(ranking_net_dir + "/" + lambda_dir);
    cerr << (ranking_net_dir + "/" + lambda_dir) << endl;

    for(int i = 0; i < alg_names.size(); i++){
        cerr << "\t" << alg_names[i] << endl;
        out << alg_names[i] << " " << ktt[i] << endl;}
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
            string net_path = base + "/" + ALGORITHMS_DIR + net_name;
            vector<string> alg_names;
            vector<vector<double>> alg_scores;
            read_alg_scores(net_path, alg_names, alg_scores);
            // cerr << "Alg scores read" << endl;
            vector<string> lambda_dirs;
            string sim_net_path = base + "/" + SIMULATIONS_DIR + net_name;
            // cerr << sim_net_path << endl;
            read_directory(sim_net_path, lambda_dirs);
            for (string lambda_dir : lambda_dirs){
                cerr << lambda_dir << endl;
                string sim_net_lambda_path = sim_net_path + "/" + lambda_dir;
                compute_avg(sim_net_lambda_path);
                // cerr << "avg computed" << endl;
                vector<double> sim_scores = read_sim_scores(sim_net_lambda_path);
                // cerr << "dsd:" << sim_scores.size() << endl;
                // cerr << "sim scores read" << endl;
                vector<double> ktt = evaluate(sim_scores, alg_scores);
                // cerr << "ktt got" << endl;
                write_rankings(base, net_name, lambda_dir, alg_names, ktt);
                // cerr << "rankings written" << endl;
            }
        }
    }
    return 0;

}
