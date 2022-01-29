#include <iostream>
#include "cylinder.h"

// Pre processor directives will put the constants and the cylinder def from header to main.cpp

int main(){
	
	Cylinder c(10, 10);

	std::cout << "Volume = "  << c.volume() << std::endl;	

	return 0;
}
