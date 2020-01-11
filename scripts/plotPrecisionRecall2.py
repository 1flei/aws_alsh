import re
import numpy as np
import matplotlib.pylab as plt
import matplotlib.lines as mlines

class fileReader:
    def __init__(self, filename):
        self.filename = filename
        self.headre = re.compile(r'--.*')
        self.datare = re.compile(r'\d+.*')
        
    def getDists(self, record):
        recordTok = record.split(':')
        dists = recordTok[2].split('~')
        return float(dists[0]), float(dists[1])
    
    def getRank(self, record):
        recordTok = record.split(':')
        return float(recordTok[1][1:-1])
        
    def readDatas(self):
        with open(self.filename, 'r') as f:
            data = []
            for line in f:
                if re.match(self.headre, line):
                    #head here
                    print(line)
                    if len(data)!=0:
                        data = np.array(data)
                        yield data
                        data = []
                else:
#                     print('data:', line)
                    toks = line.split(',')[:-1]
                    datai = [self.getRank(x) for x in toks]
#                     print(len(datai))
                    data += [datai]
            data = np.array(data)
            yield data
            data = []
            
def plotPrecisionRecall2(data, k=10, numData=10000, label='This is the label', marker='.', color='k'):
    data = data[:, :k]
#     numData = data.shape[0]
    data = np.sort(data.reshape(-1), axis=-1)

    cnt = np.arange(1, len(data)+0.5, 1)
    precisions = cnt/data
    recalls = cnt/len(data)
    
#     print('data=', data)
#     print('cnt=', cnt)
#     print('precision=', precisions)
#     print('recalls=', recalls)
    
    
#     print('data=', data)
#     print('cnt=', cnt)
    print('precision=', precisions)
    print('recalls=', recalls)
#     precisions = cnt/data
#     recalls    = cnt/10
    plt.xlim(0, 1)
    plt.plot(recalls, precisions, label=label, marker=marker, markevery=100, markerfacecolor='none', color=color)
#     plt.show()

def plotPrecisionRecall(data, k=10, numData=10000, label='This is the label', marker='.', color='k', startingLoc=0):
    data = data[:, startingLoc:k+startingLoc]
    
    sorted_data = np.sort(data.reshape(-1))
    
    N = len(sorted_data)
    NQ = N/k
    
    precisions = []
    recalls = []
    
    for ratio in np.arange(0.001, 1., 0.005):
        idx = int(len(sorted_data)*ratio)-1
        
        cntgivenrecall = sorted_data[idx]
        
        releventSeen = np.sum(data<=cntgivenrecall)
        
#         print(cntgivenrecall, releventSeen)
        precisions += [releventSeen*1./NQ/cntgivenrecall]
        recalls += [releventSeen/N]
        
#         print(recall, idx, cntgivenrecall, pr)
    recalls = np.array(recalls)
    precisions = np.array(precisions)

    print('precision=', precisions)
    print('recalls=', recalls)
#     precisions = cnt/data
#     recalls    = cnt/10

    maxp = np.max(precisions)
    plt.xlim(0, 100)
    plt.ylim(0, maxp*100+0.1)


    #percent
#     precisions = np.array(precisions)*100
#     recalls = np.array(recalls)*100
#     maxp = np.max(precisions)
#     plt.xlim(0, 100)
#     plt.ylim(0, maxp+0.1)
    
#     plt.ylim(0, maxp)
    plt.plot(recalls*100, precisions*100, label=label, marker=marker, markevery=20, markerfacecolor='none', color=color, markersize=12)
#     plt.show()
    
def bucketRecall(data, k=10, numData=1e6, label='This is the label', marker='.', color='k'):
    data = data[:, :k]
    data = np.sort(data.reshape(-1), axis=-1)
    
    cnt = np.arange(1, len(data)+0.5, 1)
    ratios = data/numData
    recalls = cnt/len(data)
    
    plt.xlim(0, 1)
    plt.ylim(0, 1)
    
    plt.plot(recalls, recalls, 'k--', label='LinearScan')
    
    x = np.arange(0., 1.05, 0.1)
    y = np.interp(x, recalls, ratios)
    
#     plt.plot(x, y, label=label, marker=marker, markevery=1, markerfacecolor='none', color=color)
    plt.plot(recalls, ratios, label=label, marker=marker, markevery=1000, markerfacecolor='none', color=color, markersize=12)
#     plt.plot(recalls, ratios, color=color)
#     plt.show()


def flRecall(data, k=10, numData=1e6, label='This is the label', marker='.', color='k'):
    data = data[:, :k]
    data = np.sort(data.reshape(-1), axis=-1)
    
    cnt = np.arange(1, len(data)+0.5, 1)
    ratios = data/numData
    recalls = cnt/len(data)
    
    plt.xlim(0, 1)
    plt.ylim(0, 1)
    
#     plt.plot(recalls, recalls, 'k--')
    
    x = np.arange(0., 1.05, 0.1)
    y = np.interp(x, recalls, ratios)
    
    #fraction of linear scan
    fracLinear = ratios/recalls
    
#     plt.plot(x, y, label=label, marker=marker, markevery=1, markerfacecolor='none', color=color)
    markevery = int(len(fracLinear)/10)
    print(len(fracLinear), markevery)
    plt.plot(recalls, fracLinear, label=label, marker=marker, markevery=markevery, markerfacecolor='none', color=color)
#     plt.plot(recalls, ratios, color=color)
#     plt.show()


