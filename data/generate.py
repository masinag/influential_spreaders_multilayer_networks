import random 
import bisect 
import math 
from functools import reduce
from multilayer import Multilayer, save_stats
DATA_DIR = 'multilayer/'
GENERATE_DIR = 'generated/'

class ZipfGenerator: 
    def __init__(self, n, s): 
        tmp = [1. / (math.pow(float(i), s)) for i in range(1, n+1)] 
        zeta = reduce(lambda sums, x: sums + [sums[-1] + x], tmp, [0]) 
        self.distMap = [x / zeta[-1] for x in zeta] 

    def next(self): 
        u = random.random()  
        # return the position of u in the sorted list
        return bisect.bisect(self.distMap, u) - 1

class Graph:
    def __init__(self, nodes):
        self.g = [[] for node in range(nodes)]
    def add_edge(self, a, b):
        self.g[a].append(b)
    def nodes(self):
        return len(self.g)
    def adj(self, n):
        return self.g[n]

def read_graph(file_name):
    nn = {}
    count = 0
    with open(DATA_DIR + file_name, 'r') as f:
        for row in f:
            if row.startswith('#'):
                if row.startswith('# Nodes'):
                    nodes = int(row.split()[2])
                    g = Graph(nodes)
            else:
                a, b = map(int, row.split())
                if a not in nn:
                    nn[a] = count
                    count += 1
                if b not in nn:
                    nn[b] = count
                    count += 1
                a, b = nn[a], nn[b]

                g.add_edge(a, b)
    return g

def generate_multilayer(files, d, s_degree, s_layer, s_node):
    layers = [read_graph(file_name) for file_name in files]
    total_nodes = sum((g.nodes() for g in layers))
    max_interconnections = int(d * math.log2(total_nodes))
    
    degree_generator = ZipfGenerator(max_interconnections, s_degree)
    layer_generator = ZipfGenerator(len(layers), s_layer)
    node_generators = [ZipfGenerator(g.nodes(), s_node) for g in layers]

    m = Multilayer(max((g.nodes() for g in layers)), len(layers))
    l_index = list(range(m.layers()))
    n_index = [list(range(layers[i].nodes())) for i in l_index]

    random.shuffle(l_index)
    for n_l_index in n_index:
        random.shuffle(n_l_index)

    for l in range(len(layers)):
        for n in range(layers[l].nodes()):
            # intra-connections
            for v in layers[l].adj(n):
                m.add_edge(n, l, v, l)
            # generate inter-connections
            degree = degree_generator.next()
            for _ in range(degree):
                added = False
                while not added :
                    l_dest = l_index[layer_generator.next()]
                    while l_dest == l:
                        l_dest = l_index[layer_generator.next()]
                        
                    n_dest = n_index[l_dest][node_generators[l_dest].next()]
                    added = m.add_edge(n, l, n_dest, l_dest)
    return m



def write_multilayer(m, output_name):
    with open(DATA_DIR + GENERATE_DIR + output_name, 'w+') as f:
        f.write(f"{m.layers()} {m.nodes()} {m.edges()}\n")
        for node in range(m.nodes()):
            for layer in range(m.layers()):
                for neigh, neigh_layer in m.adj(node, layer):
                    f.write(f"{node} {layer} {neigh} {neigh_layer}\n")


if __name__ == "__main__":
    SLN_files = ['p2p-Gnutella04.txt', 'p2p-Gnutella05.txt', 'p2p-Gnutella06.txt', 'p2p-Gnutella08.txt']
    DLN_files = ['Wiki-Vote.txt', 'Cit-HepTh.txt', 'p2p-Gnutella04.txt']
    networks = {'SLN' : SLN_files}
    dd = [1, 2, 3, 4]
    ss = [0.3, 0.8]

    for name, files in networks.items():
        for d in dd:
            for s_degree in ss:
                for s_layer in ss:
                    for s_node in ss:
                        m = generate_multilayer(files, d, s_degree, s_layer, s_node)

                        output_name = f"{name}_{d}_{s_degree}_{s_layer}_{s_node}"
                        write_multilayer(m, output_name + ".edges")
                        save_stats(m, output_name)
