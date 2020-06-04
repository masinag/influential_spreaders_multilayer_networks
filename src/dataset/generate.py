import random 
import bisect 
import math 
from functools import reduce
from stats_multilayer import save_stats
from data_structures import Graph, Multilayer

DATA_DIR = '../data/multilayer/'
GENERATE_DIR = '../data/generated/'

class ZipfGenerator: 
    def __init__(self, n, s): 
        tmp = [1. / (math.pow(float(i), s)) for i in range(1, n+1)] 
        zeta = reduce(lambda sums, x: sums + [sums[-1] + x], tmp, [0]) 
        self.distMap = [x / zeta[-1] for x in zeta] 

    def next(self): 
        u = random.random()  
        # return the position of u in the sorted list
        return bisect.bisect(self.distMap, u) - 1


def read_graph(file_name):
    nn = {}
    count = 0
    g = Graph()

    with open(DATA_DIR + file_name, 'r') as f:
        for row in f:
            if not row.startswith('#'):
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

def read_layers(files):
    return [read_graph(file_name) for file_name in files]

def generate_multilayer(layers, l_index, n_index, d, s_degree, s_layer, s_node):
    total_nodes = sum((g.nodes() for g in layers))
    max_interconnections = int(d * math.log2(total_nodes))
    print('#', int(d * math.log2(total_nodes)))
    
    degree_generator = ZipfGenerator(max_interconnections, s_degree)
    layer_generator = ZipfGenerator(len(layers), s_layer)
    node_generators = [ZipfGenerator(g.nodes(), s_node) for g in layers]

    m = Multilayer(max((g.nodes() for g in layers)), len(layers))

    degrees = []
    for l in range(len(layers)):
        for n in range(layers[l].nodes()):
            # intra-connections
            for v in layers[l].adj(n):
                m.add_edge(n, l, v, l)
            # inter-connections with other counterparts
            for j in range(len(layers)):
                if j != l and n in layers[j].nodes_set():
                    m.add_edge(n, l, n, j)
            # generate inter-connections
            degree = degree_generator.next()
            degrees.append(degree)
            for _ in range(degree):
                added = False
                while not added :
                    l_dest = l_index[layer_generator.next()]
                    while l_dest == l:
                        l_dest = l_index[layer_generator.next()]
                        
                    n_dest = n_index[l_dest][node_generators[l_dest].next()]
                    added = m.add_edge(n, l, n_dest, l_dest)
    print('>', max(degrees))
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
    networks = {'SLN' : SLN_files, 'DLN' : DLN_files}
    # dd = list(range(1, 5))
    dd = [2]
    ss = [0.3, 0.8]

    for name, files in networks.items():
        layers = read_layers(files)
        l_index = list(range(len(layers)))
        n_index = [list(range(layers[i].nodes())) for i in l_index]

        random.shuffle(l_index)
        for n_l_index in n_index:
            random.shuffle(n_l_index)

        for d in dd:
            for s_degree in ss:
                for s_layer in ss:
                    for s_node in ss:
                        m = generate_multilayer(layers, l_index, n_index, d, s_degree, s_layer, s_node)

                        output_name = f"{name}_{d}_{s_degree}_{s_layer}_{s_node}"
                        write_multilayer(m, f'{output_name}.edges')
                        print(f'Generated {output_name}.edges')
                        save_stats(m, output_name)
