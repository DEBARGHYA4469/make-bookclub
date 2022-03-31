#ifndef POINT_H 
#define POINT_H

#include <iostream>

class Point{
	private: 
		double *x, *y; 

		void invalidate(){
			x = nullptr;
			y = nullptr;
		}
	public:
	       Point(double x_param, double y_param); 
       	       ~Point(); 

	       // Copy constructor
	       Point(const Point& source_point);

	       // Move constructor
	       Point(Point&& source_point);

	       // Setters
	       void set_x(double x){ *(this->x) = x; }
	       void set_y(double y){ *(this->y) = y; }

	       // Getters 
	       double *get_x() const { return x; }
	       double *get_y() const { return y; }

	       double *steal_x(){
	       		double *new_x  = x;
			x = nullptr;
			return new_x;
	       }

	       double *steal_y(){
	       		double *new_y = y;
			y = nullptr;
			return new_y;
	       }

               void print_info() const {
	       		cout << "Hello " << endl;
	       } 	       
}; 

#endif 
