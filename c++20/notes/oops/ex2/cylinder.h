#ifndef CYLINDER_H
#define CYLINDER_H

#include "constants.h"

class Cylinder {
	public: 
		// Constructors
		Cylinder() = default;
		Cylinder(double r, double h);

		// member functions(methods)
		double volume(){
			return PI*radius*radius*height;
		}

		double get_radius(){ 
			return radius;
		}

		double get_height(){
			return height;
		}

		void set_radius(double r){
			radius = r;
		}
		void set_height(double h){
			height = h;
		}

	private: 
		// member variables
		double radius = 1;
		double height = 1;
};

#endif
