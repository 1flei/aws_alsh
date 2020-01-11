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
            
def getAvgFractionRecalls2(data):
    fractionLevels = np.arange(0., 1.0001, 0.01) 
    
    
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
        
    if len(recalls)==0:
        return fractionLevels, fractionLevels
    recalls = np.array(recalls)
#     print(recalls.shape)
    avgRecalls = np.average(recalls, axis=0)
    
    return fractionLevels, avgRecalls
            
def getAvgFractionRecalls(data): 
    recallLevels = np.arange(0.1, 0.9001, 0.01)
    
    fractions = []
    for datai in splitData(data):
        to_interp = np.append(np.append([[0, 0]], datai, axis=0), [[1, 1]], axis=0)
        f = interp1d(to_interp[:, 1], to_interp[:, 0])
        
#         for frac in fractionLevels:
#             print(frac)
#             print(f(frac))
#         print(f(fractionLevels).shape)
        fractions += [f(recallLevels)]
        
    if len(fractions)==0:
        return recallLevels, recallLevels
    fractions = np.array(fractions)
#     print(recalls.shape)
    avgFractions = np.average(fractions, axis=0)
    
    return avgFractions, recallLevels

# folder = 'bucketExperiment'
# folder = 'refactored_results'
folder = 'results_rep'
# approaches = ['SRP']
datasets = ['Mnist784']
# datasets = ['Mnist784', 'Movielens']
# approaches = ['slalsh', 's2alsh']
approaches = ['s2alsh']
# datasets = ['Movielens']
datasetLabels = ['Mnist']
# datasetLabels = ['Mnist', 'Movielens']

rratioForDatasetL2 = [[1., 2., 4.], [2.], [0.25, 0.5, 1., 2., 4]]
bestrs = [1, 0, 0]

weightSets = ['identical', 'binary', 'normal', 'uniform', 'negative']
# weightSets = ['identical']
weightLabels = ['Identical', 'Binary', 'Normal', 'Uniform', 'Negative']
Ks = [5, 10, 15, 20, 25, 30]
Kss = [list(range(1, 30)), [5, 10, 15, 20, 25, 30], list(range(1, 30))]
Ls = [300]
marker = cycle(('o', 's', 'x', '.', '*', 'v', '^', '<', '>')) 

colors = ['b', 'r']
markers = ['^', 'o']
approachLabels = ['SL-ALSH', 'S2-ALSH']

def plotFractionRecallAmongBestKL(filename, label='This is the label', marker='.', color='k', Ks=Ks):
    reader = fileReader(filename)
    
    plt.xlim(0, 100)
    plt.ylim(0, 100)
    
    pltpnts = []
    maximumRecall = 0
    minimumFraction = 1.
    for data, (k, L) in zip(reader.readDatas(), product(Ks, Ls)):
        fractions, recalls  = getAvgFractionRecalls2(data)
#         minimumFraction = np.minimum(fractions, minimumFraction)
        maximumRecall = np.maximum(recalls, maximumRecall)
#         print('dfr', data, fractions, recalls)
    
    f = interp1d(maximumRecall, fractions)
    recallLevel = np.arange(0.05, 0.9500001, 0.01)
    fractionGivenRecall = f(recallLevel)
    
    plt.plot(recallLevel*100, recallLevel*100, 'k--', label='Linear scan')
    
    np.save(filename[:-4], fractionGivenRecall)
#     np.save('npy/'+label, fractionGivenRecall)
    
#     plt.plot(recalls, fractions, marker=next(marker), markevery=10)
    plt.plot(recallLevel*100, fractionGivenRecall*100, markevery=10, markersize=12, label=label, marker=marker, color=color, markerfacecolor='none')
    #     plt.show()
    #     fraction = np.average(data[:, 0])/nDataset
    #     recall = np.average(data[:, 1])
    #     print(fraction, recall)
    #     
    #     pltpnts += [[recall, fraction]]
    #     plt.plot([recall], [fraction], 'b.')
    #     plt.text(recall, fraction, 'k=%d_l=%d'%(k, L))
    
#             plt.legend()
#             plt.show()

def product3(xs, bs, cs):
    for a in xs:
        for b in bs:
            for c in cs:
                yield (a, b, c)

def plotFractionRecallAmongBestKLR(filename, label='This is the label', marker='.', color='k', rs=[1.], chosenr=0, Ks=Ks):
    reader = fileReader(filename)
    datas = reader.readDatas()
    
    plt.xlim(0, 100)
    plt.ylim(0, 100)
    
#     for r in rs:
    testmarker = cycle(('o', 's', 'x', '.', '*', 'v', '^', '<', '>')) 
    for ridx, r in enumerate(rs):
        pltpnts = []
        maximumRecall = 0
        minimumFraction = 1.
        for k in Ks:
            for L in Ls:
                data = next(datas)
#         for data, (k, L) in zip(datas, product(Ks, Ls)):
                print(r, k, L, ridx, chosenr)
                fractions, recalls  = getAvgFractionRecalls2(data)
        #         minimumFraction = np.minimum(fractions, minimumFraction)
                maximumRecall = np.maximum(recalls, maximumRecall)
        #         print('dfr', data, fractions, recalls)
        
        f = interp1d(maximumRecall, fractions)
        recallLevel = np.arange(0.05, 0.9500001, 0.01)
        fractionGivenRecall = f(recallLevel)
        
        
    #     plt.plot(recalls, fractions, marker=next(marker), markevery=10)
        if ridx == chosenr:
            np.save(filename[:-4], fractionGivenRecall)
            plt.plot(recallLevel*100, recallLevel*100, 'k--', label='Linear scan')
            plt.plot(recallLevel*100, fractionGivenRecall*100, markevery=10, markersize=12, label=label, marker=marker, color=color, markerfacecolor='none')
    
