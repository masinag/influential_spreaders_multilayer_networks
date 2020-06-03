import matplotlib.pyplot as plt
from pathlib import Path

IMG_DIR = 'multilayer/plots/'

def save_plot(values, name, output_name):
    count = {}
    for v in values:
        count[v] = count[v] + 1 if v in count else 1
    x = list(range(min(count.keys()), max(count.keys()) + 1))
    y = [count[i] if i in count else 0 for i in x]
    plt.clf()
    plt.title(name)
    plt.plot(x, y)
    Path(IMG_DIR + output_name).mkdir(parents=True, exist_ok=True)

    plt.savefig(IMG_DIR + output_name + '/' + name + '.svg')

def save_hist(values, name, output_name):
    plt.clf()
    plt.title(name)
    plt.hist(values)
    Path(IMG_DIR + output_name).mkdir(parents=True, exist_ok=True)
    plt.savefig(IMG_DIR + output_name + '/' + name + '.svg')


def save_stats(m, output_name):
    intra_in_deg = [0 for l in range(m.layers() * m.nodes())]
    inter_in_deg = [0 for l in range(m.layers() * m.nodes())]
    intra_out_deg = [0 for l in range(m.layers() * m.nodes())]
    inter_out_deg = [0 for l in range(m.layers() * m.nodes())]

    sum_intra_in_deg =  [0 for n in range(m.nodes())]
    sum_inter_in_deg =  [0 for n in range(m.nodes())]
    sum_intra_out_deg = [0 for n in range(m.nodes())]
    sum_inter_out_deg = [0 for n in range(m.nodes())]

    layer_in_deg = []
    layer_out_deg = []

    for n in range(m.nodes()):
        for l in range(m.layers()):
            for neigh, neigh_layer in m.adj(n, l):
                if l == neigh_layer: # intra-edge
                    intra_in_deg[neigh * m.layers() + neigh_layer] += 1
                    intra_out_deg[n * m.layers() + l] += 1
                    sum_intra_in_deg[neigh] += 1
                    sum_intra_out_deg[neigh] += 1
                else:
                    inter_in_deg[neigh * m.layers() + neigh_layer] += 1
                    inter_out_deg[n * m.layers() + l] += 1
                    sum_inter_in_deg[neigh] += 1
                    sum_inter_out_deg[n] += 1
                    layer_in_deg.append(neigh_layer)
                    layer_out_deg.append(l)
    
    save_plot(intra_in_deg, 'intra_in_deg', output_name)
    save_plot(inter_in_deg, 'inter_in_deg', output_name)
    save_plot(intra_out_deg, 'intra_out_deg', output_name)
    save_plot(inter_out_deg, 'inter_out_deg', output_name)
    save_plot(sum_intra_in_deg, 'sum_intra_in_deg', output_name)
    save_plot(sum_inter_in_deg, 'sum_inter_in_deg', output_name)
    save_plot(sum_intra_out_deg, 'sum_intra_out_deg', output_name)
    save_plot(sum_inter_out_deg, 'sum_inter_out_deg', output_name)
    save_hist(layer_in_deg, 'layer_in_deg', output_name)
    save_hist(layer_out_deg, 'layer_out_deg', output_name)
    

    

