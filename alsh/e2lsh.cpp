#include "e2lsh.h"


E2LSH::E2LSH(int d, int K, int L, Scalar r):
    dim(d), K(K), L(L), r(r)
{
    assert(K>0 && L>0);

    //generate random projection vectors    
	std::default_random_engine rng;
	std::normal_distribution<double> normal(0.,1.0);
	std::uniform_real_distribution<double> uniform(0.,r);
    
    a.resize(K*L);
    b.resize(K*L);

	for(int i=0;i<K*L;i++){
		a[i].resize(d);
		for(int j=0;j<d;j++){
			a[i][j] = normal(rng);
		}
		b[i] = uniform(rng);
	}
}

E2LSH::~E2LSH()
{

}

std::vector<uint64_t> E2LSH::hash_data(const Scalar* data)
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
            projection += b[l];
            int projection_bucket = projection/r;

            sigl = hash_combine(sigl, uint64_t(projection_bucket));
        }
        ret.push_back(sigl);
    }
    return ret;
}