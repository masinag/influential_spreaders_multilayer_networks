import os
from os.path import isfile
from itertools import combinations
import sys
from data_structures import Multiplex

DATA_DIR = "../data/multiplex/"
EXTRACTED_DIR = "../data/extracted/"

dd = {f'{DATA_DIR}SacchPomb_Multiplex_Genetic' : {'N' : 875, 'E': 18214, 'L' : 3},
      f'{DATA_DIR}Drosophila_Multiplex_Genetic' : {'N' : 1364, 'E': 7267, 'L' : 2},
      f'{DATA_DIR}SacchCere_Multiplex_Genetic' : {'N' : 3096, 'E': 185849, 'L' : 5},
      f'{DATA_DIR}Homo_Multiplex_Genetic' : {'N' : 3859, 'E': 77483, 'L' : 3},
      f'{DATA_DIR}NYClimateMarch2014_Multiplex_Social' : {'N' : 4150, 'E': 45334, 'L' : 3},
      f'{DATA_DIR}MoscowAthletics2013_Multiplex_Social' : {'N' : 4370, 'E': 33411, 'L' : 3}}


    
def read_multiplex(edges):
        res = Multiplex()
        with open(edges) as ef:
            for row in ef:
                if not row.startswith("#"):
                    l, a, b, _ = map(int, row.split())
                    res.add_edge(a, b, l)
        return res

def extract_multiplex(dir, g, nn, combo):
        """
        Extracts a part of network g where the layers are only those in
        combo and every node has a counterpart in all layers
        """
        # find a subgraph where 
        ng = g.crop(nn, combo)   
        found = ng.nodes() < g.nodes()
        g = ng        
        while found:
            nn = ng.nodes_in_combo(combo)
            ng = g.crop(nn, combo)
            found = ng.nodes() < g.nodes()
            g = ng
        
        # exclude the nodes that don't belong to the biggest connected 
        # component of the multileayer
        i, cc, count = g.agg_cc()
        max_cc = 0
        for j in range(1, i):
            if count[j] > count[max_cc]:
                max_cc = j
        useful_nodes = [j for j, k in cc.items() if k == max_cc]
        g = g.crop(useful_nodes, combo)

        return g


def extract_dataset(dir, name, edges):

    g = read_multiplex(edges)

    L, N, E = dd[dir]['L'], dd[dir]['N'], dd[dir]['E']
    #find a combo of layers
    for combo in combinations([i+1 for i in range(g.layers())], L):
        nn = g.nodes_in_combo(combo)
        if len(nn) >= N:
            # print(list(combo), len(nn), N)
            break

    g = extract_multiplex(dir, g, nn, combo)
    write_multiplex(g, DATA_DIR + EXTRACTED_DIR + name)
    print('Extracted: ' + DATA_DIR + EXTRACTED_DIR + name)
    print('Initial nodes: %d' % g.nodes())
    print('Initial edges: %d' % g.edges())
    print('Nodes extracted: (%d - expected %d)' % (g.nodes(), N))
    print('Edges extracted: (%d - expected %d)\n' % (g.edges(), E))


def write_multiplex(g, file_name):
    layer_i = {l : i for i, l in enumerate(g.net)}
    node_i = {n : i for i, n in enumerate(g.nn)}
    with open(file_name, 'w+') as f:
        f.write(f'{g.layers()} {g.nodes()} {g.edges()}\n')
        for l in g.net:
            for n, vv in g.net[l].items():
                node = node_i[n]
                layer = layer_i[l]
                # a node is connected to its counterparts in all layers
                for j in g.net:
                    layer_dest = layer_i[j]
                    if not layer_dest == layer:
                        f.write(f'{node} {layer} {node} {layer_dest}\n')
                for v in vv:
                    f.write(f'{node} {layer} {node_i[v]} {layer}\n')
        
def main():
    dirs = ([element for element in os.listdir(DATA_DIR) if not isfile(element)])
    for dir in dirs:
        if not dir == EXTRACTED_DIR.rstrip('/'):
            edges, name = None, None
            for f in os.listdir(DATA_DIR + dir + "/Dataset"):
                if f.endswith(".edges"):
                    edges = DATA_DIR + dir + "/Dataset/" + f
                    name = f
            extract_dataset(DATA_DIR + dir, name, edges)
        

if __name__ == "__main__":
    main()
        
