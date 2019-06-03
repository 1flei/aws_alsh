#include "ground_truth.h"

using namespace std;

bool GROUND_TRUTH_INNER_PRODUCT_REGISTED = MyCallbackRegister::registerCallback("ground_truth_inner_product", 
		"n qn d dataset_filename queryset_filename output_filename", [&](){
	using namespace MyCallbackRegister;
	int n = algAs<int>("n");
	int qn = algAs<int>("qn");
	int d = algAs<int>("d");
	string output_filename = algAs<string>("output_filename");

	const Scalar** data = algAs<const Scalar**>("dataset");
	const Scalar** query = algAs<const Scalar**>("queryset");
	ground_truth_inner_product(n, qn, d, data, query, output_filename.c_str());
});

bool GROUND_TRUTH_WEIGHTED_DISTANCE_REGISTED = MyCallbackRegister::registerCallback("ground_truth_weighted_distance", 
		"n qn d dataset_filename weight_filename queryset_filename output_filename", [&](){
	using namespace MyCallbackRegister;
	int n = algAs<int>("n");
	int qn = algAs<int>("qn");
	int d = algAs<int>("d");
	string output_filename = algAs<string>("output_filename");

	const Scalar** data = algAs<const Scalar**>("dataset");
	const Scalar** weight = algAs<const Scalar**>("weightset");
	const Scalar** query = algAs<const Scalar**>("queryset");
	ground_truth_weighted_distance(n, qn, d, data, query, weight, output_filename.c_str());
});

bool GROUND_TRUTH_ANGLE_REGISTED = MyCallbackRegister::registerCallback("ground_truth_angle", 
		"n qn d dataset_filename queryset_filename output_filename", [&](){
	using namespace MyCallbackRegister;
	int n = algAs<int>("n");
	int qn = algAs<int>("qn");
	int d = algAs<int>("d");
	string output_filename = algAs<string>("output_filename");

	const Scalar** data = algAs<const Scalar**>("dataset");
	const Scalar** query = algAs<const Scalar**>("queryset");
	ground_truth_angle(n, qn, d, data, query, output_filename.c_str());
});

bool GROUND_TRUTH_FURTHEST_REGISTED = MyCallbackRegister::registerCallback("ground_truth_furthest", 
		"n qn d dataset_filename queryset_filename output_filename", [&](){
	using namespace MyCallbackRegister;
	int n = algAs<int>("n");
	int qn = algAs<int>("qn");
	int d = algAs<int>("d");
	string output_filename = algAs<string>("output_filename");

	const Scalar** data = algAs<const Scalar**>("dataset");
	const Scalar** query = algAs<const Scalar**>("queryset");
	ground_truth_angle(n, qn, d, data, query, output_filename.c_str());
});

// -----------------------------------------------------------------------------
int ground_truth_inner_product(					// find the ground truth results
	int   n,							// number of data points
	int   qn,							// number of query points
	int   d,							// dimension of space
	const Scalar **data,					// data set
	const Scalar **query,				// query set
	const char  *truth_set)				// address of truth set
{
	// timeval start_time, end_time;

	// -------------------------------------------------------------------------
	//  find ground truth results (using linear scan method)
	// -------------------------------------------------------------------------

    FILE *fp = fopen(truth_set, "w");
    if (!fp) {
        printf("Could not create %s.\n", truth_set);
        return 1;
    }

    double duration = MyTimer::measure([&](){
        auto list = make_unique<MaxK_List>(MAXK);
        // MaxK_List *list = new MaxK_List(MAXK);
        fprintf(fp, "%d %d\n", qn, MAXK);
        for (int i = 0; i < qn; ++i) {
            list->reset();
            for (int j = 0; j < n; ++j) {	
                Scalar ip = calc_inner_product(d, data[j], query[i]);
                list->insert(ip, j + 1);
            }

            for (int j = 0; j < MAXK; ++j) {
                fprintf(fp, "%d %f ", list->ith_id(j), list->ith_key(j));
            }
            fprintf(fp, "\n");
        }
    });
    fclose(fp);

	printf("Ground Truth: %f Seconds\n\n", duration);

	return 0;
}


