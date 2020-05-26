from collections import deque

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

    def adj(self, n):
        return self.g[n]
    
    def nodes(self):
        return len(self.g)

    def bfs_cc(self, ccv, count, n, i):
        q = deque([n])
        while q:
            e = q.popleft()
            count[i] += 1
            ccv[e] = i
            for v in self.adj(e):
                if ccv[v] == -1:
                    q.append(v)

    def cc(self):
        i = 0
        ccv = {n: -1 for n in self.g}
        count = []
        for n in self.g:
            if ccv[n] == -1:
                count.append(0)
                self.bfs_cc(ccv, count, n, i)
                i += 1
        return i, ccv, count

    
    
class Multiplex:
    def __init__(self):
        self.net = {}
        self.nn = set()

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
        """
        Return a new Multiplex which is a subnetwork of self,
        where the nodes are only those in nn
        and the layers are only those in combo
        """
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

class Multilayer:
    def __init__(self, nodes, layers):
        self.n = [ [ set() for layer in range(layers)] for node in range(nodes)]
    def add_edge(self, a, la, b, lb):
        if not (b, lb) in self.n[a][la]:
            self.n[a][la].add((b, lb))
            return True
        return False
    def nodes(self):
        return len(self.n)
    def layers(self):
        return len(self.n[0])
    def edges(self):
        return sum((len(node_layer_adj) for node_adj in self.n for node_layer_adj in node_adj))
    def adj(self, node, layer):
        return self.n[node][layer]
