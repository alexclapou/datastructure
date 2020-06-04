#include "SMMIterator.h"
#include <stdexcept>
#include "SortedMultiMap.h"

//Theta1
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    current_pair = map.head;
    current_value = map.values[current_pair].head;
    index = 0;
}

//Theta1
void SMMIterator::first(){
    current_pair = map.head;
    current_value = map.values[current_pair].head;
    index = 0;
}

//Theta1
void SMMIterator::next(){
    if(valid()){
        if(map.values[current_pair].next[current_value] != map.values[current_pair].first_empty)
            current_value = map.values[current_pair].next[current_value];
        else{
            current_pair = map.next[current_pair];
            current_value = map.values[current_pair].head;
        }
        index++;
    }
    else
        throw std::out_of_range("not valid!");
}

//Theta1
bool SMMIterator::valid() const{
    if(index < map.size())
        return true;
    return false;
}

//Theta1
TElem SMMIterator::getCurrent() const{
    if(!valid())
        throw std::out_of_range("not valid!");
    if(map.values[current_pair].next[current_value] != -1)
        map.elements[current_pair].second = map.values[current_pair].value[current_value];
    return map.elements[current_pair];
}

