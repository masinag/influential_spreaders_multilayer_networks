import os, subprocess, glob
if __name__ == "__main__":
    algs = ['addPageRank']
    # , 'verPageRank', 'laPCI', 
    #     'mlPCI', 'lsPCI', 'aggPageRank', 'multiCore', 'sumCore', 'aggCore', 
    #     'alPCI', 'aggDegree']
    

    
    for net in os.listdir('logs2'):
        print(net) 
        scores2={} 
        with open('logs2/' + net, 'r') as l2:
            for r in l2:
                if not 'iteration' in r and r != "'":
                    try:
                        n, s = r.split(', score: ')
                    except:
                        print([r])
                        exit(0)
                    n = int(n)
                    s = float(s)
                    scores2[n] = s
        scores1 = {}
        with open('logs/' + net, 'r') as l1:
            for r in l1:
                if not 'iteration' in r and r != "'":
                    try:
                        n, s = r.split(', score: ')
                    except:
                        print([r])
                        exit(0)

                    n = int(n)
                    s = float(s)
                    scores1[n] = s

        for k in scores1:
            if scores1[k] != scores2[k]:
                print(k, scores1[k], scores2[k])
        print()