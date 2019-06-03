import numpy as np
import os

def weightGen(name, nData, dim):
    def identicalGen():
        return np.ones(shape=(nData, dim))
    def negativeGen():
        return -np.ones(shape=(nData, dim))
    def normalGen():
        return np.random.normal(size=(nData, dim))
    def binaryGen():
        return np.random.randint(2, size=(nData, dim))
    def trinaryGen():
        return np.random.randint(-1, 2, size=(nData, dim))
    def uniformGen():
        return np.random.uniform(0, 1, size=(nData, dim))
    def uniform2Gen():
        return np.random.uniform(-1, 1, size=(nData, dim))
    def onehotGen():
        wOneHot  = np.zeros(shape=(nData, dim))
        for _, wi in enumerate(wOneHot):
            idx = np.random.randint(dim)
            wi[idx] = 1
        return wOneHot
    def binary2Gen():
        return np.random.binomial(n=1, p=0.25, size=(nData, dim))
    
    gens =  {
        'identical': identicalGen, 
        'negative': negativeGen, 
        'uniform': uniformGen, 
        'uniform2': uniform2Gen, 
        'binary': binaryGen, 
        'binary2': binary2Gen, 
        'trinary': trinaryGen, 
        'onehot': onehotGen, 
        'normal': normalGen
    }
    return gens[name]()
def saveWeight(wss, path):
    with open(path, 'w') as f:
        for i, ws in enumerate(wss):
            #idx
            f.write('%d '%(i+1, ))
            #data
            for w in ws:
                f.write('%f '%(w))
            f.write('\n')
def checkWeight(ds, ws):
    if os.path.exists(ws.ws):
        return True
    
    #else generate the data
    wss = weightGen(ws.name, ds.qn, ds.d)
    saveWeight(wss, ws.ws)
    return True

class WeightSet:
    def __init__(self, ds, wsName):
        self.ws = '../data/%s/%s_%s.w'%(ds.name, ds.name, wsName)
        self.gt = '../data/%s/%s_%s.gt'%(ds.name, ds.name, wsName)
        self.hd = '../data/hash/dsig_%s'%(ds.name, )
        self.hq = '../data/hash/qsig_%s_%s'%(ds.name, wsName)
        self.name = wsName
        self.of = '../data/results/%s_%s'%(ds.name, wsName)