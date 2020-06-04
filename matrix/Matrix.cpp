#include "Matrix.h"
#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;


//T(1)
Matrix::Matrix(int nrLines, int nrCols) {
	nr_lines = nrLines;
	nr_columns = nrCols;
	capacity = 6;
    total = 0;
    i_random = rand() % capacity;
    j_random = rand() % capacity;
	elements = new Node*[capacity];
	for (int i = 0; i < capacity; ++i)
	{
		Node* node = new Node;
		elements[i] = node;
	}
}

//T(total)
int Matrix::numberOfNonZeroElems(int col)const{
    if(col < 0 || col > nrColumns())
        throw std::out_of_range("out of range");
    int c = 0;
    for(int i = 0; i < capacity; i++){
        Node *c_node = elements[i];
        while(c_node!= nullptr && c_node->column != -1){
            if(c_node->column == col)
                c++;
            c_node = c_node->next;
        }
    }
    return c;
}

//O();
void Matrix::resize(){
    Node *all_elements = new Node[total];
    Node **new_elements = new Node*[capacity*2];
    int index;

    index = 0;
    for(int i = 0; i < capacity; i++){
        Node *c_node = elements[i];
        while(c_node != nullptr && c_node->line != -1){
            all_elements[index] = *c_node;
            index++;
            c_node = c_node->next;
        }
    }
    for(int i = 0; i < capacity; i++){
        Node *next_node;
        while(elements[i] != nullptr){
            next_node = elements[i]->next;
            delete elements[i];
            elements[i] = next_node;
        }
    }
    delete []elements;
    elements = new_elements;
    capacity *= 2;
    change_randoms(i_random, j_random);
    for(int i = 0; i < capacity; i++){
		Node* node = new Node;
		elements[i] = node;
    }
    for(int i = 0; i < total; i++){
        int hash_pos = hash(all_elements[i].line, all_elements[i].column);
        if(elements[hash_pos]->next == nullptr && elements[hash_pos]->column == -1){
			elements[hash_pos]->data = all_elements[i].data;
			elements[hash_pos]->column = all_elements[i].column;
			elements[hash_pos]->line = all_elements[i].line;
        }
		else
		{
            Node *current_node = elements[hash_pos];
            Node *new_node = new Node;

            new_node->column = all_elements[i].column;
            new_node->line = all_elements[i].line;
            new_node->data = all_elements[i].data;
            if(!orderedL(current_node, new_node)){
                new_node->next = current_node;
                elements[hash_pos] = new_node;
                continue;
            }
            int flag = 0;
            while(current_node->next != nullptr && !flag){
                Node *next_node = current_node->next;
                if(!orderedL(next_node, new_node)){
                    new_node->next = next_node;
                    current_node->next = new_node;
                    flag = 1;
                }
                current_node = current_node->next;
            }
            if(flag)continue;
            current_node->next = new_node;
		}
    }
    delete []all_elements;
}

//T(1)
void Matrix::change_randoms(int &random1, int &random2){
    random1 = rand() % capacity;
    random2 = rand() % capacity;
}


//T(1)
int Matrix::nrLines() const {
	return nr_lines;
}


//T(1)
int Matrix::nrColumns() const {
	return nr_columns;
}

//O(n) n - number of elements in a linked list
TElem Matrix::element(int i, int j) const {
	if (i >= nr_lines || j >= nr_columns || i < 0 || j < 0)
		throw std::out_of_range("Out of range");
    int hash_pos = hash(i, j);

    Node *current_node = elements[hash_pos];
    while(current_node != nullptr){
        if(current_node->column == j && current_node->line == i)
            return current_node->data;
        current_node = current_node->next;
    }
	return NULL_TELEM;
}

//O(n) n - number of elements in a linked list
TElem Matrix::modify(int i, int j, TElem e) {
    if(i < 0 || j < 0 || i >= nrLines() || j >= nrColumns())
        throw std::out_of_range("eeout of range");
	int hash_pos;
	int head = 0;
    int prev_value;
    Node *prev_node;

    if(float(total) / float(capacity) >= 0.7)
        resize();
    hash_pos = hash(i, j);
    Node *c_node = elements[hash_pos];
	while (c_node != nullptr)
	{
		if (c_node->column == j && c_node->line == i)
		{
			if(e == NULL_TELEM && c_node->data != NULL_TELEM)
			{
                total--;
                Node *temp_node;

                prev_value = c_node->data;
                temp_node = c_node->next;
                if(c_node == elements[hash_pos]){
                    delete elements[hash_pos];
                    if(temp_node == nullptr)
                        elements[hash_pos] = new Node;
                    else
                        elements[hash_pos] = temp_node;
                    return prev_value;
                }
                else{
                    if(temp_node == nullptr){
                        delete c_node;
                        c_node = nullptr;
                        prev_node->next = c_node;
                        return prev_value;
                    }
                    c_node->data = temp_node->data;
                    c_node->line = temp_node->line;
                    c_node->column = temp_node->column;
                    c_node->next = temp_node->next;
                    delete temp_node;
                    temp_node = nullptr;
                    return prev_value;
                }
			}
            if(e != NULL_TELEM && c_node->data != NULL_TELEM)
			{
                prev_value = c_node->data;
                c_node->data = e;
                return prev_value;
			}
		}
        prev_node = c_node;
        c_node = c_node->next;
	}
	if(e != NULL_TELEM)
	{
        total++;
		if(elements[hash_pos]->next == nullptr && elements[hash_pos]->column == -1)
		{
			elements[hash_pos]->data = e;
			elements[hash_pos]->column = j;
			elements[hash_pos]->line = i;
            return NULL_TELEM;
		}
		else
		{
            Node *current_node = elements[hash_pos];
            Node *new_node = new Node;

            new_node->column = j;
            new_node->line = i;
            new_node->data = e;
            if(!orderedL(current_node, new_node)){
                new_node->next = current_node;
                elements[hash_pos] = new_node;
                return NULL_TELEM;
            }
            while(current_node->next != nullptr){
                Node *next_node = current_node->next;
                if(!orderedL(next_node, new_node)){
                    new_node->next = next_node;
                    current_node->next = new_node;
                    return NULL_TELEM;
                }
                current_node = current_node->next;
            }
            current_node->next = new_node;
		}
	}
    // 0 0
	return NULL_TELEM;
}
void Matrix::show(){
    for(int i = 0; i < capacity; i++){
        Node *current_node = elements[i];
        while(current_node != nullptr){
            std::cout<<current_node->line<<" "<<current_node->column<<"---"<<current_node->data<<'\n';
            current_node = current_node->next;
        }
        std::cout<<'\n';
    }
    std::cout<<total<<" "<<capacity;
}

//T(1)
int Matrix::orderedL(Node *n1, Node *n2){
    if(n1->line < n2->line)
        return 1;
    else{
        if(n1->line > n2->line)
            return 0;
        else
            if(n1->column < n2->column)
                return 1;
            else
                if(n1->column > n2->column)
                    return 0;
                else
                    return 1;
    }
}

//T(1)
int Matrix::hash(int i, int j)const
{
    int result_hash = i*i_random + j*j_random;
    result_hash = result_hash % capacity;
    return result_hash;
}

Matrix::~Matrix(){
    for(int i = 0; i < capacity; i++){
        Node *next_node;
        while(elements[i] != nullptr){
            next_node = elements[i]->next;
            delete elements[i];
            elements[i] = next_node;
        }
    }
    delete []elements;
}
