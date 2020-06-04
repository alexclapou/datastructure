#pragma once
//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

struct Node {
    int line = -1, column = -1;
    TElem data = NULL_TELEM;
    Node* next = nullptr;
};

class Matrix {

private:
    int nr_lines;
    int nr_columns;
    int capacity;
    int total;
    int i_random, j_random;
    bool resized;
    Node** elements;

    int hash(int i, int j)const;
    int orderedL(Node *n1, Node *n2);
    void change_randoms(int &random1, int &random2);
public:
    void resize();
    //returns the number of non-zero elements from a given column
    //throws an exception if col is not valid
    int numberOfNonZeroElems(int col) const;
    void show();
    //constructor
    Matrix(int nrLines, int nrCols);

    //returns the number of lines
    int nrLines() const;

    //returns the number of columns
    int nrColumns() const;

    //returns the element from line i and column j (indexing starts from 0)
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    //modifies the value from line i and column j
    //returns the previous value from the position
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);

    ~Matrix();
};
