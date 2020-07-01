class G:
    def __init__(self):
        self.g = {}
    
    def add_edge(self, a, b):
        if not a in self.g:
            self.g[a] = set()
        self.g[a].add(b)
    
    def nodes(self):
        return set(self.g.keys())
    def adj(self, n):
        return self.g[n]
def read_layers(path):
    
    with open(path) as f:
        l, n, m = map(int, f.readline().split())
        ll = [G() for i in range(l)]
        for r in f:
            a, la, b, lb = map(int, r.split())
            if la == lb:
                ll[la].add_edge(a, b)
    return ll

def compare(g1, g2):
    assert(g1.nodes() == g2.nodes())
    for n in g1.nodes():
        assert(g1.adj(n) == g2.adj(n))

l1 = read_layers('SLN_2_0.8_0.8_0.8.edges')
l2 = read_layers('SLN_2_0.8_0.8_0.3.edges')


assert(len(l1) == len(l2))

for i in range(len(l1)):
    compare(l1[i], l2[i])