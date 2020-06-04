#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

//Theta(capacity)
SortedMultiMap::SortedMultiMap(Relation r) {
    //basic for slla
    relation = r;
    capacity = 5;
    total_length = 0;
    elements = new TElem[capacity];
    next = new int[capacity];
    values = new SLLAvalues[capacity];

    for(int i = 0; i < capacity; i++){
        next[i] = i+1;

        //initialize values slla for every first [capacity] keys
        init_SSLAvalues(values[i]);
    }
    next[capacity-1] = -1;
    first_empty = 0;
    length = 0;
    head = 0;
}

//O(n^2)
void SortedMultiMap::add(TKey c, TValue v) {
    if(isEmpty()){
        elements[first_empty].first = c;
        values[first_empty].value[values[first_empty].first_empty] = v;
        values[first_empty].first_empty = values[first_empty].next[values[first_empty].first_empty];
        values[first_empty].length++;
        length++;
        first_empty = next[first_empty];
    }
    else{
        bool key_found;
        int d;

        key_found = false;
        d = 0;
        for(int i = head; d < length;){
            if(elements[i].first == c){
                if(values[i].first_empty == -1){
                    values[i].first_empty = values[i].capacity;
                    values[i].capacity *= 2;
                    TValue *new_value = new TValue[values[i].capacity];
                    TValue *new_next = new int[values[i].capacity];
                    for(int J = 0; J < values[i].length; J++)
                        new_value[J] = values[i].value[J];
                    for(int J = 0; J < values[i].capacity; J++)
                        new_next[J] = J+1;
                    delete []values[i].value;
                    delete []values[i].next;
                    values[i].value = new_value;
                    values[i].next = new_next;
                    values[i].next[values[i].capacity-1] = -1;
                }
                values[i].value[values[i].first_empty] = v;
                values[i].first_empty = values[i].next[values[i].first_empty];
                values[i].length++;
                key_found = true;
            }
            i = next[i];
            d++;
        }
        if(!key_found){
            if(first_empty == -1){
                first_empty = capacity;
                capacity *= 2;
                TElem *new_elements = new TElem[capacity];
                int *new_next = new int[capacity];
                SLLAvalues *new_values = new SLLAvalues[capacity];
                for(int i = 0; i < capacity; i++)
                    new_next[i] = i+1;
                for(int i = 0; i < length; i++)
                    new_elements[i] = elements[i];
                for(int i = 0; i < length; i++)
                    new_values[i] = values[i];
                for(int i = length; i < capacity; i++)
                    init_SSLAvalues(new_values[i]);
                delete []values;
                delete []next;
                delete []elements;
                elements = new_elements;
                next = new_next;
                values = new_values;
                next[capacity-1] = -1;
            }
            elements[first_empty].first = c;
            values[first_empty].value[values[length].first_empty] = v;
            values[first_empty].first_empty = values[length].next[values[length].first_empty];
            values[first_empty].length++;
            first_empty = next[first_empty];
            length++;
        }
    }
    for(int i = head, d = 0; d < length-1; d++){
        for(int j = next[i], D = 0; D < length-1-i; D++){
            if(!relation(elements[i].first, elements[j].first)){
                swap(elements[i].first, elements[j].first);
                SLLAvalues aux;
                aux = values[i];
                values[i] = values[j];
                values[j] = aux;
            }
            j = next[j];
        }
        i = next[i];
    }
    total_length++;
}

//O(n^2)
vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> key_values;
    for(int i = head, d = 0; d < length;d++){
        if(elements[i].first == c){
            for(int j = values[i].head, D = 0; D < values[i].length; D++){
                key_values.push_back(values[i].value[j]);
                j = values[i].next[j];
            }
            return key_values;
        }
        i = next[i];
    }
    return key_values;
}

//O(n^2)
bool SortedMultiMap::remove(TKey c, TValue v) {
    if(size() == 0)
        return false;

    vector<TValue> key_values = search(c);
    if(key_values.size() == 0)
        return false;

    bool value_exist = false;
    for(TValue value:key_values)
        if(value == v)
            value_exist = true;
    if(value_exist == false)
        return false;

    int pair_found;

    pair_found = -1;
    for(int i = head, d = 0; d < length && pair_found == -1; d++){
        if(elements[i].first == c)
            pair_found = i;
        i = next[i];
    }
    int value_found;

    value_found = -1;
    for(int i = values[pair_found].head, d = 0; d < values[pair_found].length && value_found == -1; d++){
        if(values[pair_found].value[i] == v)
            value_found = i;
        i = values[pair_found].next[i];
    }
    //std::cout<<pair_found<<" "<<value_found<<'\n';
    //for every remove we have 2 cases - first case when we remove a head, and the second one when we remove something else
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    for(int i = values[pair_found].head, d = 0; d < values[pair_found].length; d++){
        if(value_found == values[pair_found].head){
            if(values[pair_found].length != 1)
               values[pair_found].head = values[pair_found].next[head];
            else
                values[pair_found].head = 0;
        }
        else{
            if(values[pair_found].next[i] == value_found){
                values[pair_found].next[i] = values[pair_found].next[value_found];
            }
        }
        i = values[pair_found].next[i];
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    values[pair_found].length--;
    if(values[pair_found].length == 0){
        if(head == pair_found){
            int aux;
            aux = head;
            head = next[head];
            first_empty = aux;
        }
        else
            for(int i = head, d = 0; d < length; d++){
                if(i == pair_found)
                   next[pair_found] = next[i];
             i = next[i];
            }
    }
    total_length--;
    return true;
}

//Theta1
int SortedMultiMap::size() const {
    return total_length;
}

//Theta1
bool SortedMultiMap::isEmpty() const {
    return total_length == 0;
}

//Theta1
SMMIterator SortedMultiMap::iterator() const {
return SMMIterator(*this);
}

//Theta(capacity)
SortedMultiMap::~SortedMultiMap() {
    for(int i = 0; i < capacity; i++){
        if(values[i].next != nullptr)
            delete []values[i].next;
        if(values[i].value != nullptr)
            delete []values[i].value;
    }
    delete []values;
    delete []elements;
    delete []next;
}


//get all the elements for the given key with search function
//if the returned value is 0 then we don t have the key
//then iterate the returned vector and remove every value of the key, when the key has 0 values the key is removed 
//O(n^3)
vector<TValue> SortedMultiMap::removeKey(TKey key){
    vector<TValue> removed_elements = search(key);
    if(removed_elements.size() == 0)
        return removed_elements;
    int pair_found;
    for(TValue value:removed_elements){
        remove(key, value);
    }
    return removed_elements;
}






