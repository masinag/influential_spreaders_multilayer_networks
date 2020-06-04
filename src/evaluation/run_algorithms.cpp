#include <iostream>
#include "../utils/Multilayer.h"
#include "../addPageRank/addPR.h"
#include "../aggCore/aggCore.h"
#include "../aggDegree/aggDeg.h"
#include "../aggPageRank/aggPR.h"
#include "../alPCI/alPCI.h"
#include "../laPCI/laPCI.h"
#include "../lsPCI/lsPCI.h"
#include "../mlPCI/mlPCI.h"
#include "../multiCore/multiCore.h"
#include "../sumCore/sumCore.h"
#include "../verBetweenness/verBC.h"
#include "../verPageRank/verPR.h"
#include "io.h"



int main(int argc, char const *argv[]) {
    vector<string> files;

    string argv_str(argv[0]);
    string base = argv_str.substr(0, argv_str.find_last_of("/"));
    
    if(argc < 2) {
        for (string &dataset: data_dirs){
            string path = base + "/" + dataset;
            read_directory(path, files);
        }
    } else {
        files.push_back (argv[1]);
    }


    for (string& network_path: files){
        string network_name = get_network_name(network_path);
        cerr << "Analyzing " << network_name << endl;
        MultilayerNetwork m = readMultilayer(network_path);
        Graph g = m.getAggregate();

        // algorithms on aggregate graph
        cerr << "\tComputing aggCore" << endl;
        vector<int> score_i = fast_k_core(g); // aggCore 
        write_algorithm_results(score_i, "aggCore", base, network_name);

        cerr << "\tComputing aggDeg" << endl;
        score_i = degree(g); // aggDeg 
        write_algorithm_results(score_i, "aggDeg", base, network_name);

        cerr << "\tComputing aggPR" << endl;
        vector<double> score_d = pageRank(g); // aggPR
        write_algorithm_results(score_d, "aggPR", base, network_name);


        // additive algorithms 
        cerr << "\tComputing addPR" << endl;
        score_d = additivePageRank(m); // addPR
        write_algorithm_results(score_d, "addPR", base, network_name);

        cerr << "\tComputing sumCore" << endl;
        score_i = sumCore(m); // sumCore 
        write_algorithm_results(score_i, "sumCore", base, network_name);


        // multilayer algorithms
        cerr << "\tComputing mlPCI" << endl;
        score_i = mlPCI(m); // mlPCI
        write_algorithm_results(score_i, "mlPCI", base, network_name);

        cerr << "\tComputing alPCI" << endl;
        score_i = alPCI(m); // alPCI
        write_algorithm_results(score_i, "alPCI", base, network_name);

        cerr << "\tComputing laPCI" << endl;
        score_i = laPCI(m); // laPCI
        write_algorithm_results(score_i, "laPCI", base, network_name);

        cerr << "\tComputing lsPCI" << endl;
        score_i = lsPCI(m); // lsPCI
        write_algorithm_results(score_i, "lsPCI", base, network_name);

        cerr << "\tComputing multiCore" << endl;
        score_i = multiCore(m); // multiCore
        write_algorithm_results(score_i, "multiCore", base, network_name);
        
        cerr << "\tComputing verBC" << endl;
        score_d = verBetweennessCentrality(m); // verBC
        write_algorithm_results(score_d, "verBC", base, network_name);
        
        cerr << "\tComputing verPR" << endl;
        score_d = verPageRank(m); // verPR
        write_algorithm_results(score_d, "verPR", base, network_name);


    }
    return 0;
}
