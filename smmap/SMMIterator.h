#pragma once

#include "SortedMultiMap.h"
#include <stack>

//creates an iterator over the values associated to key k.  If k is not in the SortedMultiMap the iterator is invalid after creation, otherwise, the current element is the first value associated to the key

//Create the ValueIterator class with the same operations as the regular SortedMultiMapIterator, except that the constructor of the ValueIterator receives as parameter the SortedMultiMap and the key and the getCurrent operation returns a TValue.


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);
    BSTNode *node;
    stack<BSTNode*> it_stack;
    BSTNode *current_node;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

class ValueIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
    TKey key;
	const SortedMultiMap& map;
	ValueIterator(const SortedMultiMap& map, TKey k);
    BSTNode *node;
    stack<BSTNode*> it_stack;
    BSTNode *current_node;

public:
	void first();
	void next();
	bool valid() const;
   	TValue getCurrent() const;
};
