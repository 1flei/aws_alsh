#pragma once

#include "../def.h"
#include "../util.h"
#include <vector>
#include <cinttypes>
#include <random>

//random projection
class SRPLSH
{
public:
    SRPLSH(int d, int K, int L);   //L: #hasher, K: #hash function per hasher, so K*L hash in total
    ~SRPLSH();

    std::vector<uint64_t> hash_data(const Scalar* data);

protected:
    int dim, K, L;
    std::vector<std::vector<Scalar> > a;
};