folder = 'rankingExperiment'
    
# datasets = ['MovieLens', 'Yahoo', 'Sift']
# nPnts = [50000, 620000, 1e6]
datasets = ['MNist784', 'Sift']
datasetLabels = ['MNIST', 'Sift']
nPnts = [60000, 1000000, 50000]

weightSets = ['identical', 'binary', 'normal', 'uniform', 'identical2']
# weightSets = ['identical']
weightLabels = ['Identical', 'Binary', 'Normal', 'Uniform', 'Negative']
# approaches = ['L2', 'SRP']
approaches = ['L2auto', 'SRP']
approachLabels = ['SL-ALSH', 'S2-ALSH']

# markerss = [['o', 's'], ['^', 'v'], ['<', '>']]
markerss = [['^', 'x'], ['o', 'v'], ['<', '>']]
colorss = [['b', 'g'], ['r', 'c'], ['m', 'y']]

# styles = ['bo-', 'gs-', 'r^-', 'cv-', 'm<-', 'y>-']
# lagendLabels = ['MIP-128', 'MIP-256', 'SRP-128', 'SRP256', 'L2-128', 'L2-256']
styles = ['bo-', 'gs-', 'r^-', 'cv-', 'm<-', 'y>-']
lagendLabels = ['SRP', 'L2']

def plot_bak():
    fig = plt.figure(figsize=(4*len(weightSets), 3.333*len(datasets)))
    plt.rcParams.update({'font.size': 13})
    
    pltcnt = 1
    for pltx, (dataset, n) in enumerate(zip(datasets, nPnts)):
        for plty, (weightSet, wlabel) in enumerate(zip(weightSets, weightLabels)):
            plt.subplot(len(datasets), len(weightSets), pltcnt)
            if pltx==0:
                plt.title(wlabel)
            if pltx==2:
                plt.xlabel('Recall')
            if plty==0:
    #             plt.ylabel('%s\nfraction of dataset to scan'%(dataset, ))
                plt.ylabel('%s\nPrecision'%(dataset, ))
            pltcnt += 1
            
            for approach, label, markers, colors in zip(approaches, approachLabels, markerss, colorss):
                print(dataset, weightSet, approach)
                filename = '%s/%s/%s/precisionRecall%s.out'%(folder, dataset, weightSet, approach)
                reader = fileReader(filename)
                
                for data, k, marker, color in zip(reader.readDatas(), ['-128', '-256'], markers, colors):
    #                 print(data)
                    bucketRecall(data, numData = n, label=label, marker=marker, color=color)
    #                 plotPrecisionRecall(data, numData = n, label=label, marker=marker, color=color)
    #                 flRecall(data, numData = n, label=label, marker=marker, color=color)
    
            handles = [mlines.Line2D([], [], color=s[0], marker=s[1], markerfacecolor='none', label=label) for s, label in zip(styles, lagendLabels)]
    #         plt.legend(handles=handles, loc=2)
            plt.legend()
            
def plot_one_lagend():
#     fig = plt.figure(figsize=(4*len(weightSets), 0.4+3.333*len(datasets)))
    fig = plt.figure(figsize=(4*len(weightSets), 8.3) )
    
    plt.rcParams.update({'font.size': 13})
    
    plt.subplots_adjust(bottom=0.1, top=0.8)
    
    pltcnt = 1
    for pltx, (dataset, datasetLabel, n) in enumerate(zip(datasets, datasetLabels, nPnts)):
        for plty, (weightSet, wlabel) in enumerate(zip(weightSets, weightLabels)):
            ax = plt.subplot(len(datasets), len(weightSets), pltcnt)
            if pltx==0:
                plt.title(wlabel)
            if pltx==2:
                plt.xlabel('Recall (%)')
            if plty==0:
                plt.ylabel('%s\nPrecision (%%)'%(datasetLabel, ))
#                 plt.ylabel('%s\nPrecision'%(dataset, ))
            pltcnt += 1
            
#             axbos = ax.get_position()
            
            for approach, label, markers, colors in zip(approaches, approachLabels, markerss, colorss):
                print(dataset, weightSet, approach)
                filename = '%s/%s/%s/precisionRecall%s.out'%(folder, dataset, weightSet, approach)
                reader = fileReader(filename)
                
                for data, marker, color in zip(reader.readDatas(), markers, colors):
    #                 print(data)
#                     bucketRecall(data, numData = n, label=label, marker=marker, color=color)
                    plotPrecisionRecall(data, numData = n, label=label, marker=marker, color=color)
    #                 flRecall(data, numData = n, label=label, marker=marker, color=color)
    
            handles = [mlines.Line2D([], [], color=s[0], marker=s[1], markerfacecolor='none', label=label) for s, label in zip(styles, lagendLabels)]
    #         plt.legend(handles=handles, loc=2)
#             plt.legend()
            if pltx==1 and plty==1:
                plt.figlegend(fontsize=16, bbox_to_anchor=(0.33,0.77,0.25,0.2), loc="center",
                            mode="expand", borderaxespad=0, ncol=3)
                
#         plt.savefig('precision_recall_2.png', bbox_inches='tight', dpi=fig.dpi)
        plt.savefig('precision_recall_2.eps', bbox_inches='tight', pad_inches=0.3, dpi=fig.dpi)
        plt.savefig('precision_recall_2.png', bbox_inches='tight', pad_inches=0.3, dpi=fig.dpi)

plot_one_lagend()
plt.show()