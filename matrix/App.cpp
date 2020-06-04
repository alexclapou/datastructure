
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;


int main() {
    new_test();
	testAll();
	testAllExtended();
	cout << "Test End" << endl;
	system("pause");
}
