#pragma once

#include "def.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <cassert>
#include "pri_queue.h"


// -----------------------------------------------------------------------------
int read_data(						// read data set from disk
	int   n,							// number of data points
	int   d,							// dimensionality
	const char *fname,					// address of data
	Scalar **data);						// data (return)

// -----------------------------------------------------------------------------
int read_ground_truth(				// read ground truth results from disk
	int    qn,							// number of query objects
	const  char *fname,					// address of truth set
	Result **R);						// ground truth results (return)

// -----------------------------------------------------------------------------
Scalar calc_inner_product(			// calc inner product
	int   dim,							// dimension
	const Scalar *p1,					// 1st point
	const Scalar *p2);					// 2nd point
	
// -----------------------------------------------------------------------------
Scalar calc_l2_sqr(					// calc L2 square distance
	int   dim,							// dimension
	const Scalar *p1,					// 1st point
	const Scalar *p2);					// 2nd point

// -----------------------------------------------------------------------------
Scalar calc_l2_dist(					// calc L2 distance
	int   dim,							// dimension
	const Scalar *p1,					// 1st point
	const Scalar *p2);					// 2nd point

// -----------------------------------------------------------------------------
Scalar calc_l1_dist(					// calc L1 distance
	int   dim,							// dimension
	const Scalar *p1,					// 1st point
	const Scalar *p2);					// 2nd point

// -----------------------------------------------------------------------------
Scalar calc_recall(					// calc recall (percentage)
	int   k,							// top-k value
	const Result *R,					// ground truth results 
	MaxK_List *list);					// results returned by algorithms

// -----------------------------------------------------------------------------
int get_hits(						// get the number of hits between two ID list
	int   k,							// top-k value
	int   t,							// top-t value
	const Result *R,					// ground truth results 
	MaxK_List *list);					// results returned by algorithms

// -----------------------------------------------------------------------------
Scalar calc_recall(					// calc recall (percentage)
	int   k,							// top-k value
	const Result *R,					// ground truth results
	MinK_List *list);					// results returned by algorithms
// -----------------------------------------------------------------------------
Scalar calc_weighted_dist2(			// calc inner product
	int   dim,							// dimension
	const Scalar *w,
	const Scalar *p1,					// 1st point
	const Scalar *p2);					// 2nd point

inline int get_num_bits8(uint8_t x)				//get the number of 1 in the binary representation of u
{
	x = (x&0x55) + ((x>>1)&0x55);
	x = (x&0x33) + ((x>>2)&0x33);
	x = (x&0x0f) + ((x>>4)&0x0f);
	return x;
}

inline int get_num_bits64(uint64_t x)			////get the number of 1 in the binary representation of x
{
	x = x - ((x >> 1) & 0x5555555555555555);
    x = (x & 0x3333333333333333) +
        ((x >> 2) & 0x3333333333333333);
    x = ((x + (x >> 4)) & 0x0F0F0F0F0F0F0F0F);
    return (x*(0x0101010101010101))>>56;
}

void calc_min_max(
	int n, 
	int qn,
	int d, 
	const float** data, 
	const float** query, 
	float& maxx, 
	float& minx);

int calc_hamming_dist(			// calc inner product
	int   dim,		
	const uint8_t *p1,					// 1st point
	const uint8_t *p2);					// 2nd point

int calc_hamming_dist(			// calc inner product
	int   dim,		
	const uint64_t *p1,					// 1st point
	const uint64_t *p2);					// 2nd point

Scalar calc_angle(				// calc angle
	int   dim,							// dimension
	const Scalar *p1,					// 1st point
	const Scalar *p2);					// 2nd point


Scalar calc_cosangle(				// calc cos(angle)
	int   dim,							// dimension
	const Scalar *p1,					// 1st point
	const Scalar *p2);					// 2nd point

Scalar calc_ratio(
	int k, 
	const Result *Rs, 
	MinK_List *list);

Scalar calc_ratio(
	int k, 
	const Result *Rs, 
	MaxK_List *list);



template<class Iter>
void print_vec(const Iter &its, int dim)
{
	Iter it = its;
	for(int i=0;i<dim;i++){
		std::cout << *it;
		++it;
		if(i==dim-1){
			std::cout << std::endl;
		} else{
			std::cout << ", ";
		}
	}
}

template<class Iter>
void print_vec(const Iter& its, const Iter& ite, const std::string &header=""){
//	if(verbosity){
	std::cout << header;
	for(Iter it=its; ; ){
		std::cout << *it;
		++it;
		if(it!=ite){
			std::cout << ", ";
		} else{
			std::cout << std::endl;
			break;
		}
	}
//	}
}
template<class Iter, class OStream>
void print_vec(const Iter& its, const Iter& ite, const std::string &header="", OStream &os=std::cout){
//	if(verbosity){
	os << header;
	for(Iter it=its; ; ){
		os << *it;
		++it;
		if(it!=ite){
			os << ", ";
		} else{
			os << std::endl;
			break;
		}
	}
//	}
}

#if __cplusplus < 201402L
//make_unique, which is available in c++17
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
#else
using std::make_unique;
#endif

inline uint64_t hash_combine(uint64_t h0, uint64_t h1)
{
    return h0 ^ (0x9e3779b9 + (h0<<6) + (h0>>2) + h1);
}

//return idx such that xs[idx[i]] is sorted for i in range(beign, end)
//require begin and end are randomly accessable!!
template<typename T, typename F>
std::vector<int> argsort(const T& begin, const T& end, const F& cmp)
{
	size_t len = distance(begin, end);
	std::vector<int> idx(len);
	for(int i=0;i<idx.size();i++){
		idx[i] = i;
	}
	std::sort(idx.begin(), idx.end(), [&](int a, int b){
		return cmp(*(begin+a), *(begin+b));
	});
	return idx;
}
template<typename T>
std::vector<int> argsort(const T& begin, const T& end)
{
	size_t len = distance(begin, end);
	std::vector<int> idx(len);
	for(int i=0;i<idx.size();i++){
		idx[i] = i;
	}
	std::sort(idx.begin(), idx.end(), [&](int a, int b){
		return *(begin+a)<*(begin+b);
	});
	return idx;
}

template<typename Iter>
void scatter(const Iter& begin, std::vector<int> &idx)
{
    using T = typename std::iterator_traits<Iter>::value_type;
	std::vector<T> tmpxs(begin, begin+idx.size());
	for(int i=0;i<idx.size();i++){
		*(begin+i) = tmpxs[idx[i]];
	}
}


template<class uintt>
struct CountMarkerU
{
	std::vector<uintt> markCount;
	uintt curCnt;
	CountMarkerU(int sz=0):markCount(sz), curCnt(1){}


	void resize(int n){
		markCount.resize(n);
		fill(markCount.begin(), markCount.end(), 0);
	}

	void mark(int n){
		markCount[n] = curCnt;
	}
	bool isMarked(int n){
		return markCount[n] >= curCnt;
	}
	void clear(){
		if(curCnt==~uintt(0)){
			curCnt=1;
			markCount.clear();
		} else{
			curCnt++;
		}
	}
};

using CountMarker = CountMarkerU<unsigned>;