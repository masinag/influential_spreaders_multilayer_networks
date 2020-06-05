# from ranking import kendallsTau
# from pathlib import Path
# from scipy.stats import kendalltau
# import os


# DATASETS_DIRS = ['../../data/multiplex/extracted/', '../../data/multilayer/generated']

# SIMULATIONS_DIR = '../../results/simulations/'
# ALGORITHMS_DIR = '../../results/algorithms/'
# RANKING_DIR = '../../results/rankings/'

# AVG_FILE = 'avg'

# # ALGORITHMS = ['addPageRank', 'verPageRank', 'laPCI', 'mlPCI', 'lsPCI', 'aggPageRank', 
# #         'multiCore', 'sumCore', 'aggCore', 'alPCI', 'aggDegree', 'verBetweenness']

# def read_alg_scores(net_path):
#     res = {}
#     for alg in os.listdir(net_path):
#         if alg.endswith('.alg'):
#             score = []
#             with open(net_path + '/' + alg) as f:
#                 t, _ = f.readline().split() # ignore header line
#                 type_f = int if t == 'i' else float
#                 for k in f:
#                     score.append(type_f(k))
#             res[alg.rstrip('.alg')] = score 
#     return res

# def compute_avg(path):
#     count = 0
#     score = None
#     for filename in os.listdir(path):
#         if filename.endswith('.sim'):
#             count += 1
#             with open(path + '/' + filename) as f:
#                 num_nodes, _ = map(int, f.readline().split())
#                 score = score or [0 for _ in range(num_nodes)]
#                 for i, k in enumerate(f):
#                     score[i] += int(k)

#     with open(path + '/' + AVG_FILE, 'w+') as f:
#         for s in score:
#             f.write(str(s / count) + "\n")

# def read_sim_scores(path):
#     score = []
#     with open(path + '/' + AVG_FILE) as f:
#         for r in f:
#             score.append(float(r))
#     return score

# def evaluate(sim_score, alg_scores):
#     return {alg_name : float(kendallsTau(alg_score, sim_score)) for alg_name, alg_score in alg_scores.items()}

# def write_rankings(net, lambda_dir, ktt):
#     Path(RANKING_DIR).mkdir(parents=True, exist_ok=True)
#     Path(RANKING_DIR + net).mkdir(parents=True, exist_ok=True)
#     with open(RANKING_DIR + net + '/' + lambda_dir, 'w+') as f:
#         for name, score in ktt.items():
#             f.write("%s %f\n" % (name, score))

# if __name__ == "__main__":
#     # for each dataset output the kendall's Tau
#     for dir in DATASETS_DIRS:
#         for net in os.listdir(dir):
#             net = net.rstrip('.edges')
#             # print("#%s" % net)
#             alg_scores = read_alg_scores(ALGORITHMS_DIR + net)
#             for lambda_dir in os.listdir(SIMULATIONS_DIR + net):
#                 sim_net_lambda_dir = SIMULATIONS_DIR + net + '/' + lambda_dir
#                 if not AVG_FILE in os.listdir(sim_net_lambda_dir):
#                     compute_avg(sim_net_lambda_dir)
#                 sim_scores = read_sim_scores(sim_net_lambda_dir)
#                 ktt = evaluate(sim_scores, alg_scores)
#                 write_rankings(net, lambda_dir, ktt)
#             # # dictionary with different spreading powers
#             # simulations_ranking = read_simulations_output(net)
#             # for algorithm in ALGORITHMS:
#             #     algorithm_ranking = read_algorithm_output(algorithm, net)
#             #     kt = {}
#             #     for sp in simulations_ranking:
#             #         kt[sp] = kendallsTau(simulations_ranking[sp], algorithm_ranking)
#             #     write_result(net, algorithm, kt)


