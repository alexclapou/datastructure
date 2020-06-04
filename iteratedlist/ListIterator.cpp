#include "ListIterator.h"
#include <stdexcept>
#include "IteratedList.h"
#include <exception>

ListIterator::ListIterator(const IteratedList& list) : list(list) {
    if(list.isEmpty())
        current_node = nullptr;
    else
        current_node = list.head;
}

void ListIterator::first() {
    current_node = list.head;
}

void ListIterator::next() {
    if(valid())
        current_node = current_node->next;
    else
        throw std::out_of_range("invalid iterator");
}

bool ListIterator::valid() const {
    if(current_node == nullptr)
        return  false;
    return true;
}

TElem ListIterator::getCurrent() const {
    if(valid())
        return current_node->data;
    throw std::out_of_range("not valid");
}
