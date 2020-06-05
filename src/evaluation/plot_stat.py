import matplotlib.pyplot as plt
import os
RANKING_DIR = '../../results/rankings/'

def show_scores(nets_cat, nets, net_scores, alg_names, rows, cols):
    fig, axs = plt.subplots(rows, cols, figsize=(15,15))
    fig.tight_layout(pad=6.0)
    
    axs = axs.flatten()

    for i, net in enumerate(nets):
        alg_names.sort(key = lambda x : net_scores[net][x], reverse=True)
        scores = [net_scores[net][alg] for alg in alg_names]
        axs[i].bar(range(len(scores)), scores, align ='center', tick_label=alg_names)
        plt.setp(axs[i].get_xticklabels(), rotation=90, horizontalalignment='right')
        axs[i].set_title(net)
        
    plt.savefig(RANKING_DIR + nets_cat)
    
    

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
