#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>
#include <cassert>

using namespace std;

void test_new()
{
    Bag b;
    b.add(10);
    b.add(5);
    b.add(1);
    b.add(7);
    b.add(-3);
    assert(b.toSet() == 0);
    b.add(5);
    assert(b.toSet() == 1);
    b.add(10);
    b.add(11);
    b.add(5);
    b.add(11);
    b.add(1);
    b.add(5);
    b.add(5);
    b.add(5);
    b.add(-3);
    b.add(5);
    b.add(1);
    b.add(5);
    assert(b.toSet() == 11);//1+2+1+1+7-1
}

int main() {

    test_new();
	testAll();
	cout << "Short tests over" << endl;
	testAllExtended();

	cout << "All test over" << endl;
}
