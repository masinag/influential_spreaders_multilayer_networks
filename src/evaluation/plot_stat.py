import matplotlib.pyplot as plt
import os
from matplotlib import cm
from colorspacious import cspace_converter
RANKING_DIR = '../../results/rankings/'

def show_scores(nets_cat, nets, net_scores, alg_names, rows, cols):
    fig, axs = plt.subplots(rows, cols, figsize=(15,15))
    fig.tight_layout(pad=6.0)
    
    axs = axs.flatten()

    for i, net in enumerate(nets):
        
        alg_names.sort(key = lambda x : net_scores[net][x], reverse=True)
        scores = [net_scores[net][alg] for alg in alg_names]
        barlist = axs[i].bar(range(len(scores)), scores, align ='center', tick_label=alg_names, color='tab:green')
        plt.setp(axs[i].get_xticklabels(), rotation=90, horizontalalignment='right')
        barlist[0].set_color('r')
        axs[i].set_title(net)
        
    # plt.savefig(RANKING_DIR + nets_cat)
    plt.show()
    

if __name__ == "__main__":
    scores = {} # lambda : net : alg : score
    nets = os.listdir(RANKING_DIR)
    #plot (net, (alg, score))
    alg_names = set()
    for net in nets:
        for l in os.listdir(RANKING_DIR + net):
            if not l in scores:
                scores[l] = {}
            scores[l][net] = {}
            with open(RANKING_DIR + net + '/' + l) as f:
                for r in f:
                    alg_name, score = r.split()
                    scores[l][net][alg_name] = float(score)
                    alg_names.add(alg_name)

    net_scores = scores['1.0lambda']

    mm = [net for net in net_scores.keys() if 'multiplex' in net]
    dln = [net for net in net_scores.keys() if net.startswith('DLN')] 
    sln = [net for net in net_scores.keys() if net.startswith('SLN')] 
    alg_names = list(sorted(alg_names))
    alg_colors = {}

    mm.sort()
    sln.sort()
    dln.sort()

    show_scores('multiplex', mm, net_scores, alg_names, 3, 2)
    show_scores('sln', sln, net_scores, alg_names, 4, 2)
    show_scores('dln', dln, net_scores, alg_names, 4, 2)

    

        # for alg, score in net_scores[net].items():
        #     alg_scores[alg].append(score)
    
    # for alg in alg_scores:
    #     plt.plot([i for i in range(len(net_scores))], alg_scores[alg])

    # for i, net in enumerate(sorted(net_scores.keys())):
    #     axs[i].hist([s[i] for alg, s in sorted(alg_scores.items())])
    #     axs[i].set_xlabel(alg_names)


    
    # plt.legend(list(alg_scores.keys()))
    # plt.xlabel(list(sorted(net_scores.keys())))
    # plt.plot(list(net_scores.keys()), alg_scores.items())
    # print(alg_scores)



# sphinx_gallery_thumbnail_number = 2

# import numpy as np
# import matplotlib as mpl
# import matplotlib.pyplot as plt
# from matplotlib import cm
# from colorspacious import cspace_converter
# from collections import OrderedDict

# cmaps = OrderedDict()

# cmaps['Perceptually Uniform Sequential'] = [
#             'viridis', 'plasma', 'inferno', 'magma', 'cividis']

# cmaps['Sequential'] = [
#             'Greys', 'Purples', 'Blues', 'Greens', 'Oranges', 'Reds',
#             'YlOrBr', 'YlOrRd', 'OrRd', 'PuRd', 'RdPu', 'BuPu',
#             'GnBu', 'PuBu', 'YlGnBu', 'PuBuGn', 'BuGn', 'YlGn']


# cmaps['Sequential (2)'] = [
#             'binary', 'gist_yarg', 'gist_gray', 'gray', 'bone', 'pink',
#             'spring', 'summer', 'autumn', 'winter', 'cool', 'Wistia',
#             'hot', 'afmhot', 'gist_heat', 'copper']

# cmaps['Diverging'] = [
#             'PiYG', 'PRGn', 'BrBG', 'PuOr', 'RdGy', 'RdBu',
#             'RdYlBu', 'RdYlGn', 'Spectral', 'coolwarm', 'bwr', 'seismic']
# cmaps['Cyclic'] = ['twilight', 'twilight_shifted', 'hsv']
# cmaps['Qualitative'] = ['Pastel1', 'Pastel2', 'Paired', 'Accent',
#                         'Dark2', 'Set1', 'Set2', 'Set3',
#                         'tab10', 'tab20', 'tab20b', 'tab20c']
# cmaps['Miscellaneous'] = [
#             'flag', 'prism', 'ocean', 'gist_earth', 'terrain', 'gist_stern',
#             'gnuplot', 'gnuplot2', 'CMRmap', 'cubehelix', 'brg',
#             'gist_rainbow', 'rainbow', 'jet', 'nipy_spectral', 'gist_ncar']
# nrows = max(len(cmap_list) for cmap_category, cmap_list in cmaps.items())
# gradient = np.linspace(0, 1, 256)
# gradient = np.vstack((gradient, gradient))


# def plot_color_gradients(cmap_category, cmap_list, nrows):
#     fig, axes = plt.subplots(nrows=nrows)
#     fig.subplots_adjust(top=0.95, bottom=0.01, left=0.2, right=0.99)
#     axes[0].set_title(cmap_category + ' colormaps', fontsize=14)

#     for ax, name in zip(axes, cmap_list):
#         ax.imshow(gradient, aspect='auto', cmap=plt.get_cmap(name))
#         pos = list(ax.get_position().bounds)
#         x_text = pos[0] - 0.01
#         y_text = pos[1] + pos[3]/2.
#         fig.text(x_text, y_text, name, va='center', ha='right', fontsize=10)

#     # Turn off *all* ticks & spines, not just the ones with colormaps.
#     for ax in axes:
#         ax.set_axis_off()


# for cmap_category, cmap_list in cmaps.items():
#     plot_color_gradients(cmap_category, cmap_list, nrows)

# plt.show()
