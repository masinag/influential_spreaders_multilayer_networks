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
        int i = 0;
        for (string &dataset: data_dirs){
            string path = base + "/" + dataset;
            read_directory(path, files);
            for(; i < files.size(); i++){
                files[i] = path + files[i]; 
            }
        }
    } else {
        files.push_back (argv[1]);
    }


    for (string& network_path: files){
        string network_name = get_network_name(network_path);
        cerr << getTimestamp() << " - " << "Analyzing " << network_name << endl;
        cerr << network_path << endl;
        MultilayerNetwork m = readMultilayer(network_path);

        MultilayerNetwork mt(m.layers(), m.nodes());
        m.transpose(mt);
        Graph g = m.getAggregate();
        Graph gt(g.size());
        g.transpose(gt);


        // algorithms on aggregate graph
        cerr << getTimestamp() << " - " << "\tComputing aggCore" << endl;
        vector<int> score_i = fast_k_core(g); // aggCore 
        write_algorithm_results(score_i, "aggCore", base, network_name);

        // --- transposed
        cerr << getTimestamp() << " - " << "\tComputing aggCore_T" << endl;
        score_i = fast_k_core(gt); // aggCore 
        write_algorithm_results(score_i, "aggCore_T", base, network_name);

        cerr << getTimestamp() << " - " << "\tComputing aggDeg" << endl;
        score_i = degree(g); // aggDeg 
        write_algorithm_results(score_i, "aggDeg", base, network_name);

        cerr << getTimestamp() << " - " << "\tComputing aggPR" << endl;
        vector<double> score_d = pageRank(g); // aggPR
        write_algorithm_results(score_d, "aggPR", base, network_name);

        // --- transposed
        cerr << getTimestamp() << " - " << "\tComputing aggPR_T" << endl;
        score_d = pageRank(gt); // aggPR
        write_algorithm_results(score_d, "aggPR_T", base, network_name);



        // additive algorithms 
        cerr << getTimestamp() << " - " << "\tComputing addPR" << endl;
        score_d = additivePageRank(m); // addPR
        write_algorithm_results(score_d, "addPR", base, network_name);

        // --- transposed

        cerr << getTimestamp() << " - " << "\tComputing addPR_T" << endl;
        score_d = additivePageRank(mt); // addPR
        write_algorithm_results(score_d, "addPR_T", base, network_name);

        cerr << getTimestamp() << " - " << "\tComputing sumCore" << endl;
        score_i = sumCore(m); // sumCore 
        write_algorithm_results(score_i, "sumCore", base, network_name);

        // --- transposed

        cerr << getTimestamp() << " - " << "\tComputing sumCore_T" << endl;
        score_i = sumCore(mt); // sumCore 
        write_algorithm_results(score_i, "sumCore_T", base, network_name);

        // multilayer algorithms
        cerr << getTimestamp() << " - " << "\tComputing mlPCI" << endl;
        score_i = mlPCI(m); // mlPCI
        write_algorithm_results(score_i, "mlPCI", base, network_name);

        cerr << getTimestamp() << " - " << "\tComputing alPCI" << endl;
        score_i = alPCI(m); // alPCI
        write_algorithm_results(score_i, "alPCI", base, network_name);

        cerr << getTimestamp() << " - " << "\tComputing laPCI" << endl;
        score_i = laPCI(m); // laPCI
        write_algorithm_results(score_i, "laPCI", base, network_name);

        cerr << getTimestamp() << " - " << "\tComputing lsPCI" << endl;
        score_i = lsPCI(m); // lsPCI
        write_algorithm_results(score_i, "lsPCI", base, network_name);

        cerr << getTimestamp() << " - " << "\tComputing multiCore" << endl;
        score_i = multiCore(m); // multiCore
        write_algorithm_results(score_i, "multiCore", base, network_name);

        // --- transposed
        cerr << getTimestamp() << " - " << "\tComputing multiCore_T" << endl;
        score_i = multiCore(mt); // multiCore
        write_algorithm_results(score_i, "multiCore_T", base, network_name);

        
        cerr << getTimestamp() << " - " << "\tComputing verBC" << endl;
        score_d = verBetweennessCentrality(m); // verBC
        write_algorithm_results(score_d, "verBC", base, network_name);
        
        cerr << getTimestamp() << " - " << "\tComputing verPR" << endl;
        score_d = verPageRank(m); // verPR
        write_algorithm_results(score_d, "verPR", base, network_name);

        // --- transposed

        cerr << getTimestamp() << " - " << "\tComputing verPR_T" << endl;
        score_d = verPageRank(mt); // verPR
        write_algorithm_results(score_d, "verPR_T", base, network_name);


    }
    return 0;
}
