#include "fraction_recall.h"


bool FRACTION_RECALL_E2KL_REGISTED = MyCallbackRegister::registerCallback("fraction_recall_e2kl", 
    "n qn d r dataset_filename queryset_filename weight_filename output_filename ground_truth_filename data_hash_filename query_hash_filename", 
    [&](){
	    using namespace MyCallbackRegister;
        using namespace std;

        int n = algAs<int>("n");
        int qn = algAs<int>("qn");
        int d = algAs<int>("d");

        Scalar r = algAs<Scalar>("r");

        string output_filename = algAs<string>("output_filename");

        std::cout << "output: " << output_filename << std::endl;

        const Scalar** data = algAs<const Scalar**>("dataset");
        const Scalar** weight = algAs<const Scalar**>("weightset");
        const Scalar** query = algAs<const Scalar**>("queryset");
        const Result** results = algAs<const Result**>("ground_truth");

        string data_hash_filename = algAs<string>("data_hash_filename");
        string query_hash_filename = algAs<string>("query_hash_filename");

        std::vector<int> Ks, Ls;
        int maxk = 30, maxl= 300;
        for(int i=1;i<=maxk;i++){
            Ks.push_back(i);
        }
        Ls.push_back(maxl);

        int nHashers = maxk*maxl;

        E2LSH e2lsh(d, 1, nHashers, r);
        const auto hp = [&](const float* data) -> vector<uint64_t>{
            // return some vector
            return e2lsh.hash_data(data);
        };
        const auto hq = [&](const float* query, const float*weight) -> vector<uint64_t>{
            //weight unused
            return e2lsh.hash_data(query);
        };
        unique_ptr<FILE, decltype(&fclose)> fp(fopen(output_filename.c_str(), "w"), &fclose);

        fraction_recall(n, qn, d, Ks, Ls, data, query, weight, results, hp, hq, fp.get(), data_hash_filename, query_hash_filename);
    });


bool FRACTION_RECALL_SLALSH_REGISTED = MyCallbackRegister::registerCallback("fraction_recall_slalsh", 
    "n qn d r U dataset_filename queryset_filename weight_filename output_filename ground_truth_filename data_hash_filename query_hash_filename", 
    [&](){
	    using namespace MyCallbackRegister;
        using namespace std;

        int n = algAs<int>("n");
        int qn = algAs<int>("qn");
        int d = algAs<int>("d");

        Scalar r = algAs<Scalar>("r");
        Scalar U = algAs<Scalar>("U");

        string output_filename = algAs<string>("output_filename");

        std::cout << "output: " << output_filename << std::endl;

        const Scalar** data = algAs<const Scalar**>("dataset");
        const Scalar** weight = algAs<const Scalar**>("weightset");
        const Scalar** query = algAs<const Scalar**>("queryset");
        const Result** results = algAs<const Result**>("ground_truth");

        string data_hash_filename = algAs<string>("data_hash_filename");
        string query_hash_filename = algAs<string>("query_hash_filename");

        std::vector<int> Ks, Ls;
        int maxk = 30, maxl= 300;
        for(int i=1;i<=maxk;i++){
            Ks.push_back(i);
        }
        Ls.push_back(maxl);

        int nHashers = maxk*maxl;

        Scalar minx, maxx;
        calc_min_max(n, qn, d, data, query, minx, maxx);

        SLALSH slalsh(d, 1, nHashers, minx, maxx, r, U);
        const auto hp = [&](const float* data) -> vector<uint64_t>{
            // return some vector
            return slalsh.hash_data(data);
        };
        const auto hq = [&](const float* query, const float*weight) -> vector<uint64_t>{
            //weight unused
            return slalsh.hash_query(query, weight);
        };
        unique_ptr<FILE, decltype(&fclose)> fp(fopen(output_filename.c_str(), "w"), &fclose);

        fraction_recall(n, qn, d, Ks, Ls, data, query, weight, results, hp, hq, fp.get(), data_hash_filename, query_hash_filename);
    });


bool FRACTION_RECALL_S2ALSH_REGISTED = MyCallbackRegister::registerCallback("fraction_recall_s2alsh", 
    "n qn d U dataset_filename queryset_filename weight_filename output_filename ground_truth_filename data_hash_filename query_hash_filename", 
    [&](){
	    using namespace MyCallbackRegister;
        using namespace std;

        int n = algAs<int>("n");
        int qn = algAs<int>("qn");
        int d = algAs<int>("d");

        Scalar U = algAs<Scalar>("U");

        string output_filename = algAs<string>("output_filename");

        std::cout << "output: " << output_filename << std::endl;

        const Scalar** data = algAs<const Scalar**>("dataset");
        const Scalar** weight = algAs<const Scalar**>("weightset");
        const Scalar** query = algAs<const Scalar**>("queryset");
        const Result** results = algAs<const Result**>("ground_truth");

        string data_hash_filename = algAs<string>("data_hash_filename");
        string query_hash_filename = algAs<string>("query_hash_filename");

        std::vector<int> Ks, Ls;
        int maxk = 30, maxl= 300;
        for(int i=1;i<=maxk;i++){
            Ks.push_back(i);
        }
        Ls.push_back(maxl);

        int nHashers = maxk*maxl;

        Scalar minx, maxx;
        calc_min_max(n, qn, d, data, query, minx, maxx);
        S2ALSH s2alsh(d, 1, nHashers, minx, maxx, U);

        const auto hp = [&](const float* data) -> vector<uint64_t>{
            // return some vector
            return s2alsh.hash_data(data);
        };
        const auto hq = [&](const float* query, const float*weight) -> vector<uint64_t>{
            //weight unused
            return s2alsh.hash_query(query, weight);
        };
        unique_ptr<FILE, decltype(&fclose)> fp(fopen(output_filename.c_str(), "w"), &fclose);

        fraction_recall(n, qn, d, Ks, Ls, data, query, weight, results, hp, hq, fp.get(), data_hash_filename, query_hash_filename);
    });