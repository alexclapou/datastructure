#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);
    int current_pair;
    int current_value;
    int index;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};
    //removes a key together with all its values
    //returns a vector with the values that were previously associated to this value (and were removed)
    vector<TValue> removeKey(TKey key);

