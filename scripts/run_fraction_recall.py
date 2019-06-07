from dataset_config import *
from weight_gen import *
import os


datasets = [MNIST784(), MovieLens(), Sift()]
weights= ['identical', 'negative', 'uniform', 'binary', 'normal', 'onehot']

def get_datahash_filename(dataset_name, weight_name, method_name, params):
    return '%s_%s_%s.dh'%(dataset_name, method_name, params)
def get_queryhash_filename(dataset_name, weight_name, method_name, params):
    return '%s_%s_%s_%s.qh'%(dataset_name, weight_name, method_name, params)

def fractionRecallS2ALSH(datasets=datasets, weightsets=weights, U=3.14, qnpercent=1.):
    def getArgs(ds, ws):
        params= 'U%f'%(U, )
        return '-n %s -q %s -d %s -D %s -Q %s -O %s -W %s -G %s -U %f --data_hash_filename %s --query_hash_filename %s'%\
        (ds.n, int(ds.qn*qnpercent), ds.d, ds.ds, ds.qs, ws.of+'_fraction_recall_s2alsh.out', ws.ws, ws.gt, U, 
        get_datahash_filename(ds.name, ws.name, 's2alsh', params), 
        get_queryhash_filename(ds.name, ws.name, 's2alsh', params))
    
    for ds in datasets:
        for w in weightsets:
            ws = WeightSet(ds, w)
            checkWeight(ds, ws)
            args = getArgs(ds, ws)
            cmd = './alsh -A fraction_recall_s2alsh '+args
            print(cmd)
            os.system(cmd)

def fractionRecallSLALSH(datasets=datasets, weightsets=weights, r=4, U=3.14, qnpercent=1.):
    def getArgs(ds, ws):
        params= 'U%fr%f'%(U, r)
        return '-n %s -q %s -d %s -D %s -Q %s -O %s -W %s -G %s -r %f -U %f --data_hash_filename %s --query_hash_filename %s'%\
        (ds.n, int(ds.qn*qnpercent), ds.d, ds.ds, ds.qs, ws.of+'_fraction_recall_slalsh.out', ws.ws, ws.gt, r, U, 
        get_datahash_filename(ds.name, ws.name, 'slalsh', params), 
        get_queryhash_filename(ds.name, ws.name, 'slalsh', params))
    
    for ds in datasets:
        for w in weightsets:
            ws = WeightSet(ds, w)
            checkWeight(ds, ws)
            args = getArgs(ds, ws)
            cmd = './alsh -A fraction_recall_slalsh '+args
            print(cmd)
            os.system(cmd)

def fractionRecallE2KL(datasets=datasets, weightsets=weights, r=4, qnpercent=1):
    def getArgs(ds, ws):
        params = 'r%f'%(r, )
        return '-n %s -q %s -d %s -D %s -Q %s -O %s -W %s -G %s -r %f --data_hash_filename %s --query_hash_filename %s'%\
        (ds.n, int(ds.qn*qnpercent), ds.d, ds.ds, ds.qs, ws.of+'_fraction_recall_e2.out', ws.ws, ws.gt, r, 
        get_datahash_filename(ds.name, ws.name, 'e2', params), 
        get_queryhash_filename(ds.name, ws.name, 'e2', params))
    
    for ds in datasets:
        for w in weightsets:
            ws = WeightSet(ds, w)
            checkWeight(ds, ws)
            args = getArgs(ds, ws)
            cmd = './alsh -A fraction_recall_e2kl '+args
            print(cmd)
            os.system(cmd)

if __name__ == '__main__':
    # fractionRecallE2KL(datasets=datasets, weightsets=weights)
    fractionRecallSLALSH(datasets=datasets, weightsets=weights)
    fractionRecallS2ALSH(datasets=datasets, weightsets=weights)