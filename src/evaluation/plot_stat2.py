import os
import matplotlib
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import tikzplotlib
import matplotlib.ticker as tkr


matplotlib.rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
## for Palatino and other serif fonts use:
#rc('font',**{'family':'serif','serif':['Palatino']})
matplotlib.rc('text', usetex=True)
# import matplotlib.pyplot as plt
# sns.set(style="white", context="talk")
RESULT_DIR = '../../results/'
DOC_DIR = '../../doc/'
RANKING_DIR = 'rankings/'
IMG_DIR = 'img/variation/'
sort = False

NET_TYPE_F = 'net_type'
NET_F = 'net'
II_F = 'ii'
IJ_F = 'ij'
ALG_F = 'Algoritmo' 
SCORE_F = 'Kendall\'s ${\\tau}$'

MUX_NAMES = {'drosophila' : 'Drosophila', 
            'homo' : 'Homo', 
            'MoscowAthletics2013' : 'MA2013',
            'NYClimateMarch2014' : 'NYCM2014', 
            'sacchcere' : 'SacchCere', 
            'sacchpomb' : 'SacchPomb'}

matplotlib.use("pgf")
matplotlib.rcParams.update({
    "pgf.texsystem": "pdflatex",
    'font.family': 'serif',
    'text.usetex': True,
    'pgf.rcfonts': False,
})


def text_height(x):
    return 10 if x >= 0 else -15

def get_latex(net_name):
    if net_name.startswith('SLN') or net_name.startswith('DLN'):
        t, d, deg, lay, node = net_name.split('_')
        return "%s$_{%s, %s, %s}$" % (t, deg, lay, node)
    else:
        name = MUX_NAMES[net_name[:net_name.find('_')]]
        return name
