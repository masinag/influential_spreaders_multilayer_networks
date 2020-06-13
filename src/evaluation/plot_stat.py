import os
import matplotlib.pyplot as plt
import seaborn as sns
# import matplotlib.pyplot as plt
# sns.set(style="white", context="talk")
RESULT_DIR = '../../results/'
RANKING_DIR = 'rankings/'

sort = False

def text_height(x):
    return 10 if x >= 0 else -15

def show_scores(nets_cat, nets, net_scores, alg_names, rows, cols, palette_dict, sort=True):
    fig, axs = plt.subplots(rows, cols, figsize=(30,25), sharex=True, sharey=True)
    fig.tight_layout()
      
    axs = axs.flatten()

    for i, net in enumerate(sorted(nets)):
        if sort:
            alg_names.sort(key = lambda x : net_scores[net][x], reverse=True)
        palette = [palette_dict[alg] for alg in alg_names]
        scores = [net_scores[net][alg] for alg in alg_names]
        g = sns.barplot(x=alg_names, y=scores, ax=axs[i], palette=palette)
        for p in g.patches:
             g.annotate("%.2f" % p.get_height(), (p.get_x() + p.get_width() / 2., p.get_height()),
                 ha='center', va='center', fontsize=18, color='black', xytext=(0, text_height(p.get_height())),
                 textcoords='offset points')
        # barlist = axs[i].bar(range(len(scores)), scores, align ='center', tick_label=alg_names, color='tab:green')
        plt.setp(axs[i].get_xticklabels(), rotation=90, horizontalalignment='center')
        axs[i].set_ylim(-1, 1)
        if (i % cols == 0):
            axs[i].set_ylabel('${\\tau}$')
        
        # barlist[0].set_color('r')
        axs[i].set_title(net)
        
    plt.savefig(RESULT_DIR + nets_cat + '10.svg', bbox_inches='tight')
    # plt.show()
    

if __name__ == "__main__":
    scores = {} # lambda : net : alg : score
    nets = os.listdir(RESULT_DIR + RANKING_DIR)
    #plot (net, (alg, score))
    alg_names = set()
    for net in nets:
        for l in os.listdir(RESULT_DIR + RANKING_DIR + net):
            if not l in scores:
                scores[l] = {}
            scores[l][net] = {}
            with open(RESULT_DIR + RANKING_DIR + net + '/' + l) as f:
                for r in f:
                    alg_name, score = r.split()
                    if not alg_name.endswith('2') and not alg_name.endswith('_'):
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

    # color palette

    sns.set(context="poster", style="whitegrid")
    sns.set_palette('tab20b_r', len(alg_names))
    current_palette = sns.color_palette()
    palette_dict = {alg_names[i] : current_palette[i] for i in range(len(alg_names))}
    
    show_scores('multiplex', mm, net_scores, alg_names, 3, 2, palette_dict, sort)
    show_scores('sln', sln, net_scores, alg_names, 4, 2, palette_dict, sort)
    show_scores('dln', dln, net_scores, alg_names, 4, 2, palette_dict, sort)

    

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


# import numpy as np
# import seaborn as sns
# import matplotlib.pyplot as plt
# sns.set(style="white", context="talk")
# rs = np.random.RandomState(8)

