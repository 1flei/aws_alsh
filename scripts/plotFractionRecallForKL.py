import re
import numpy as np
import matplotlib.pylab as plt
import matplotlib.lines as mlines
# from weightedSpace.logParser import readDatas
from itertools import product, cycle
from scipy.spatial import ConvexHull
from scipy.interpolate import interp1d

class fileReader:
    def __init__(self, filename):
        self.filename = filename
        self.headre = re.compile(r'K=\d+, L=\d+.*')
        self.datare = re.compile(r'\d+.*')
        
    def getNum(self, record):
        return float(record[0].strip())
    def getRecall(self, record):
        return float(record[1].strip())/100.
        
    def readDatas(self):
        with open(self.filename, 'r') as f:
            data = []
            
            isFirst = True
            for line in f:
                if re.match(self.headre, line):
                    #head here
#                     print(line)
                    if not isFirst:
                        data = np.array(data)
                        yield data
                        data = []
                    isFirst = False
                else:
#                     print('data:', line)
                    toks = line.split(',')
#                     print(toks)
                    datai = [self.getNum(toks), self.getRecall(toks)]
#                     print(len(datai))
                    data += [datai]
            data = np.array(data)
            yield data
            data = []
    
def splitData(data):
#     print(data)
    ret = []
    
    lastd = 1e9
    for d in data:
        if d[0]<=lastd:        
            if len(ret)>0:
                yield np.array(ret)
            ret = []
        lastd = d[0]
        ret += [d]
    if len(ret)>0:
        yield np.array(ret)
            
def getAvgFractionRecalls(data, numDataset, nq=1000):
    fractionLevels = np.arange(0., 1., 0.01) + 1/numDataset
    
    
    recalls = []
    for datai in splitData(data):
#         datai_ = np.copy(datai)
#         datai_[:, 0]/=numDataset
        to_interp = np.append(np.append([[0, 0]], datai, axis=0), [[1, 1]], axis=0)
        f = interp1d(to_interp[:, 0], to_interp[:, 1])
        
#         for frac in fractionLevels:
#             print(frac)
#             print(f(frac))
#         print(f(fractionLevels).shape)
        recalls += [f(fractionLevels)]
        
#     print('len(recalls)=', len(recalls))
    for i in range(nq-len(recalls)):
        recalls += [fractionLevels]
        
    if len(recalls)==0:
        return fractionLevels, fractionLevels
    recalls = np.array(recalls)
#     print(recalls.shape)
    avgRecalls = np.average(recalls, axis=0)
#     avgRecalls = np.sum(recalls, axis=0)/nq
    
    return fractionLevels, avgRecalls
        
# reader = fileReader('fractionRecallSRP.out')
# reader = fileReader('fractionRecallL2.out')
# reader = fileReader('rankingExperiment/Mnist/mip/fractionRecallSIMPLE.out')
# reader = fileReader('rankingExperiment/Mnist/mip/fractionRecallSphereIP.out')
# reader = fileReader('rankingExperiment/MovieLens2/mip/fractionRecallSIMPLE.out')
# reader = fileReader('fractionRecallSIMPLE.out')
# reader = fileReader('rankingExperiment/MovieLens2/mip/fractionRecallSphereIP.out')
# reader = fileReader('e2lshExperiment_Combined/Sift/identical/fractionRecallSRP.out')
# reader = fileReader('e2lshExperiment_Combined/Sift/identical/fractionRecallE2.out')
# reader = fileReader('refactored_results/Mnist784_normal_fraction_recall_s2aslh.out')
reader = fileReader('results_rep/Mnist784_identical_fraction_recall_s2alsh.out')
# reader = fileReader('fractionRecallE2.out')
# Ks = np.arange(3, 32, 3)
# Ls = np.arange(20, 210, 20)
# Ks = [5, 10, 15, 20, 25, 30]
Ks = list(range(1, 30))
Ls = [300]

nDataset = 60000

plt.xlim(0, 1)
plt.ylim(0, 1)

pltpnts = []
marker = cycle(('o', 's', 'x', '.', '*', 'v', '^', '<', '>')) 
for data, (k, L) in zip(reader.readDatas(), product(Ks, Ls)):
    print(data, k, L)
    fractions, recalls = getAvgFractionRecalls(data, nDataset)
#     print(data, fractions, recalls)
    
    plt.plot(recalls, fractions, label='k=%d_L=%d'%(k, L), marker=next(marker), markevery=10)
#     plt.show()
#     fraction = np.average(data[:, 0])/nDataset
#     recall = np.average(data[:, 1])
#     print(fraction, recall)
#     
#     pltpnts += [[recall, fraction]]
#     plt.plot([recall], [fraction], 'b.')
#     plt.text(recall, fraction, 'k=%d_l=%d'%(k, L))

plt.legend()
plt.show()

# pltpnts = np.array(pltpnts)
# print(pltpnts)
# 
# hull = ConvexHull(pltpnts)
# vs = pltpnts[np.append(hull.vertices, hull.vertices[0])]
# for v, vp1 in zip(vs, vs[1:]):
#     if v[0] > vp1[0]:
#         continue
#     plt.plot([v[0], vp1[0]], [v[1], vp1[1]], 'r--')
# # plt.plot(pltpnts[hull.vertices,0], pltpnts[hull.vertices,1], 'r--', lw=2)
# # plt.plot(hull[:, 0], hull[:, 1])
# plt.show()