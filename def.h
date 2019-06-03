#pragma once
#include <cstdint>

typedef float Scalar;

struct Result {
    Scalar key_; // distance / random projection value
    int id_; // object id
};

const int MAXK = 100;

const Scalar E = 2.7182818F;
const Scalar PI = 3.141592654F;
const Scalar EPS = 1e-6F;