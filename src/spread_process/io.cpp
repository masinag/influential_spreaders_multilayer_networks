

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

#define SIM_DIR "../simulations/"
#define LOG_DIR "logs/"

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
            string file_path = name + dp->d_name;
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
    string sim_path = base + "/" + SIM_DIR;
    string log_sim_path = sim_path + LOG_DIR;
    if(!dir_exists(sim_path)){
        create_dir(sim_path);
    }
    if(!dir_exists(log_sim_path)){
        create_dir(log_sim_path);
    }
    return log_sim_path + getTimestamp() + ".sim.log";
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

    string sim_path = base + "/" + SIM_DIR;
    string net_sim_path = sim_path + network_name + "/";
    string net_sim_lambda_path = net_sim_path + lambda_coeff + "lambda" + "/";
    if(!dir_exists(sim_path)){
        create_dir(sim_path);
    }
    if(!dir_exists(net_sim_path)){
        create_dir(net_sim_path);
    }
    if(!dir_exists(net_sim_lambda_path)){
        create_dir(net_sim_lambda_path);
    }

    ofstream out(net_sim_lambda_path + timestamp + ".sim");

    out << sp.size() << " " << total_nodes << endl;

    for(double x : sp)
        out << x << endl;
    
    out.close();
}
