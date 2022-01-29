#include <iostream>
#include "cylinder.h"

// Pre processor directives will put the constants and the cylinder def from header to main.cpp

int main(){
	
	Cylinder c(10, 10);

	std::cout << "Volume = "  << c.volume() << std::endl;	

	// Managing a stack object through pointers, but ugly implementation 
	Cylinder *p_cyl = &c;
	std::cout << "Volume = " << p_cyl->volume() << std::endl;
	
	p_cyl->set_radius(2);
	std::cout << "New volume: " << c.volume() << std::endl;

	//Create a cylinder heap object through new operator
	Cylinder *p_cyl2 = new Cylinder(100, 2);
	std::cout << "Volume 2: " << p_cyl2->volume() << std::endl;

	return 0;
}
