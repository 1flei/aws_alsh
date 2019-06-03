#pragma once

#include "../def.h"
#include "../util.h"
#include <vector>
#include <cinttypes>
#include <random>

//random projection
class SLALSH
{
public: 
    //L: #hasher, K: #hash function per hasher, so K*L hash in total
    SLALSH(int d, int K, int L, Scalar minx, Scalar maxx, Scalar r, Scalar U=PI);  
    ~SLALSH();

    std::vector<uint64_t> hash_data(const Scalar* data);
    std::vector<uint64_t> hash_query(const Scalar* query, const Scalar* weight);

protected:
    int dim, K, L;
    Scalar minx, maxx;
    std::vector<std::vector<Scalar> > a;
    std::vector<Scalar> b;
    Scalar U;
    Scalar r;
};