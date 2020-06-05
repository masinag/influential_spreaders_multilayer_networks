

#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctime>
#include <fstream>
#include <chrono>
#include <iostream>
#include <cstring>

#include "io.h"

#define RES_DIR "../../results/"
#define SIM_DIR "simulations/"
#define ALG_DIR "algorithms/"
#define LOG_DIR "logs/"

string data_dirs[2] = {"../../data/multilayer/generated/", "../../data/multiplex/extracted/"};


string getTimestamp(){
    timeval curTime;
    gettimeofday(&curTime, NULL);
    int milli = curTime.tv_usec / 1000;
    char buffer [80];
    strftime(buffer, 80, "%Y-%m-%d_%H:%M:%S", localtime(&curTime.tv_sec));
    char currentTime[84] = "";
    sprintf(currentTime, "%s:%03d", buffer, milli);
    return currentTime;
}

void read_directory(string &name, vector<string>& v){
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        if(strcmp(dp -> d_name, ".") && strcmp(dp -> d_name, "..")){
            string file_path = dp->d_name;
            v.push_back(file_path);
        }
    }
    closedir(dirp);
}


bool dir_exists(string &path)
{
    struct stat info;

    if(stat( path.c_str(), &info ) != 0)
        return false;
    else if(info.st_mode & S_IFDIR)
        return true;
    else
        return false;
}


void create_dir(string &path){
    mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}


string get_log_file(string &base){
    string res_path = base + "/" + RES_DIR;
    string res_sim_path = res_path + SIM_DIR;
    string res_sim_log_path = res_sim_path + LOG_DIR;
    if(!dir_exists(res_path)){
        create_dir(res_path);
    }
    if(!dir_exists(res_sim_path)){
        create_dir(res_sim_path);
    }
    if(!dir_exists(res_sim_log_path)){
        create_dir(res_sim_log_path);
    }
    return res_sim_log_path + getTimestamp() + ".sim.log";
}

void write_log(string &log_file, string log_message) {
    ofstream out(log_file, ofstream::app);
    out << getTimestamp() + " - " + log_message << endl;
    out.close();
}

/**
 * Output format:
 * <number_of_nodes> <sum_of_nodes_for_each_layer>
 * <nodes_infected_by_0>
 * <nodes_infected_by_1>
 * <nodes_infected_by_2>
 * ...
 * <nodes_infected_by_n>
 */
void write_simulation_results(int total_nodes, vector<int> &sp, string &base, string &network_name, string lambda_coeff, int i){
    
    string timestamp = getTimestamp() + "#" + to_string(i);
    // printf("current time: %s \n", currentTime);

    string res_path = base + "/" + RES_DIR;
    string res_sim_path = res_path + SIM_DIR;
    string res_sim_net_path = res_sim_path + network_name + "/";
    string res_sim_net_lambda_path = res_sim_net_path + lambda_coeff + "lambda/";
    
    if(!dir_exists(res_path)){
        create_dir(res_path);
    }
    if(!dir_exists(res_sim_path)){
        create_dir(res_sim_path);
    }
    if(!dir_exists(res_sim_net_path)){
        create_dir(res_sim_net_path);
    }
    if(!dir_exists(res_sim_net_lambda_path)){
        create_dir(res_sim_net_lambda_path);
    }
    ofstream out(res_sim_net_lambda_path + timestamp + ".sim");

    out << sp.size() << " " << total_nodes << endl;

    for(double x : sp)
        out << x << endl;
    
    out.close();
}

void write_algorithm_results(vector<int> &score, string alg_name, string &base, string &network_name){
    
    string res_path = base + "/" + RES_DIR;
    string res_alg_path = res_path + ALG_DIR;
    string res_alg_net_path = res_alg_path + network_name + "/";
    
    if(!dir_exists(res_path)){
        create_dir(res_path);
    }
    if(!dir_exists(res_alg_path)){
        create_dir(res_alg_path);
    }
    if(!dir_exists(res_alg_net_path)){
        create_dir(res_alg_net_path);
    }

    ofstream out(res_alg_net_path + alg_name + ".alg");

    out << "i " << score.size() << endl;

    for(int x : score)
        out << x << endl;
    
    out.close();
}


void write_algorithm_results(vector<double> &score, string alg_name, string &base, string &network_name){
    
    string res_path = base + "/" + RES_DIR;
    string res_alg_path = res_path + ALG_DIR;
    string res_alg_net_path = res_alg_path + network_name + "/";
    
    if(!dir_exists(res_path)){
        create_dir(res_path);
    }
    if(!dir_exists(res_alg_path)){
        create_dir(res_alg_path);
    }
    if(!dir_exists(res_alg_net_path)){
        create_dir(res_alg_net_path);
    }

    ofstream out(res_alg_net_path + alg_name + ".alg");

    out << "d " << score.size() << endl;

    for(double x : score)
        out << x << endl;
    
    out.close();
}



string get_network_name(string &network_path){
    string network_name = network_path.substr(network_path.find_last_of("/") + 1, 
        string::npos);
    return network_name.substr(0, network_name.rfind(".edges"));
}
