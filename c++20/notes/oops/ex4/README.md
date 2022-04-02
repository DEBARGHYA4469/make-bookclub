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

```cpp
	class Person{
	private:
		string last_name, first_name;
		int *age;
	public:
		Person() = default;
		Person(string last_name_param, string first_name_param, int age_param);
		Person(string last_name);

		void print_info(){
			cout << "Printing object info: " << endl;
		}
	};

	int main(){
		Person p1 = Person("John", "Snow", 25);
		p1.print_info();

		Person p2(p1); // create copies
		p2.print_info();
	}
```

* member wise copy. address of pointer age also gets copied. 

```cpp
	Person p1("John","Snow",25);
	Person p2(p1);
	p1.set_age(30);

	p1.print_info(); // age = 30
	p2.print_info(); // age = 30
```

* Generated copy constructor does memberwise copies. 

* It is possible for set up a copy constructor
```cpp

	/* This is wrong!!
		We are passing p by value, which again invokes copy constructor. endless chain of copy constructor 	
	*/
	Person::Person(const Person p): last_name(p.get_last_name()), first_name(p.get_first_name(), age(p.get_age())) {} 
	/*
		This works, but it still does member wise copy!!. Bad!
	*/
	Person::Person(const Person &p): last_name(p.get_last_name()), first_name(p.get_first_name(), age(p.get_age())) {} 

	Person::Person(const Person &p): last_name(p.get_last_name()),
									 first_name(p.get_first_name(), 
									 age(new int(*(p.get_age()))) {} // Good

	Person::Person(const Person &p): Person(p.get_last_name(),
									 p.get_first_name(),
									 *(p.get_age())) {}								 
```

* Pass by value leads to endless chain of copy constructor calls.

```cpp
// Delegate from copy constructor
Person::Person(const Person &p): Person(p.get_first_name, p.get_last_name, *(p.get_age)) {}
```
* Objects stored in arrays are copies

```cpp
	Person s1{"John", "Out"};
	Person s2{"Sean", "Out"};
	Person s3{"Bill", "Out"};

	Person students[] = {s1, s2, s3, Person(s1)}; // copies of the objects 

	// Use references to avoid copies 
	for(Person& s: students){
		s.set_first_name("Array");
	}
```

* Shallow Copy vs Deep Copy:
	- Member wise copy of member variables even for pointers
	- When pointer member variables are involved allocating new memory, deep copy.

### Move Constructor

* steal data from other objects(temporary objects)

	
```cpp
	class Point{
		private : 
			double *x {}; 
			double *y {};
		public: 
			Point(double x_param, double y_param);
			~Point();
	}

``` 

* Point p3(Point(40.7, 50.3)): steal data from Point(40.7,50.3)

```cpp
	// move constructor
	Point::Point(Point&& source_point): x(source_point.get_x()), y(source_point.get_y())
	{
		source_point.invalidate();
		cout << "body of move constructor" << endl;
	}
```

* Point p3(std::move(Point(40.7, 50.3))) : force compiler as temporary with std::move

* Deleted Constructors: Disable a constructor from being used as objects.

```cpp
	Point() = delete;
	Point(const Point& source_point) = delete;
	Point(Point && source_point) = delete;    

	// Point P1; # not allowed, deleted function 
	// Point P1(P0);
``` 

* Initializer List Constructors: constructors to initialize aggregates. speacial containers. 

- eg of aggregates:

```cpp
struct Point{
	double x;
	double y;
};

int main(){
	Point point1{12.5, 65.2}; // compiler generating initializer list 
}

// Custom initializer list .... 

class Point{

	public: 
		Point(std::initializer_list<double> list){ // instance of template class
			for(auto i = list.begin(); i!=list.end(); i++){
				cout << *i << endl;
			}		
			x = *(list.begin());
			y = *(list.begin()+1);	
		}

	void print_info() const{
		std::cout << x << " " << y << endl;
	}
	
	private:
		double x;
		double y;
};


// Runtime Error if error in assignment.
```

* Aggregate Initialization: All aggregates can be initialized with {} 

- eg. Point p1{10.0, 20.0};
- int scores[] {1,2,3,4,5};

* Designated Initializers: 

```cpp
	struct Component{
		double x;
		double y;
		double z;
	}

	int main(){
		Component c1{.x=10, .y=20, .z=30};
		Component c2{.y=5.9,.z=6.1};
		// Component c4{.x=4.3, .z=5.6, .y=9.4}; //Compiler error 
	}
```  

* Uniform initialization for aggregates: initializing any object either through () or {}. 

- Person p1{"Steven", 23}; or Person p1("Steven", 32);

- {}  allows narrowing conversions, while () does not. 





