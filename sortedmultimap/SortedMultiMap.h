#pragma once
#include <iostream>
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111
#define NULL_TELEM pair<TKey, TValue>(-11111, -11111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

struct SLLAvalues{
    TValue *value;
    int *next;
    int capacity;
    int first_empty;
    int length;
    int head;
};

//values for every pair
static void init_SSLAvalues(SLLAvalues &list_of_values)
{
    list_of_values.head = 0;
    list_of_values.capacity = 5;
    list_of_values.value = new TValue[list_of_values.capacity];
    list_of_values.next = new int[list_of_values.capacity];
    for(int i = 0; i < list_of_values.capacity; i++){
        list_of_values.next[i] = i+1;
    }
    list_of_values.next[list_of_values.capacity-1] = -1;
    list_of_values.first_empty = 0;
    list_of_values.length = 0;
}

class SortedMultiMap {
	friend class SMMIterator;
    private:
    TElem *elements;
    SLLAvalues *values;
    int *next;

    int head;
    Relation relation;
    int capacity;
    int total_length;
    int length;
    int first_empty;

    public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    //removes a key together with all its values
    //returns a vector with the values that were previously associated to this value (and were removed)
    vector<TValue> removeKey(TKey key);

    // destructor
    ~SortedMultiMap();
};