def plot_lines(df, net_type, param, palette, markers, base):
    print(net_type, param)
    # print(df.to_dict())
    # new_df = df.groupby([NET_F])
    # fig, axs = plt.subplots(rows, cols, figsize=(20, 10), sharex=True, sharey=False)
    # fig.tight_layout()
      
    # axs = axs.flatten()
    # values = ['1.0', '1.2', '1.4', '1.6']
    # mm = ['.', 'o', 'v', '^', '<', '>', '8', 's', 'p', 'P', '*', 'h', 'H', 'X', 'D', 'd', 'p', '.']
    # data = {}
    # for net in sorted(nets):
    #     pass

    # fig.subplots_adjust(top=0.95, left=0.05, right=0.85, bottom=0.1)

    # handles, labels = axs[0].get_legend_handles_labels()
    # axs[cols-1]
    # .legend(bbox_to_anchor=(1.05, 1.), loc=2, borderaxespad=0.)
    # plt.figure(10, 10)
    
    # sns.relplot(x=param, y=SCORE_F, style=ALG_F,
    #         dashes=False, markers=mm, kind="line", data=df)
    nets = df[NET_F].unique()

    g = sns.relplot(x=param, y=SCORE_F, col=NET_F, hue=ALG_F, data=df, kind='line', style=ALG_F, dashes=False, col_order=sorted(nets),
        legend='full', col_wrap=2, markers=markers, palette=palette, height=3, aspect=1.2, facet_kws={'sharey': True, 'sharex': True})
    g.set_titles("{col_name}")
    g.set_xlabels("$\\lambda_{%s}~/~\\lambda_c$" % (param))
    # xticks = [f'{x//10}.{x%10}' for x in g.get_xticklabels()]
    # g.set_xticklabels(xticks)
    # print([x.get_text() for x in g.axes.flat[-1].get_xticklabels()])
    xticks = []
    for x in g.axes.flat[-1].get_xticklabels():
        n = x.get_text().split('{')[1]
        n = n.split('}')[0]
        n = int(n)
        xticks.append('$\\mathdefault{%d.%d}' % (n // 10, n % 10))
    
    # xticks = [f'$\\mathdefault{x.get_text().split('{')[1]}$' for x in g.axes.flat[-1].get_xticklabels()]
    # print(xticks)
    g.set_xticklabels(xticks)
    
    for ax in g.axes.flatten():
        # ax.set_yticklabels(ax.get_yticklabels(), fontsize=13)
        ax.yaxis.set_major_formatter(tkr.FuncFormatter(lambda x, p: "{:.3f}".format(x)))
        # yticks = []
        # # yticks.append([])
        # for i,l in enumerate(ax.get_yticklabels()):
        #     # old_label = l.get_text()
        #     value = l.get_position()[1]
        #     new_label = '$\\mathdefault{%.3f}$' % (value)
        #     # print(new_label, old_label)
        #     yticks.append(new_label)
        # # print(yticks)
        # ax.set_yticklabels(yticks)
    # g.set(yticklabels = [])
    # print(len(yticks), len(g.axes))
    # for i, ax in enumerate(g.axes):
    #     print(yticks[i])
    #     ax.set_yticklabels(yticks[i])
            # ax.get_yticklabels()[i].set_text(new_label)
        
        # ax.set_yticklabels(yticks)
            # ax.get_yticklabels()[i] = new_text
            # print(new_text)
    # for ax in g.axes:
    #     for l in ax.get_yticklabels():
    #         print(l)
        # print(ax.get_yticklabels())

        # n = x.get_text().split('{')[1]
        # n = n.split('}')[0]
        # n = int(n)
        # xticks.append('$\\mathdefault{%d.%d}' % (n // 10, n % 10))
    # g.set(yticks=[])
    
    
    # plt.title(f'{net_type}')
    # plt.xlabel(param)
    # tikzplotlib.save(f'{base}{DOC_DIR}{IMG_DIR}{net_type}_{param}.tex', flavor="context")
    # plt.show()
    plt.savefig(f'{base}{DOC_DIR}{IMG_DIR}{net_type}_{param}.pgf')


def get_value(name, part):
    ii_coeff, ij_coeff = name.split('ii')
    ij_coeff = ij_coeff.rstrip('ij')
    return ii_coeff if part == 'ii' else ij_coeff

def is_constant(name, part):
    ii_coeff, ij_coeff = name.split('ii')
    ij_coeff = ij_coeff.rstrip('ij')
    return ii_coeff == '1.0' if part == 'ii' else ij_coeff == '1.0'

def get_type(net_name):
    if 'SLN' in net_name: return 'sln'
    elif 'DLN' in net_name: return 'dln'
    else: return 'multiplex'

def get_top_n(filename, n):
    scores = {}
    with open(filename) as f:
        if n < 0: n = len(f)
        for r in f:
            alg_name, score = r.split()
            if alg_name.endswith('_T'): continue
            scores[alg_name] = float(score)
    
    return list(sorted(scores.keys(), key = lambda x : scores[x], reverse=True))[:n]

def plot_stats(base, n):
    scores = {} # net_type:...,  Net:...., ii:..., ij,.., Alg:..., Score:...
    rank_dir = base + RESULT_DIR + RANKING_DIR
    nets = os.listdir(rank_dir)
    types = ['sln', 'dln', 'multiplex']
    lambdas = ['ii', 'ij']
    scores = {NET_TYPE_F : [], NET_F : [], II_F : [], IJ_F: [], ALG_F : [], SCORE_F : []}
    # sns.set(font_scale=2)
    alg_names = set()
    for net in nets:
        t = get_type(net)
        for i, ll in enumerate(sorted(os.listdir(rank_dir + net))):
            if i == 0:
                top_n = get_top_n(rank_dir + net + '/' + ll, n)
                # print("Top n: ", top_n)
            with open(rank_dir + net + '/' + ll) as f:
                for r in f:
                    alg_name, score = r.split()
                    if alg_name.endswith('_T') or alg_name not in top_n: continue
                    alg_names.add(alg_name)
                    # print("Adding", alg_name, "for", net, ll)
                    score = float(score)
                    scores[NET_TYPE_F].append(get_type(net))
                    scores[NET_F].append(get_latex(net))
                    scores[II_F].append(round(float(get_value(ll, 'ii')) * 10))
                    scores[IJ_F].append(round(float(get_value(ll, 'ij')) * 10))
                    scores[ALG_F].append(alg_name)
                    scores[SCORE_F].append(score)
    data = pd.DataFrame(scores)
    palette = list(reversed(sns.color_palette("Blues", 10)))
    markers = ['D', 'o', 'P', 'v', 's', 'X', 'p', '^', 'x', '+', '*']
    my_palette = {}
    my_markers = {}
    for i, alg in enumerate(sorted(alg_names)):
        my_palette[alg] = palette[i]
        my_markers[alg] = markers[i]
    # print(data)
    for t in types:
        
        # print(x)
        plot_lines(data.query(f'({NET_TYPE_F} == "{t}") and ({IJ_F} == 10)'), t, II_F, my_palette, my_markers, base)
        plot_lines(data.query(f'({NET_TYPE_F} == "{t}") and ({II_F} == 10)'), t, IJ_F, my_palette, my_markers, base)


if __name__ == "__main__":
    import sys
    base = sys.argv[0]
    base = base[:base.rfind('/') + 1]
    plot_stats(base, int(sys.argv[1]) if len(sys.argv) > 1 else -1)
    
