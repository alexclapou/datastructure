#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    new_tests();
    testAll();
	testAllExtended();

    std::cout<<"Finished SMM Tests!"<<std::endl;
}