def plotFractionRecallFromFile():
    fig = plt.figure(figsize=(4*len(weightSets), 0.4+3.333*len(datasets)))
    
    plt.rcParams.update({'font.size': 13})
    
    plt.subplots_adjust(bottom=0.1, top=0.85)
    
    pltcnt = 1
    for pltx, (dataset, datasetLabel, rs, bestr, ks) in enumerate(zip(datasets, datasetLabels, rratioForDatasetL2, bestrs, Kss)):
        print(dataset, datasetLabel, rs, bestr)
        for plty, (weight, wlabel) in enumerate(zip(weightSets, weightLabels)):
            plt.subplot(len(datasets), len(weightSets), pltcnt)
            
            if pltx==0:
                plt.title(wlabel)
            if pltx==2:
                plt.xlabel('Recall (%)')
            if plty==0:
                plt.ylabel('%s\nFraction to scan (%%)'%(datasetLabel, ))
            
            
            for approach, approachLabel, color, marker in zip(approaches, approachLabels, colors, markers):
                filename = '%s/%s_%s_fraction_recall_%s.out'%(folder, dataset, weight, approach)
                print(filename)
                
                
                recallLevel = np.arange(0.05, 0.9500001, 0.01)
                
                fractionGivenRecall = np.load('fractionRecall%s.npy'%(approachLabel))
                
                plt.plot(recallLevel*100, recallLevel*100, 'k--', label='Linear scan')
                plt.plot(recallLevel*100, fractionGivenRecall*100, markevery=10, markersize=12, label=approachLabel, marker=marker, color=color, markerfacecolor='none')
    
                
#                 if approach=='L2':
#                     plotFractionRecallAmongBestKLR(filename, color=color, marker=marker, label=approachLabel, rs=rs, chosenr=bestr, Ks=ks)
#                 else:
#                     plotFractionRecallAmongBestKL(filename, color=color, marker=marker, label=approachLabel, Ks=ks)
                
            if pltcnt==1:
                plt.figlegend(fontsize=16, bbox_to_anchor=(0.28,0.78,0.3,0.2), loc="center",
                            mode="expand", borderaxespad=0, ncol=3)
#                 plt.figlegend(fontsize=16, bbox_to_anchor=(0.18,0.77,0.5,0.2), loc="center",
#                             mode="expand", borderaxespad=0, ncol=3)
            pltcnt+=1
            
    plt.savefig('fraction_recall.png', bbox_inches='tight', pad_inches=0.27, dpi=fig.dpi)
    plt.savefig('fraction_recall.eps', bbox_inches='tight', pad_inches=0.27, dpi=fig.dpi)
    plt.show()
    
def plotFractionRecall():
#     fig = plt.figure(figsize=(4*len(weightSets), 0.4+3.333*len(datasets)))
    fig = plt.figure(figsize=(4*len(weightSets), 8.3) )
    
    plt.rcParams.update({'font.size': 13})
    
#     plt.subplots_adjust(bottom=0.1, top=0.85)
    plt.subplots_adjust(bottom=0.1, top=0.8)
    
    pltcnt = 1
    for pltx, (dataset, datasetLabel, rs, bestr, ks) in enumerate(zip(datasets, datasetLabels, rratioForDatasetL2, bestrs, Kss)):
        print(dataset, datasetLabel, rs, bestr)
        for plty, (weight, wlabel) in enumerate(zip(weightSets, weightLabels)):
            plt.subplot(len(datasets), len(weightSets), pltcnt)
            
            if pltx==0:
                plt.title(wlabel)
            if pltx==2:
                plt.xlabel('Recall (%)')
            if plty==0:
                plt.ylabel('%s\nFraction to scan (%%)'%(datasetLabel, ))
            
            
            for approach, approachLabel, color, marker in zip(approaches, approachLabels, colors, markers):
                filename = '%s/%s_%s_fraction_recall_%s.out'%(folder, dataset, weight, approach)
                print(filename)
                
                if approach=='L2':
                    plotFractionRecallAmongBestKLR(filename, color=color, marker=marker, label=approachLabel, rs=rs, chosenr=bestr, Ks=ks)
                else:
                    plotFractionRecallAmongBestKL(filename, color=color, marker=marker, label=approachLabel, Ks=ks)
                
            if pltcnt==1:
                plt.figlegend(fontsize=16, bbox_to_anchor=(0.28,0.78,0.3,0.2), loc="center",
                            mode="expand", borderaxespad=0, ncol=3)
#                 plt.figlegend(fontsize=16, bbox_to_anchor=(0.18,0.77,0.5,0.2), loc="center",
#                             mode="expand", borderaxespad=0, ncol=3)
            pltcnt+=1
            
    plt.savefig('fraction_recall.png', bbox_inches='tight', pad_inches=0.27, dpi=fig.dpi)
    plt.savefig('fraction_recall.eps', bbox_inches='tight', pad_inches=0.27, dpi=fig.dpi)
    plt.show()


# plotFractionRecallFromFile()
plotFractionRecall()

