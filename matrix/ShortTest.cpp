#include <assert.h>
#include "Matrix.h"
#include <iostream>

using namespace std;

void new_test(){
    Matrix m(5, 5);
    m.modify(1, 1, 5);
    m.modify(1, 2, 5);
    m.modify(2, 1, 3);
    assert(m.numberOfNonZeroElems(1) == 2);
    m.modify(4, 1, 5);
    assert(m.numberOfNonZeroElems(1) == 3);
}

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);
}
