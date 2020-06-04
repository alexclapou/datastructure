#include "SMMIterator.h"
#include <iostream>
#include "SortedMultiMap.h"


//O(n)
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    node = map.bst;
    while(node != nullptr){
        it_stack.push(node);
        node = node->left;
    }
    if(!it_stack.empty())
        current_node = it_stack.top();
    else
        current_node = nullptr;
}
//O(n)
void SMMIterator::first(){
    while(!it_stack.empty())
        it_stack.pop();
    node = map.bst;
    while(node != nullptr){
        it_stack.push(node);
        node = node->left;
    }
    if(!it_stack.empty())
        current_node = it_stack.top();
    else
        current_node = nullptr;
}

//O(n)
void SMMIterator::next(){
    if(it_stack.empty())
        throw std::out_of_range("out of range");
    BSTNode *node = it_stack.top();
    it_stack.pop();
    if(node->right != nullptr){
        node = node->right;
        while(node != nullptr){
            it_stack.push(node);
            node = node->left;
        }
    }
    if(!it_stack.empty())
        current_node = it_stack.top();
    else
        current_node = nullptr;
}
//T(1)
bool SMMIterator::valid() const{
    if(current_node == nullptr)
        return false;
    return true;
}
//T(1)
TElem SMMIterator::getCurrent() const{
    if(valid())
        return current_node->data;
    throw std::out_of_range("out of range");
}

ValueIterator::ValueIterator(const SortedMultiMap& d, TKey k): map(d){
    key = k;
    node = map.bst;
    while(node != nullptr){
        it_stack.push(node);
        node = node->left;
    }
    if(!it_stack.empty()){
        current_node = it_stack.top();
        if(current_node->data.first != key)
            next();
    }
    else
        current_node = nullptr;
}

void ValueIterator::first(){
    while(!it_stack.empty())
        it_stack.pop();
    node = map.bst;
    while(node != nullptr){
        if(node->data.first == key)
            it_stack.push(node);
        node = node->left;
    }
    if(!it_stack.empty()){
        current_node = it_stack.top();
        if(current_node->data.first != key)
            next();
    }
    else
        current_node = nullptr;
}

void ValueIterator::next(){
    if(it_stack.empty())
        throw std::out_of_range("out of range");
    BSTNode *node = it_stack.top();
    it_stack.pop();
    if(node->right != nullptr){
        node = node->right;
        while(node != nullptr){
            it_stack.push(node);
            node = node->left;
        }
    }
    if(!it_stack.empty()){
        current_node = it_stack.top();
        if(current_node->data.first != key){
            next();
        }
        else return;
    }
    else
        current_node = nullptr;
}

bool ValueIterator::valid()const{
    if(current_node == nullptr)
        return false;
    return true;
}

TValue ValueIterator::getCurrent()const{
    return current_node->data.second;
}
