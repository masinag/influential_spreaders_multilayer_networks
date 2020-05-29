from ranking import kendallsTau
import os
DATASETS_DIRS = ['../../data/multiplex/extracted/', '../data/multilayer/generated']

SIMULATIONS_DIR = '../simulations/'

ALGORITHMS_RANKINGS_DIR = ['../rankings/']


ALGORITHMS = ['addPageRank', 'verPageRank', 'laPCI', 'mlPCI', 'lsPCI', 'aggPageRank', 
        'multiCore', 'sumCore', 'aggCore', 'alPCI', 'aggDegree', 'verBetweenness']

def read_simulations_output(net):
    return {}

def read_algorithm_output(algorithm, net):
    return []

def write_result(net, algorithm, kt):
    pass

if __name__ == "__main__":
    # for each dataset output the kendall's Tau
    for dir in DATASETS_DIRS:
        for net in os.listdir(dir):
            # dictionary with different spreading powers
            simulations_ranking = read_simulations_output(net)
            for algorithm in ALGORITHMS:
                algorithm_ranking = read_algorithm_output(algorithm, net)
                kt = {}
                for sp in simulations_ranking:
                    kt[sp] = kendallsTau(simulations_ranking[sp], algorithm_ranking)
                write_result(net, algorithm, kt)


