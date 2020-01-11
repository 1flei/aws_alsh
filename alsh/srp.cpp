#include "srp.h"


SRPLSH::SRPLSH(int d, int K, int L):
    dim(d), K(K), L(L)
{
    assert(K>0 && L>0);

    //generate random projection vectors    
	std::default_random_engine rng;
	std::normal_distribution<double> normal(0.,1.0);
    
    a.resize(K*L);

	for(int i=0;i<K*L;i++){
		a[i].resize(d);
		for(int j=0;j<d;j++){
			a[i][j] = normal(rng);
		}
	}
}

SRPLSH::~SRPLSH()
{

}

std::vector<uint64_t> SRPLSH::hash_data(const Scalar* data)
{
    std::vector<uint64_t> ret;
    for(int l=0;l<L;l++){
        uint64_t sigl = 0;
        for(int k=0;k<K;k++){
            double projection = 0.;
            for(int i=0;i<dim;i++){
                double x = data[i];
                projection += x*a[l*K+k][i];
            }
            uint64_t sigkl = projection>0;

            sigl = hash_combine(sigl, sigkl);
        }
        ret.push_back(sigl);
    }
    return ret;
}