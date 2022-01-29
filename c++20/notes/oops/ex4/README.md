## Constructors: Advanced

* A window to customize how our classes are built.

```cpp
	class Cylinder{
	private:
		double radius = 1;
		double height = 2;
	public:
		Cylinder() = default;
		Cylinder(double radius, double height=10); // default arguments
		// Cylinder(double radius=5, double height=80); // error!! ambiguous with default. 
	}

	int main(){

	}
```

### Initializer List 

```cpp
	class Cylinder{
	
	private:
		double radius = 1;
		double height = 2;
	
	public:
		Cylinder() = default;
		Cylinder(double radius, double height): base_radius(radius), base_height(height) {} 
	
	private:
		double radius, height;
	}

	int main(){

	}
```

* Initialized list avoid uncessary copies. Saves memory waste.

* Initializer list vs memberwise copy: 

		- Memberwise copy:
			- Two steps:
				- object creation	
				- member variable assignment
			- Potential unnecessary copies of data
			- order of member variables does not matter

		- Initializer data
			- Happens at real object creation
			- Avoids unncessary copies
			- Order of member variables matter 

* eg. copying strings can be expensive, initializer list is better in such bases

### Explicit Constructors

```cpp
	class Square{
	public:
		explicit Square(double side_param); // explicit conversion, don't allow implicit conversion
		~Square();
		double surface() const;
	private:
		double side;
	}

	Square::Square(double side_param): side{side_param} {}
	double Square::surface() const {
		return side * side;
	}

	Square::~Square(){}

	bool compare(const Square &square1, const Square& square2){
		return square1.surface() > square2.surface() ? true: false;
	}

	int main(){
		// Sneaky implicit conversion
		Square s1(30.0);
		cout << compare(s1, 44.5) << endl; // implicit conversion
	}
```

* Resolution: mark the constructor as explicit.

```cpp
	explicit Square(double side_param, string color="black"); // implicit conversion not allowed!
```

### Constructor Delegation

```cpp
	class Square{
	public:
		explicit Square(double side_param);
		Square(double side_param, string color_param, int shading_param);
	}

	Square::Square(double side_param) : side(side_param) {}
	Square::Square(double side_param, string color_param, int shading_param): side(side_param), color(color_param), shading_param(shading_param){

	}

	// Constructor delegation
	Square::Square(double side_param): Square(side_param, "red", 3) {}
```

* Sequence of events: 
	- One param constructor is called, compiler realizes the delegation, calls 3 param constructor

```cpp 
	// Square::Square(double side_param): Square(side_param, "red", 3), position(4) // disallowed
	Square::Square(double side_param): Square(side_param, "red", 3) {
		position = 4;
	}
```
Following is not a constructor delegation!

```cpp
	Square::Square(double side_param){
		Square(side_param, "red", 3); // This is a local creation of a constructor, nothing speacial.
	}
```

## Copy Constructor


