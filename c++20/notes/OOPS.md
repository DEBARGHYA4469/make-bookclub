### CLASSES

```cpp
	class Cylinder{
		private: 
			double radii = 1.0;
			double ht = 1.0;	
		public: 
			Cylinder(){
				radii = 2.0;
				ht = 2.0;
			}

			Cylinder(double r, double h){
				radii = r;
				ht = h;	
			}

			double volume(){
				return PI*radii*radii*ht;
			}	
	};	
```

CONSTRUCTORS: 

* Constructors have no return type. 

* Same name as the class.

* Can have parameter. Can also have an empty parameter list.

* Used to initialize member variables of a class. 

* Can be parameterized, default.

```cpp
	Cylinder() = default; // required if you have your own constructor
```

* If you have a constructor in your class, it will not generate the default one.

* private constructor is not usable from outside, you cannot create object.

* Setters & Getters: 

```cpp
	class Cylinder{
		private:
			double r,h;
		public: 
			// GETTERS
			double getradii(){ return r; }
			double getheight(){ return h; }
			
			// SETTERS
			void setradii(double r){ r=r; } 
			void setheight(double h){ h=h; }
	} 
```
* Class across multiple files 





