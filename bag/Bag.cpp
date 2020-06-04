#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	unique_capacity = 0;
    positions_capacity = 0;
    unique_length = 0;
    positions_length = 0;
    u = new TElem[1];
    p = new TElem[1];
}

void Bag::add(TElem elem) {
	int elem_found;

    elem_found = -1;
    for(int i = 0; i < unique_length; i++)
        if(elem == u[i])
            elem_found = i;
    if(unique_capacity == unique_length){
        unique_capacity = unique_capacity+5;
        TElem *new_u = new TElem[unique_capacity];
        for(int i = 0; i < unique_length; i++)
            new_u[i] = u[i];
        delete u;
        u = new_u;
    }
    if(positions_capacity == positions_length){
        positions_capacity = positions_capacity+5;
        TElem *new_p = new TElem[positions_capacity];
        for(int i = 0; i < positions_length; i++)
            new_p[i] = p[i];
        delete p;
        p = new_p;
    }
    if(elem_found == -1){
        u[unique_length] = elem;
        p[positions_length] = unique_length;
        unique_length++;
        positions_length++;
    }
    else{
        p[positions_length] = elem_found;
        positions_length++;
    }
}
/*
bool Bag::remove(TElem elem) {
	if(search(elem) == false || size() == 0)
        return false; 

    int elem_index, temp_index;

    elem_index = -1;
    for(int i = 0; i < unique_length && elem_index == -1; i++)
        if(u[i] == elem)
            elem_index = i;
    if(nrOccurrences(elem) == 0){
        for(int i = elem_index; i < unique_length-1; i++)
            u[i] = u[i+1];
        unique_length--;
    }
    for(int i = 0; i < positions_length; i++)
        if(p[i] == elem_index)
            temp_index = i;
    for(int i = temp_index; i < positions_length-1; i++)
        p[i] = p[i+1];
    positions_length--;
    return true; 
}
*/
bool Bag::remove(TElem elem){
    if(size() == 0 || search(elem) == false)
        return false;
    int elem_index, temp_index;

    elem_index = -1;
    for(int i = 0; i < unique_length; i++)
        if(u[i] == elem)
            elem_index = i;
    if(nrOccurrences(elem) == 1){
        for(int i = elem_index; i < unique_length-1; i++)
            u[i] = u[i+1];
        unique_length--;
        for(int i = 0; i < positions_length; i++)
            if(p[i] > elem_index)
                p[i]--;
    }
    for(int i = 0; i < positions_length; i++)
        if(p[i] == elem_index)
            temp_index = i;
    for(int i = temp_index; i < positions_length-1; i++)
        p[i] = p[i+1];
    positions_length--;
    return true;
}

/*function toSet()is:
 *  number_of_removed <- 0
 *  for i <- 0, unique_length execute:
 *      while nrOccurrences(u[i]) != 1 execute:
 *          remove(u[i])
 *          number_of_removed <- number_of_removed + 1
 *      end-while
 *  end-for
 *  toSet <- number_of_removed
 *end-function O(n^3)*/

int Bag::toSet()
{
    int number_of_removed;

    number_of_removed = 0;
    for(int i = 0; i < unique_length; i++)
        while(nrOccurrences(u[i]) != 1){
            remove(u[i]);
            number_of_removed++;
        }
    return number_of_removed;
}

bool Bag::search(TElem elem) const {
    for(int i = 0; i < unique_length; i++)
        if(elem == u[i])
            return true;
    return false; 
}

int Bag::nrOccurrences(TElem elem) const {
	if(size() == 0 || search(elem) == false)
        return 0;
	int number_occurrences, elem_index;

    number_occurrences = 0;
    elem_index = -1;
    for(int i = 0; i < unique_length && elem_index == -1; i++)
        if(elem == u[i])
            elem_index = i;
    for(int i = 0; i < positions_length; i++)
        if(p[i] == elem_index)
            number_occurrences++;
    return number_occurrences;
}

int Bag::size() const {
	return positions_length;
}

bool Bag::isEmpty() const {
    if(size() == 0)
        return true;
	return false;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

Bag::~Bag() {
	delete[] u;
    delete[] p;
}

