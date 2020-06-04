#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

int main() {
    new_tests();
	testAll();
	testAllExtended();
	std::cout << "Finished LP Tests!" << std::endl;
}
