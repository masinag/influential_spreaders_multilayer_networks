import os
from os.path import isfile
from itertools import combinations
import sys
sys.setrecursionlimit(20000)

EXTRACTED_DIR = "extracted"

dd = {'SacchPomb_Multiplex_Genetic' : {'N' : 875, 'E': 18214, 'L' : 3},
      'Drosophila_Multiplex_Genetic' : {'N' : 1364, 'E': 7267, 'L' : 2},
      'SacchCere_Multiplex_Genetic' : {'N' : 3096, 'E': 185849, 'L' : 5},
      'Homo_Multiplex_Genetic' : {'N' : 3859, 'E': 77483, 'L' : 3},
      'NYClimateMarch2014_Multiplex_Social' : {'N' : 4150, 'E': 45334, 'L' : 3},
      'MoscowAthletics2013_Multiplex_Social' : {'N' : 4370, 'E': 33411, 'L' : 3}}

class Graph:
    def __init__(self):
        self.g = {}

    def add_node(self, n):
        if n not in self.g:
            self.g[n] = set()

    def add_edge(self, a, b):
        self.add_node(a)
        self.add_node(b)
        self.g[a].add(b)

    def dfs_cc(self, ccv, count, n, i):
        ccv[n] = i
        count[i] += 1
        for v in self.g[n]:
            if ccv[v] == -1:
                self.dfs_cc(ccv, count, v, i)
        

    def cc(self):
        i = 0
        ccv = {n: -1 for n in self.g}
        count = []
        for n in self.g:
            if ccv[n] == -1:
                count.append(0)
                self.dfs_cc(ccv, count, n, i)
                i += 1
        return i, ccv, count
    
class Multiplex:
    def __init__(self):
        self.net = {}
        self.nn = set()
    
    @staticmethod
    def read(edges):
        res = Multiplex()
        with open(edges) as ef:
            for row in ef:
                if not row.startswith("#"):
                    l, a, b, _ = map(int, row.split())
                    res.add_edge(a, b, l)
        return res

    def add_layer(self, l):
        if l not in self.net:
            self.net[l] = {}
    def add_node(self, n, l):
        self.add_layer(l)
        self.nn.add(n)
        if n not in self.net[l]:
            self.net[l][n] = set()
    def add_edge(self, a, b, l):
        self.add_node(a, l)
        self.add_node(b, l)
        self.net[l][a].add(b)
    
    def layers(self):
        return len(self.net)
    
    def nodes(self):
        return len(self.nn)

    def edges(self):
        return sum(len(vv) for l in self.net for vv in self.net[l].values())

    def nodes_in_combo(self, combo, nodes = None):
        nn = nodes or self.nn.copy()
        for l in combo:
            nn.intersection_update(self.net[l].keys())
        return nn

    def crop(self, nn, combo):
        ng = Multiplex()
        for l in combo:
            for node, vv in self.net[l].items():
                if node in nn:
                    for v in vv:
                        if v in nn:
                            
                            ng.add_edge(node, v, l)
        return ng

    def get_aggregate(self):
        res = Graph()
        for l in self.net:
            for n, vv in self.net[l].items():
                for v in vv:
                    res.add_edge(n, v)
                    res.add_edge(v, n)
        return res

    def agg_cc(self):
        g = self.get_aggregate()
        return g.cc()
        

    @staticmethod
    def extract(dir, g, nn, combo):
        L, N, E = dd[dir]['L'], dd[dir]['N'], dd[dir]['E']
        ng = g.crop(nn, combo)
   
        # print(g.nodes(), '--->', ng.nodes())
        found = ng.nodes() < g.nodes()
        g = ng
                
        while found:
            nn = ng.nodes_in_combo(combo)
            ng = g.crop(nn, combo)
            found = ng.nodes() < g.nodes()
            # print(g.nodes(), '--->', ng.nodes())
            g = ng
        i, cc, count = g.agg_cc()
        max_cc = 0
        for j in range(1, i):
            if count[j] > count[max_cc]:
                max_cc = j
        useful_nodes = [j for j, k in cc.items() if k == max_cc]
        g = g.crop(useful_nodes, combo)
        # print('#####', g.nodes(), '--->', ng.nodes())
        print('Nodes extracted: (%d - expected %d)' % (g.nodes(), N))
        print('Edges extracted: (%d - expected %d)' % (g.edges(), E))
        return g


def extract_dataset(dir, name, edges):
    print(dir)

    g = Multiplex.read(edges)
    print('Initial nodes: %d' % g.nodes())
    print('Initial edges: %d' % g.edges())
                

    L, N = dd[dir]['L'], dd[dir]['N']
    #find a combo of layers
    for combo in combinations([i+1 for i in range(g.layers())], L):
        nn = g.nodes_in_combo(combo)
        if len(nn) >= N:
            print(list(combo), len(nn), N)
            break

    g = Multiplex.extract(dir, g, nn, combo)
    print(g.layers(), L)
    assert(g.layers() == L)
    # cin >> l >> n >> m;
    # MultilayerNetwork res(l, n, m);
    # while (cin >> a >> la >> b >> lb){
    #     res.addEdge(a, la, b, lb);
    # }
    layer_i = {l : i for i, l in enumerate(g.net)}
    node_i = {n : i for i, n in enumerate(g.nn)}
    # print(g.nodes())
    # print(len(node_i))
    with open(EXTRACTED_DIR + '/' + name, 'w+') as f:
        f.write('%d %d %d\n' % (g.layers(), g.nodes(), g.edges()))
        for l in g.net:
            for n, vv in g.net[l].items():
                node = node_i[n]
                layer = layer_i[l]
                for v in vv:
                    f.write('%d %d %d %d\n' % (node, layer, node_i[v], layer))   


    
        
def main():
    dirs = ([element for element in os.listdir() if not isfile(element)])
    for dir in dirs:
        if not dir == EXTRACTED_DIR:
            edges, name = None, None
            for f in os.listdir(dir + "/Dataset"):
                if f.endswith(".edges"):
                    edges = dir + "/Dataset/" + f
                    name = f
            extract_dataset(dir, name, edges)
        

if __name__ == "__main__":
    main()
        
