#include <assert.h>
#include <iostream>
#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void new_test(){
    SortedMultiMap smm = SortedMultiMap(relation1);
    smm.add(1,0);
    smm.add(2,4);
    smm.add(1,3);
    smm.add(1,4);
    smm.add(3,4);
    smm.add(1,9);
    smm.add(1,8);
    smm.add(5,4);
    smm.add(1,15);
    int i = 0;
    ValueIterator kit = smm.kiterator(1);
    while(kit.valid()){
        TValue v = kit.getCurrent();
        if(i % 2 == 0)
            assert(v == 2 * i);
        else
            assert(v == 3 * i);
        kit.next();
        i++;
    }
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());
}

