#ifndef __PRI_QUEUE_H
#define __PRI_QUEUE_H

#include "def.h"
#include <cstdlib>
#include <limits>

// -----------------------------------------------------------------------------
//  MinK_List: a structure which maintains the smallest k values (of type Scalar)
//  and associated object id (of type int).
//
//  This structure is used for ANN search
// -----------------------------------------------------------------------------
class MinK_List {
public:
	MinK_List(int max);				// constructor (given max size)
	~MinK_List();					// destructor

	// -------------------------------------------------------------------------
	void reset() { num_ = 0; }

	// -------------------------------------------------------------------------
	Scalar min_key()	{ return (num_ > 0 ? list_[0].key_ : std::numeric_limits<Scalar>::max()); }

	// -------------------------------------------------------------------------
	Scalar max_key()	{ return (num_ >= k_ ? list_[k_ - 1].key_ : std::numeric_limits<Scalar>::max()); }

	// -------------------------------------------------------------------------
	Scalar ith_key(int i) { return (i < num_ ? list_[i].key_ : std::numeric_limits<Scalar>::max()); }

	// -------------------------------------------------------------------------
	int ith_id(int i) { return (i < num_ ? list_[i].id_ : std::numeric_limits<int>::max()); }

	// -------------------------------------------------------------------------
	int size() { return num_; }

	int getk() {
		return k_; 
	}

	// -------------------------------------------------------------------------
	bool isFull();					// is full?

	// -------------------------------------------------------------------------
	Scalar insert(					// insert item
		Scalar key,						// key of item
		int id);						// id of item

protected:
	int    k_;						// max numner of keys
	int    num_;					// number of key current active
	Result *list_;					// the list itself
};

// -----------------------------------------------------------------------------
//  MaxK_List: An MaxK_List structure is one which maintains the largest k 
//  values (of type Scalar) and associated object id (of type int).
//
//  This structure is used for MIP search
// -----------------------------------------------------------------------------
class MaxK_List {
public:
	MaxK_List(int max);				// constructor (given max size)
	~MaxK_List();					// destructor

	// -------------------------------------------------------------------------
	void reset() { num_ = 0; }

	// -------------------------------------------------------------------------
	Scalar max_key()	{ return num_ > 0 ? list_[0].key_ : std::numeric_limits<Scalar>::min(); }

	// -------------------------------------------------------------------------
	Scalar min_key() { return num_ == k_ ? list_[k_-1].key_ : std::numeric_limits<Scalar>::min(); }

	// -------------------------------------------------------------------------
	Scalar ith_key(int i) { return i < num_ ? list_[i].key_ : std::numeric_limits<Scalar>::min(); }

	// -------------------------------------------------------------------------
	int ith_id(int i) { return i < num_ ? list_[i].id_ : std::numeric_limits<int>::min(); }

	// -------------------------------------------------------------------------
	int size() { return num_; }

	int getk() {
		return k_; 
	}

	// -------------------------------------------------------------------------
	bool isFull();					// is full?

	// -------------------------------------------------------------------------
	Scalar insert(					// insert item
		Scalar key,						// key of item
		int id);						// id of item

private:
	int k_;							// max numner of keys
	int num_;						// number of key current active
	Result *list_;					// the list itself
};

#endif // __PRI_QUEUE_H
