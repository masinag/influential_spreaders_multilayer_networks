#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <string> 
#include <vector> 

using namespace std;
extern string data_dirs[2]; 

void read_directory(string &name, vector<string>& v);
string get_log_file(string &base);
void write_log(string &log_file, string log_message);
void write_simulation_results(int total_nodes, vector<int> &sp, string &base, string &network_name, string lambda_coeff, int i);
void write_algorithm_results(vector<int> &score, string alg_name, string &base, string &network_name);
void write_algorithm_results(vector<double> &score, string alg_name, string &base, string &network_name);
string get_network_name(string &network_path);


#endif