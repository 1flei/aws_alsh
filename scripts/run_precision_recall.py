from dataset_config import *
from weight_gen import *
import os


datasets = [MNIST784(), MovieLens(), Sift()]
weights= ['identical', 'negative', 'uniform', 'binary', 'normal', 'onehot']

def precisionRecallS2ALSH(datasets=datasets, weightsets=weights, U=3.1415, L=256, qnpercent=1):
    def getArgs(ds, ws):
        return '-n %s -q %s -d %s -D %s -Q %s -O %s -W %s -U %f -L %d'%\
        (ds.n, int(ds.qn*qnpercent), ds.d, ds.ds, ds.qs, ws.of+'_precision_recall_s2.out', ws.ws, U, L)
    
    for ds in datasets:
        for w in weightsets:
            ws = WeightSet(ds, w)
            checkWeight(ds, ws)
            args = getArgs(ds, ws)
            cmd = './alsh -A precision_recall_s2alsh '+args
            print(cmd)
            os.system(cmd)

def precisionRecallSLALSH(datasets=datasets, weightsets=weights, U=3.1415, r=4, L=256, qnpercent=1):
    def getArgs(ds, ws):
        return '-n %s -q %s -d %s -D %s -Q %s -O %s -W %s -r %f -U %f -L %d'%\
        (ds.n, int(ds.qn*qnpercent), ds.d, ds.ds, ds.qs, ws.of+'_precision_recall_sl.out', ws.ws, r, U, L)
    
    for ds in datasets:
        for w in weightsets:
            ws = WeightSet(ds, w)
            checkWeight(ds, ws)
            args = getArgs(ds, ws)
            cmd = './alsh -A precision_recall_slalsh '+args
            print(cmd)
            os.system(cmd)


def precisionRecallE2KL(datasets=datasets, weightsets=weights, r=4, L=256, qnpercent=1):
    def getArgs(ds, ws):
        return '-n %s -q %s -d %s -D %s -Q %s -O %s -W %s -r %f -L %d'%\
        (ds.n, int(ds.qn*qnpercent), ds.d, ds.ds, ds.qs, ws.of+'_precision_recall_e2.out', ws.ws, r, L)
    
    for ds in datasets:
        for w in weightsets:
            ws = WeightSet(ds, w)
            checkWeight(ds, ws)
            args = getArgs(ds, ws)
            cmd = './alsh -A precision_recall_e2kl '+args
            print(cmd)
            os.system(cmd)

if __name__ == '__main__':
    # precisionRecallE2KL(datasets=datasets, weightsets=weights)
    precisionRecallS2ALSH(datasets=datasets, weightsets=weights)
    precisionRecallSLALSH(datasets=datasets, weightsets=weights)