// -----------------------------------------------------------------------------
int ground_truth_weighted_distance(					// find the ground truth results
	int   n,							// number of data points
	int   qn,							// number of query points
	int   d,							// dimension of space
	const Scalar **data,					// data set
	const Scalar **query,				// query set
	const Scalar **weight,				// query set
	const char  *truth_set)				// address of truth set
{
	// -------------------------------------------------------------------------
	//  find ground truth results (using linear scan method)
	// -------------------------------------------------------------------------
	FILE *fp = fopen(truth_set, "w");
	if (!fp) {
		printf("Could not create %s.\n", truth_set);
		return 1;
	}

    double truth_time = MyTimer::measure([&](){
        auto list = make_unique<MinK_List>(MAXK);
        fprintf(fp, "%d %d\n", qn, MAXK);
        for (int i = 0; i < qn; ++i) {
            list->reset();
            for (int j = 0; j < n; ++j) {
                Scalar ip = calc_weighted_dist2(d, weight[i], data[j], query[i]);
                list->insert(ip, j + 1);
            }

            for (int j = 0; j < MAXK; ++j) {
                fprintf(fp, "%d %f ", list->ith_id(j), list->ith_key(j));
            }
            fprintf(fp, "\n");
        }
    });
    fclose(fp);

	printf("Ground Truth: %f Seconds\n\n", truth_time);

	return 0;
}
// -----------------------------------------------------------------------------
int ground_truth_furthest(					// find the ground truth results
	int   n,							// number of data points
	int   qn,							// number of query points
	int   d,							// dimension of space
	const Scalar **data,					// data set
	const Scalar **query,				// query set
	const char  *truth_set)				// address of truth set
{
	// -------------------------------------------------------------------------
	//  find ground truth results (using linear scan method)
	// -------------------------------------------------------------------------
	FILE *fp = fopen(truth_set, "w");
	if (!fp) {
		printf("Could not create %s.\n", truth_set);
		return 1;
	}

    double truth_time = MyTimer::measure([&](){
        auto list = make_unique<MaxK_List>(MAXK);
        fprintf(fp, "%d %d\n", qn, MAXK);
        for (int i = 0; i < qn; ++i) {
            list->reset();
            for (int j = 0; j < n; ++j) {
                Scalar ip = calc_l2_dist(d, data[j], query[i]);
                list->insert(ip, j + 1);
            }

            for (int j = 0; j < MAXK; ++j) {
                fprintf(fp, "%d %f ", list->ith_id(j), list->ith_key(j));
            }
            fprintf(fp, "\n");
        }
    });
	fclose(fp);

	printf("Ground Truth: %f Seconds\n\n", truth_time);
	return 0;
}
// -----------------------------------------------------------------------------
int ground_truth_angle(					// find the ground truth results
	int   n,							// number of data points
	int   qn,							// number of query points
	int   d,							// dimension of space
	const Scalar **data,					// data set
	const Scalar **query,				// query set
	const char  *truth_set)				// address of truth set
{
	// -------------------------------------------------------------------------
	//  find ground truth results (using linear scan method)
	// -------------------------------------------------------------------------
	FILE *fp = fopen(truth_set, "w");
	if (!fp) {
		printf("Could not create %s.\n", truth_set);
		return 1;
	}

    double truth_time = MyTimer::measure([&](){
        auto list = make_unique<MinK_List>(MAXK);
        fprintf(fp, "%d %d\n", qn, MAXK);
        for (int i = 0; i < qn; ++i) {
            list->reset();
            for (int j = 0; j < n; ++j) {
                Scalar ip = calc_angle(d, data[j], query[i]);
                list->insert(ip, j + 1);
            }

            for (int j = 0; j < MAXK; ++j) {
                fprintf(fp, "%d %f ", list->ith_id(j), list->ith_key(j));
            }
            fprintf(fp, "\n");
        }
    });
	fclose(fp);

	printf("Ground Truth: %f Seconds\n\n", truth_time);

	return 0;
}