# pp = ['Accent', 'Accent_r', 'Blues', 'Blues_r', 'BrBG', 'BrBG_r', 'BuGn', 'BuGn_r', 'BuPu', 'BuPu_r', 
#  'CMRmap', 'CMRmap_r', 'Dark2', 'Dark2_r', 'GnBu', 'GnBu_r', 'Greens', 'Greens_r', 'Greys', 'Greys_r', 'OrRd', 
#  'OrRd_r', 'Oranges', 'Oranges_r', 'PRGn', 'PRGn_r', 'Paired', 'Paired_r', 'Pastel1', 
#  'Pastel1_r', 'Pastel2', 'Pastel2_r', 'PiYG', 'PiYG_r', 'PuBu', 'PuBuGn', 'PuBuGn_r', 
#  'PuBu_r', 'PuOr', 'PuOr_r', 'PuRd', 'PuRd_r', 'Purples', 'Purples_r', 'RdBu', 'RdBu_r', 
#  'RdGy', 'RdGy_r', 'RdPu', 'RdPu_r', 'RdYlBu', 'RdYlBu_r', 'RdYlGn', 'RdYlGn_r', 'Reds', 
#  'Reds_r', 'Set1', 'Set1_r', 'Set2', 'Set2_r', 'Set3', 'Set3_r', 'Spectral', 'Spectral_r', 
#  'Wistia', 'Wistia_r', 'YlGn', 'YlGnBu', 'YlGnBu_r', 'YlGn_r', 'YlOrBr', 'YlOrBr_r', 'YlOrRd', 
#  'YlOrRd_r', 'afmhot', 'afmhot_r', 'autumn', 'autumn_r', 'binary', 'binary_r', 'bone', 
#  'bone_r', 'brg', 'brg_r', 'bwr', 'bwr_r', 'cividis', 'cividis_r', 'cool', 'cool_r', 'coolwarm', 'coolwarm_r', 'copper', 'copper_r',
#  'cubehelix', 'cubehelix_r', 'flag', 'flag_r', 'gist_earth', 'gist_earth_r', 'gist_gray', 'gist_gray_r', 'gist_heat', 'gist_heat_r', 
#  'gist_ncar', 'gist_ncar_r',
#  'gist_rainbow', 'gist_rainbow_r', 'gist_stern', 'gist_stern_r', 'gist_yarg', 
#  'gist_yarg_r', 'gnuplot', 'gnuplot2', 'gnuplot2_r', 'gnuplot_r', 'gray', 'gray_r',
#  'hot', 'hot_r', 'hsv', 'hsv_r', 'icefire', 'icefire_r', 'inferno', 
#  'inferno_r', 'magma', 'magma_r', 'mako', 'mako_r', 
#  'nipy_spectral', 'nipy_spectral_r', 'ocean', 'ocean_r', 'pink', 'pink_r',
#  'plasma', 'plasma_r', 'prism', 'prism_r', 'rainbow', 'rainbow_r',
#  'rocket', 'rocket_r', 'seismic', 'seismic_r', 'spring', 'spring_r',
#  'summer', 'summer_r', 'tab10', 'tab10_r', 'tab20', 'tab20_r', 'tab20b',
#  'tab20b_r', 'tab20c', 'tab20c_r', 'terrain', 'terrain_r', 'twilight',
#  'twilight_r', 'twilight_shifted', 'twilight_shifted_r', 'viridis', 'viridis_r', 'vlag', 'vlag_r', 'winter', 'winter_r']


# N = 18
# plt.ion()
# # Set up the matplotlib figure
# f, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(7, 5), sharex=True)

# # Generate some sequential data
# x = np.array(list("ABCDEFGHIJKLMNOPQR"))
# y1 = np.arange(1, N + 1)
# # ax = plt.gca()
# # fig = plt.figure(figsize=(7, 5))
# for p in pp:
#     sns.set_palette(p, N)
#     current_palette = sns.color_palette()
#     unique_colors = set()
#     for c in current_palette:
#         unique_colors.add(c)
#     if len(unique_colors) >= N:
#         print(current_palette)
#         sns.barplot(x=x, y=y1, ax=ax1)
#         ax1.axhline(0, color="k", clip_on=False)
#         ax1.set_ylabel("Sequential")
#         plt.savefig(p + '.png')
#         # _ = input("Press [enter] to continue.") # wait for input from the user
#         # plt.close()    # close the figure to show the next one.

# # # Center the data to make it diverging
# # y2 = y1 - 5.5
# # sns.barplot(x=x, y=y2, palette="vlag", ax=ax2)
# # ax2.axhline(0, color="k", clip_on=False)
# # ax2.set_ylabel("Diverging")

# # # Randomly reorder the data to make it qualitative
# # y3 = rs.choice(y1, len(y1), replace=False)
# # sns.barplot(x=x, y=y3, palette="deep", ax=ax3)
# # ax3.axhline(0, color="k", clip_on=False)
# # ax3.set_ylabel("Qualitative")

# # # Finalize the plot
# # sns.despine(bottom=True)
# # plt.setp(f.axes, yticks=[])
# # plt.tight_layout(h_pad=2)
