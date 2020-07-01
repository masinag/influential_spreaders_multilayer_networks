import os
import matplotlib
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
# import matplotlib.pyplot as plt
# sns.set(style="white", context="talk")
RESULT_DIR = '../../results/'
RANKING_DIR = 'rankings/'
sort = False

NET_TYPE_F = 'net_type'
NET_F = 'net'
II_F = 'ii'
IJ_F = 'ij'
ALG_F = 'alg' 
SCORE_F = '${\\tau}$'

def text_height(x):
    return 10 if x >= 0 else -15

def plot_lines(df, net_type, param):
    print(net_type, param)
    print(df.to_dict())
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
    # mm = ['.', 'o', 'v', '^', '<', '>', '8', 's', 'p', 'P', '*', 'h', 'H', 'X', 'D', 'd', 'p', '.']

    sns.relplot(x=param, y=SCORE_F, col=NET_F, hue=ALG_F, data=df, kind='line', 
        legend='full', col_wrap=3, markers=True, palette="tab20")
    plt.title(f'{net_type}')
    # plt.xlabel(param)
    plt.show()


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

def plot_stats(base):
    scores = {} # net_type:...,  Net:...., ii:..., ij,.., Alg:..., Score:...
    rank_dir = base + RESULT_DIR + RANKING_DIR
    nets = os.listdir(rank_dir)
    types = ['sln', 'dln', 'multiplex']
    lambdas = ['ii', 'ij']
    scores = {NET_TYPE_F : [], NET_F : [], II_F : [], IJ_F: [], ALG_F : [], SCORE_F : []}

    for net in nets:
        t = get_type(net)
        for ll in sorted(os.listdir(rank_dir + net)):
            with open(rank_dir + net + '/' + ll) as f:
                for r in f:
                    alg_name, score = r.split()
                    if alg_name.endswith('_T'): continue
                    score = float(score)
                    scores[NET_TYPE_F].append(get_type(net))
                    scores[NET_F].append(net)
                    scores[II_F].append(round(float(get_value(ll, 'ii')) * 10))
                    scores[IJ_F].append(round(float(get_value(ll, 'ij')) * 10))
                    scores[ALG_F].append(alg_name)
                    scores[SCORE_F].append(score)
    data = pd.DataFrame(scores)
    print(data)
    for t in types:
        
        # print(x)
        plot_lines(data.query(f'({NET_TYPE_F} == "{t}") and ({IJ_F} == 10)'), t, II_F)
        plot_lines(data.query(f'({NET_TYPE_F} == "{t}") and ({II_F} == 10)'), t, IJ_F)


if __name__ == "__main__":
    import sys
    base = sys.argv[0]
    base = base[:base.rfind('/') + 1]
    plot_stats(base)
    
