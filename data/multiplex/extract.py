import os
from os.path import isfile

EXTRACTED_DIR = "extracted"

# def add_layer(node_layers, node, layer):
#     if node in node_layers:
#         node_layers[node].add(layer)
#     else:
#         node_layers[node] = set([layer])

def extract_dataset(name, edges):
    # extract only the nodes present in all layers
    # node_layers = {}
    layers = set()
    nodes = set()
    edges_count = 0
    with open(edges) as ef:
        for row in ef:
            if not row.startswith("#"):
                layer, a, b, _ = map(int, row.split())
    #             add_layer(node_layers, a, layer)
    #             add_layer(node_layers, b, layer)
                layers.add(layer)
                nodes.add(a)
                nodes.add(b)
                edges_count += 1
    # # keep only the nodes present in all layers and re-name them
    # new_id = {}
    # new_nodes_count = 0
    # for node, nlayers in node_layers.items():
    #     if len(nlayers) == len(layers):
    #         new_id[node] = new_nodes_count
    #         new_nodes_count += 1
    with open(edges, 'r') as ef, open(EXTRACTED_DIR + "/" + name, 'w+') as extracted:
        extracted.write("%d %d %d\n" % (len(layers), len(nodes), edges_count))
        for row in ef:
            if not row.startswith("#"):
                layer, a, b, _ = map(int, row.split())
                # make indexes start from 0
                extracted.write("%d %d %d\n" % (layer-1, a-1, b-1))

        
def main():
    dirs = ([element for element in os.listdir() if not isfile(element)])
    for dir in dirs:
        if not dir == EXTRACTED_DIR:
            edges, name = None, None
            for f in os.listdir(dir + "/Dataset"):
                if f.endswith(".edges"):
                    edges = dir + "/Dataset/" + f
                    name = f
            extract_dataset(name, edges)

if __name__ == "__main__":
    main()
        
