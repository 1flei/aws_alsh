#pragma once

#include "../def.h"
#include "../util.h"
#include <vector>
#include <cinttypes>
#include <random>

//random projection
class E2LSH
{
public: 
    //L: #hasher, K: #hash function per hasher, so K*L hash in total
    E2LSH(int d, int K, int L, Scalar r);  
    ~E2LSH();

    std::vector<uint64_t> hash_data(const Scalar* data);

protected:
    int dim, K, L;
    std::vector<std::vector<Scalar> > a;
    std::vector<Scalar> b;
    Scalar r;
};