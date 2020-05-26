import os, subprocess, glob
if __name__ == "__main__":
    algs = ['addPageRank']
    # , 'verPageRank', 'laPCI', 
    #     'mlPCI', 'lsPCI', 'aggPageRank', 'multiCore', 'sumCore', 'aggCore', 
    #     'alPCI', 'aggDegree']
    dirs = ['../data/multilayer/generated/', '../data/multiplex/extracted/']

    for d in dirs:
        count = 6
        for net in os.listdir(d):  
            count -= 1 
            for alg in algs:
                with open('logs2/' + alg + '_' + net + '.log', 'w+') as f:
                    runnable = glob.glob(alg + '/*.out')[0]
                    out = subprocess.run([runnable, d + net], stdout=subprocess.PIPE)
                    res = str(out.stdout).replace('\\n', '\n')[2:]
                    f.write(res)
            if count == 0:
                break
            