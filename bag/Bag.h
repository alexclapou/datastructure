#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -11111;
typedef int TElem;
class BagIterator; 
class Bag {

private:
	TElem *u; //Unique elements list
    TElem *p; //positions list
    int unique_length; // length of the unique list
    int positions_length; //length of the position list(length of the bag/ thenumber of elements in the bag)
    int unique_capacity; // capacity of the unique list
    int positions_capacity; //capacity of the positions list


	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

    //keeps only one occurrence of all elements from the Bag
    //returns the number of removed elements
    int toSet();

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();
};
