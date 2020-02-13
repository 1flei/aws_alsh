#include "precision_recall.h"

using namespace std;

//register precision_recall experiment function here

//K is assumed to be 1 in this case, thus not needed
bool PRECISION_RECALL_E2KL_REGISTED = MyCallbackRegister::registerCallback("precision_recall_e2kl", 
    "n qn d r L dataset_filename queryset_filename weight_filename output_filename", 
    [&](){
	    using namespace MyCallbackRegister;
        int n = algAs<int>("n");
        int qn = algAs<int>("qn");
        int d = algAs<int>("d");

        int L = algAs<int>("L");
        Scalar r = algAs<Scalar>("r");

        string output_filename = algAs<string>("output_filename");

        std::cout << "output: " << output_filename << std::endl;

        const Scalar** data = algAs<const Scalar**>("dataset");
        const Scalar** weight = algAs<const Scalar**>("weightset");
        const Scalar** query = algAs<const Scalar**>("queryset");

        unique_ptr<FILE, decltype(&fclose)> fp(fopen(output_filename.c_str(), "w"), &fclose);

        //K = 1 is assumed
        E2LSH e2lsh(d, 1, L, r);

        //used for normalization

        const auto hp = [&](const float* data) -> vector<uint64_t>{
            // return some vector
            return e2lsh.hash_data(data);
        };
        const auto hq = [&](const float* query, const float*weight) -> vector<uint64_t>{
            //weight unused
            return e2lsh.hash_data(query);
        };

        fprintf(fp.get(), "----e2lsh: r=%f, L=%d----\n", r, L);
        precision_recall(n, qn, d, data, query, weight, hp, hq, fp.get());
    }
);


//K is assumed to be 1 in this case, thus not needed
bool PRECISION_RECALL_S2ALSH_REGISTED = MyCallbackRegister::registerCallback("precision_recall_s2alsh", 
    "n qn d L U dataset_filename queryset_filename weight_filename output_filename", 
    [&](){
	    using namespace MyCallbackRegister;
        int n = algAs<int>("n");
        int qn = algAs<int>("qn");
        int d = algAs<int>("d");

        int L = algAs<int>("L");
        Scalar U = algAs<Scalar>("U");

        string output_filename = algAs<string>("output_filename");

        std::cout << "output: " << output_filename << std::endl;

        const Scalar** data = algAs<const Scalar**>("dataset");
        const Scalar** weight = algAs<const Scalar**>("weightset");
        const Scalar** query = algAs<const Scalar**>("queryset");

        unique_ptr<FILE, decltype(&fclose)> fp(fopen(output_filename.c_str(), "w"), &fclose);

        float minx, maxx;
        calc_min_max(n, qn, d, data, query, minx, maxx);

        //K = 1 is assumed
        S2ALSH s2alsh(d, 1, L, minx, maxx, U);

        const auto hp = [&](const float* data) -> vector<uint64_t>{
            // return some vector
            return s2alsh.hash_data(data);
        };
        const auto hq = [&](const float* query, const float*weight) -> vector<uint64_t>{
            //weight unused
            return s2alsh.hash_query(query, weight);
        };

        fprintf(fp.get(), "----s2alsh: L=%d, U=%f----\n", L, U);
        precision_recall(n, qn, d, data, query, weight, hp, hq, fp.get());
    }
);


//K is assumed to be 1 in this case, thus not needed
bool PRECISION_RECALL_SLALSH_REGISTED = MyCallbackRegister::registerCallback("precision_recall_slalsh", 
    "n qn d L U r dataset_filename queryset_filename weight_filename output_filename", 
    [&](){
	    using namespace MyCallbackRegister;
        int n = algAs<int>("n");
        int qn = algAs<int>("qn");
        int d = algAs<int>("d");

        int L = algAs<int>("L");
        Scalar U = algAs<Scalar>("U");
        Scalar r = algAs<Scalar>("r");

        string output_filename = algAs<string>("output_filename");

        std::cout << "output: " << output_filename << std::endl;

        const Scalar** data = algAs<const Scalar**>("dataset");
        const Scalar** weight = algAs<const Scalar**>("weightset");
        const Scalar** query = algAs<const Scalar**>("queryset");

        unique_ptr<FILE, decltype(&fclose)> fp(fopen(output_filename.c_str(), "w"), &fclose);

        float minx, maxx;
        calc_min_max(n, qn, d, data, query, minx, maxx);

        //K = 1 is assumed
        SLALSH slalsh(d, 1, L, minx, maxx, r, U);

        const auto hp = [&](const float* data) -> vector<uint64_t>{
            // return some vector
            return slalsh.hash_data(data);
        };
        const auto hq = [&](const float* query, const float*weight) -> vector<uint64_t>{
            //weight unused
            return slalsh.hash_query(query, weight);
        };

        fprintf(fp.get(), "----slalsh: L=%d, U=%f, r=%f----\n", L, U, r);
        precision_recall(n, qn, d, data, query, weight, hp, hq, fp.get());
    }
);
