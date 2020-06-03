#ifndef IO_H
#define IO_H
#include <string> 
#include <vector> 

using namespace std;

void read_directory(string &name, vector<string>& v);
string get_log_file(string &base);
void write_log(string &log_file, string log_message);
void write_simulation_results(int total_nodes, vector<int> &sp, string &base, string &network_name, string lambda_coeff, int i);


#endif