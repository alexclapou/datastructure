#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    new_test();
    testAll();
	testAllExtended();

    std::cout<<"Finished SMM Tests!"<<std::endl;
	system("pause");
}
