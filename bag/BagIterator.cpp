#include <exception>
#include "BagIterator.h"
#include "Bag.h"
#include <iostream>
using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	elem_index = 0;
}
void BagIterator::first() {
	elem_index = 0;
}


void BagIterator::next() {
	if(valid()){
        elem_index++;
    }
    else{
        throw runtime_error{ "" };
    }
}


bool BagIterator::valid() const {
	if(elem_index < bag.positions_length && elem_index >= 0)
        return true;
	return false;
}



TElem BagIterator::getCurrent() const
{
	  if(valid() == false)
        throw runtime_error{ "" };
    return bag.u[bag.p[elem_index]]; 

}
