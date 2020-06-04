#include <stdexcept>
#include <iostream>
#include <stdexcept>
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"


//Theta(1)
IteratedList::IteratedList() {
    head = nullptr;
    list_length = 0;
}

//Theta(1)
int IteratedList::size() const {
    return list_length;
}

//Theta(1)
bool IteratedList::isEmpty() const {
    return (list_length == 0);
}

//Theta(1)
ListIterator IteratedList::first() const {
	return ListIterator(*this);
}

//Theta(1)
TElem IteratedList::getElement(ListIterator pos) const {
    if(pos.valid())
        return pos.getCurrent();
    throw std::out_of_range("not valid");
}

//O(n)
TElem IteratedList::remove(ListIterator& pos) {
    if(!pos.valid())
        throw std::out_of_range("not valid");
    TElem data_removed;
    Node *keep_node;

    list_length--;
    data_removed = pos.getCurrent();
    if(pos.current_node == head){
        keep_node = head->next;
        delete head;
        head = keep_node;
        pos.current_node = head;
    }
    else{
        keep_node = pos.current_node->next;
        if(keep_node != nullptr){
            pos.current_node->data = keep_node->data;
            pos.current_node->next = keep_node->next;
            delete keep_node;
        }
        else{
            Node *last_new;

            last_new = head;
            while(last_new->next->next != nullptr){
                last_new = last_new->next;
            }
            last_new->next = nullptr;
            delete pos.current_node;
            pos.current_node = last_new;
        }
    }
    return data_removed;
}

//O(list_length)
ListIterator IteratedList::search(TElem e) const{
    ListIterator new_iterator = first();
    while(new_iterator.valid()){
        if(new_iterator.getCurrent() == e)
            return new_iterator;
        new_iterator.next();
    }
    return new_iterator;
}

//Theta(1)
TElem IteratedList::setElement(ListIterator pos, TElem e) {
    if(pos.valid()){
        TElem old_data;

        old_data = pos.getCurrent();
        pos.current_node->data = e;
        return old_data;
    }
    throw std::out_of_range("not valid");
}

//Theta(1)
void IteratedList::addToPosition(ListIterator& pos, TElem e) {
    if(!pos.valid())
        throw std::out_of_range("not valid");
    Node *new_node, *temp_node;

    new_node = new Node;
    temp_node = pos.current_node;
    new_node->data = e;
    new_node->next = pos.current_node->next;
    temp_node->next = new_node;
    list_length++;
    pos.current_node = new_node;
}

//Theta(1)
void IteratedList::addToBeginning(TElem e)
{
    Node *new_head, *temp_node;

    new_head = new Node;
    temp_node = head;
    head = new_head;
    head->next = temp_node;
    head->data = e;
    list_length++;
}

//we get the first element from the list
//create an iterator for the list
//then loop the list and if we get index==k delete the element and increase the number of removed elements
//if index!=k then go next element and increase index(remove(it) removes the iterator with the next position)
//complexity:O(n^2)
int IteratedList::removeFromKtoK(int k){
    if(k <= 0)
        throw std::out_of_range("invalid k");
    if(k > size())
        return 0;
    if(size () == 0)
        return 0;
    int index;
    int nr_removed;

    index = 1;
    first();
    nr_removed = 0;
    int first_element = getElement(first());
    ListIterator it = search(first_element);
    while(it.valid()){
        if(index == k){
            index = 1;
            remove(it);
            nr_removed++;
        }
        else{
            index++;
            it.next();
        }
    }
    return nr_removed;
}

//O(n)
void IteratedList::addToEnd(TElem e) {
    if(head == nullptr){
        head = new Node;

        head->next = nullptr;
        head->data = e;
    }
    else{
        Node *new_node, *current_node;

        current_node = head;
        new_node = new Node;
        while(current_node->next != nullptr)
            current_node = current_node->next;
        current_node->next = new_node;
        new_node->data = e;
        new_node->next = nullptr;
    }
    list_length++;
}

//Theta(n)
IteratedList::~IteratedList() {
    Node *next_node;

    while(head != nullptr){
        next_node = head->next;
        delete head;
        head = next_node;
    }
    head = nullptr;
}

