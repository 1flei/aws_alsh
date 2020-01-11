#include "s2alsh.h"


S2ALSH::S2ALSH(int d, int K, int L, Scalar minx, Scalar maxx, Scalar U):
    dim(d), K(K), L(L), minx(minx), maxx(maxx), U(U)
{
    assert(K>0 && L>0);

    //generate random projection vectors    
	std::default_random_engine rng;
	std::normal_distribution<double> normal(0.,1.0);
    
    a.resize(K*L);

	for(int i=0;i<K*L;i++){
		a[i].resize(2*d);
		for(int j=0;j<2*d;j++){
			a[i][j] = normal(rng);
		}
	}
}

S2ALSH::~S2ALSH()
{

}


std::vector<uint64_t> S2ALSH::hash_data(const Scalar* data)
{
    std::vector<uint64_t> ret;
    for(int l=0;l<L;l++){
        uint64_t sigl = 0;
        for(int k=0;k<K;k++){
            double projection = 0.;
            for(int i=0;i<dim;i++){
                double x = data[i];
				double Ux = (x-minx)/(maxx-minx)*U;
				double cosUx = cos(Ux);
				double sinUx = sin(Ux);
				projection += cosUx*a[l*K+k][i] + sinUx*a[l*K+k][i+dim];
            }

            sigl = hash_combine(sigl, uint64_t(projection > 0));
        }
        ret.push_back(sigl);
    }
    return ret;
}

std::vector<uint64_t> S2ALSH::hash_query(const Scalar* query, const Scalar* weight)
{
    std::vector<uint64_t> ret;
    for(int l=0;l<L;l++){
        uint64_t sigl = 0;
        for(int k=0;k<K;k++){
            double projection = 0.;
            for(int i=0;i<dim;i++){
                double x = query[i];
				double w = weight[i];
				double Uq = (x-minx)/(maxx-minx)*U;
				double cosUq = w*cos(Uq);
				double sinUq = w*sin(Uq);
				projection += cosUq*a[l*K+k][i] + sinUq*a[l*K+k][i+dim];
            }

            sigl = hash_combine(sigl, uint64_t(projection > 0));
        }
        ret.push_back(sigl);
    }
    return ret;
}