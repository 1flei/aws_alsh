#pragma once

#include <memory>
#include "../util.h"
#include "../pri_queue.h"
#include "../def.h"
#include "../register.h"
#include "../mytimer.h"

// -----------------------------------------------------------------------------
//  interface of this package
// -----------------------------------------------------------------------------
int ground_truth_inner_product(					// find the ground truth results for Euclidean distance
	int   n,							// number of data points
	int   qn,							// number of query points
	int   d,							// dimension of space
	const Scalar **data,					// data set
	const Scalar **query,				// query set
	const char  *truth_set);			// address of truth set

int ground_truth_weighted_distance(					// find the ground truth results
	int   n,							// number of data points
	int   qn,							// number of query points
	int   d,							// dimension of space
	const Scalar **data,					// data set
	const Scalar **query,				// query set
	const Scalar **weight,				// query set
	const char  *truth_set);				// address of truth set

int ground_truth_furthest(					// find the ground truth results
	int   n,							// number of data points
	int   qn,							// number of query points
	int   d,							// dimension of space
	const Scalar **data,					// data set
	const Scalar **query,				// query set
	const char  *truth_set);				// address of truth set

int ground_truth_angle(					// find the ground truth results
	int   n,							// number of data points
	int   qn,							// number of query points
	int   d,							// dimension of space
	const Scalar **data,					// data set
	const Scalar **query,				// query set
	const char  *truth_set);				// address of truth set