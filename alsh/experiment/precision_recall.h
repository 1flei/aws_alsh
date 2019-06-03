#pragma once

#include <string>
#include "../../def.h"
#include "../../util.h"
#include "../../register.h"
#include "../e2lsh.h"
#include "../s2alsh.h"
#include "../slalsh.h"
#include <memory>

//input:
//n: #points
//qn: #queries
//d: dimension
//data: pointer to data
//query: pointer to query
//weight: pointer to weight
//hp: hash function for data    PF:: const Scalar* -> vector<uint64_t>
//hq: hash function for query   QF:: const Scalar* query -> const Scalar* weight -> vector<uint64_t> 
//fp, FILE*, 
template<class PF, class QF>
void precision_recall( 
    int n,
    int qn, 
    int d, 
    const Scalar** data, 
    const Scalar** query,
    const Scalar** weight, 
    const PF& hp, 
    const QF& hq, 
    FILE* fp
    )
{
    fprintf(fp, "----precision_recall: n=%d, qn=%d, d=%d----\n", n, qn, d);

    printf("computing sig of x\n");
    std::vector<std::vector<uint64_t> > datasigs;
    datasigs.reserve(n);
    for(int i=0;i<n;i++){
        const Scalar* datai = data[i];
        auto datasig = hp(datai);
        
        datasigs.emplace_back(std::move(datasig) );
        // datasigs.push_back(datasig);
    }
    
    std::vector<Scalar> truedists(n);
    std::vector<int> sigsims(n);
    std::vector<int> sigidx(n);
    std::vector<int> sigrank(n);
    std::vector<int> dataidx(n);

    for(int i=0;i<n;i++){
        sigidx[i] = i;
        sigrank[i] = i;
        dataidx[i] = i;
    }
    random_shuffle(sigidx.begin(), sigidx.end());
    random_shuffle(sigrank.begin(), sigrank.end());
    random_shuffle(dataidx.begin(), dataidx.end());

    printf("for each query...\n");
    for(int i=0;i<qn;i++){
        auto queryi = query[i];
        auto weighti = weight[i];
        auto querysigi = hq(queryi, weighti);

        if(i%100==0){
            printf("query-%d\n", i);
        }

        for(int j=0;j<n;j++){
            truedists[j] = calc_weighted_dist2(d, weighti, queryi, data[j]);
        }

        // printVec(truedists.begin(), truedists.end(), "trudists:\n");
        
        for(int j=0;j<n;j++){
            sigsims[j] = 0;
            for(int dsig=0;dsig<querysigi.size() && dsig<datasigs[j].size(); dsig++){
                if((querysigi[dsig]==datasigs[j][dsig])){
                    sigsims[j]++; 
                }
            }
        }
        // printVec(sigsims.begin(), sigsims.end(), "sigsim:\n");

        sort(sigidx.begin(), sigidx.end(), [&](int a, int b){
            return sigsims[a] > sigsims[b];
        });
        sort(dataidx.begin(), dataidx.end(), [&](int a, int b){
            return truedists[a] < truedists[b];
        });
        sort(sigrank.begin(), sigrank.end(), [&](int a, int b){
            return sigidx[a] < sigidx[b];
        });
        // printVec(&query[i][0], &query[i][d], "query: ");
        // printVec(&weight[i][0], &weight[i][d], "weight: ");
        // for(int j=0;j<5;j++){
        //     printVec(&data[dataidx[j]][0], &data[dataidx[j]][d], "data: ");
        // }
        // printVec(sigsims.begin(), sigsims.end(), "sigsims: ");
        // printVec(dataidx.begin(), dataidx.end(), "dataidx: ");
        // printVec(sigidx.begin(), sigidx.end(), "sigidx: ");
        // printVec(sigrank.begin(), sigrank.end(), "sigrank: ");

        for(int j=0;j<100 && j<n;j++){
            //scheme: dataidx, sigrank[dataidx], sigsim[dataidx], truedist[dataidx]
            fprintf(fp, "(%d, %d, %d, %f), ", dataidx[j], sigrank[dataidx[j]]+1, sigsims[dataidx[j]], truedists[dataidx[j]]);
        }
        fprintf(fp, "\n");
        // printf("query-%d end\n", i);
    }
    // printf("end of for loop\n");
}