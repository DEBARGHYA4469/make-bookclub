### FUNCTIONS 

* void func(int a[5]): a is not a true array, its a pointer.

* Imp: array as parameter decays into a pointer. 

* size(a): gives sizeof the pointer, 8 bytes (eg)

* Same as passing a int pointer.
 
* Multi-dimensional array:
	- const double array[][3]

* constexpr functions: Compile time functions 

```cpp
	constexpr int getval(int multiplier){
		return 3*multiplier;
	}
	
	int main(int argc, char **argv){
		int b = 5;
		constexpr int val1 = getval(4); // compile-time 

		int val2 = getval(b); // runtime 
	}
``` 

* consteval function : same as constexpr but it is mandatory to run the function at compile time. 

```cpp
	consteval int getval(int multiplier){
		return multipler*5;
	}

	int main(){
		int val1 = getval(6); // works!!
		int b = 5;
		int val2 = getval(b); // error!!
	}
```

* Enums: 

```cpp
	// default enum type is int 
	enum class Month{
		Jan, Feb, Mar, Apr	
	};

	Month month = Month::Mar;
```

* Type Aliases: 

	- using Bigint = unsigned long long int;

* Command Line Argument: 

```cpp
	int main(int argc, char **argv){ // char *argv[]
		for(int i=0;i<argc;++i)
			cout << argv[i] << endl;
	}

```

* First index in argv is the name of the program 

* Function Overloading: 
 
	- With Pointers!
	
	```cpp
	  double max(double *num, size_t cnt){
		
	  }

	  double max(int *num, size_t cnt){

	  }
	```

 	- With References 
	
	```cpp
		void say_my_name(const std::string &name){
		
		}

		void say_my_name(std::string name){

		}

		std::string var = "Hello";
		say_my_name(var); // Error! Ambiguous

		int func(double a, double b){} 
		int func(int &a. int &b){} 

		char x = 45;
		char y = 46;
		
		func(x,y); // double is called because references cannot implicitly typecast 
	```

* Overloading by const: 

	```
		int func(const int a) & 
		int func(int a)

	```

	- Above two functions are ambiguous!

* Const References:
	
	```cpp
		
		int max(int &a,int &b){ return a>b? a: b; }
		int max(const int &a,const int &b){ return a>b? a: b; }	
	
		int a = 45, b = 55;
		max(a,b); // first func is called!
	
		const int &v1=a;
		const int &v2=b;

		max(a,b); // second func is called!	
	```  


### LAMBDA FUNCTIONS

* Lambda functions are anonymous functions 
* A mechanism to set up anonymous functions w/o names. 

```cpp
	[capture-list](paramters)->return-type{
		// function body
	};
```

* lambda expression: 

```cpp
	[](){
		cout << "Hello world!" << endl;
	}();
```

* Capture List: 
	- [c] : by value 
	- [&c]: by reference
	- [=]: capture everything by value   
	- [&]: capture everything by references

Functions: 

* Some misfits:
	- static variable: scope is function, lifetime: program
	- inline functions: reduce function call overhead

* Call Stack: 
	- debugging call stack!


### Templates

* Avoid multiple overloads!

```cpp
	template<typename T>
	T maximum(T a, T b){
		return a>b? a:b;
	}	
	
	// To explicitly call : maximum<double>(1,2);

```

* Blueprint from which compiler generate function based on args and not real code!

```cpp
	template<typename T>
	const T& maximum(const T& a, const T&b); 
```

* Template speacilization: tell compiler to use custom implementation

```cpp
	template <> 
	const char *maximum<const char *> (const char *a, const char *b){
		return strcmp(a,b) > 0 ? a: b;
	}
```

	- When we write any template based function or class, compiler creates a copy of that function/class whenever compiler sees that being used for a new data type. If a speacilizaed version is present, compiler first checks with the speacilizedversion by matching the passed parameter. 

```cpp
	template <class T>
	void fun(T a){
		cout << a << endl;
	}

	template<>
	void fun(char a){
		cout << a << endl;
	}
```

```cpp

//(3)Function template
template <typename T> T maximum(T a,T b){
    std::cout << "Template overload called(T) " << std::endl;
    return (a > b) ? a : b ; 
}

//(1)A raw overload will take precedence over any template instance
//if const char* is passed to maximum
const char* maximum(const char* a, const char* b){
	std::cout << "Raw overload called" << std::endl;
	return (std::strcmp(a,b) > 0) ? a : b ; 
}


//(2)Overload through templates. Will take precedence over raw T
//if a pointer is passed to maximum

template <typename T> T* maximum(T* a, T* b){
	std::cout << "Template overload called (T*) " << std::endl;
     return (*a > *b)? a : b;
}

```


* Function templates with multiple parameter

```cpp
template <typename T, typename P> maximum(T a, P b);

template <typename T, typename P, typename U> maximum(T a, P b)
U maximum(T a, P b){
	return a+b;
} 

// Bad design : order of template parameter

// Better Approach!

template <typename ReturnType, typename T, typename P>
ReturnType maximum(T a, P b){
	return (a>b)? a: b;
}
```

* Function template return type with auto:

* auto max1 = maximum(12.5, 5)

```cpp
	// auto type templates
	template<typename T, typename S>
	auto maximum(T a, S b){
		return a>b ? a : b;
	}
```

* Function def has to be present before the auto template function call, else compiler would not be able to resolve the return type.

* Decltype: getting the type of an expression 

eg. 
	 - decltype((a>b)? a:b) 


```cpp
	template <typename T, typename P>
	decltype((a>b)?a : b) maximum(T a, Pb){
		return (a>b) ? a: b; // compiler error 
	}
	
	// decltype as trailing return type!!
	template <typename T, typename P>
	auto maximum(T a, T b)-> decltype((a>b)?a:b){
		return (a>b) ? a: b;
	}
```  

* Decltype auto: 

```cpp
	template<typename T, typename P>
	decltype(auto) maximum(T a, P b){
		return a>b ? a:b;
	}
```
* Default Arguments



### POINTERS 

```cpp
// declaring pointers  
int *ptr; 
double *ptr; 

// explicitly initializing to nullptr 
int *ptr {nullptr};
double *ptr {nullptr};
```
* sizeof(int), sizeof(double): same size, store address of variables

```cpp
int var {43};
int *ptr{ &var }; 
``` 

* int* var, var2: var2 is a variable of type int(and not a ptr!!)

* Pointer to a char: char *c 

* char *msg{ "hello world!" }: C-style string 

* char ptr is a compiler magic as it prints out the string its pointing to. But when dereferenced(*msg) it prints out the first char.

* You cannot modify a char with char ptr as string literal is made up of const char. You cannot change a literal.
 
* Better use ```const char *msg = "hello world!"```.

* Or, use regular arrays. 

```cpp 
char msg[] = "hello world!";
msg[0] = 't' 
```

### Arrays of pointers to char 

* storing an array of strings 

* Issue with wasting memory char msg[][90] {} 

* const char* msg[] {"msg1","msg2","msg3","msg4","msg5"};


### Const Pointer vs Pointer to Const 

* const int * var : You cannot modify the variable its pointing to, i.r pointer to a const var 
* int * const var : You cannot be made to point somewhere else, i.e const pointer 
* const int * const var: both the features.

const int * : ptr to const 
int * const : const ptr   

* Array of const pointer: 

```
/*
	const char *c[] = {"red","green","blue"};
	*c[0] = "m"; // will throw error!!
*/

	// This is possible!

	const char *c[] = {"red","green","blue"};
	c[0] = "magenta"

	// array of const pointer to const char 
```

### Array & Pointer: 

* int score[10] = {1,2,3,4,5};
* int *ptr = score;
* array name vs real ptr: 
  - you cannot make it point somewhere else.
  - you cannot deduce the array size from raw ptrs but array name works
  - size(arrname)
  - arrayname -> ptr : Pointer decay, you lose some information 
   eg. int *p = arr;

* std::ptrdiff_t pos_diff = ptr2 - ptr1; // store the ptr difference.

* Virtual Memory : Map of main memory [0, 2^n-1]. Tricks the program tobelieve that it has whole of RAM. 

* MMU: program executation model, binary file will be a representation of VM. Memory management unit transforms the memory map of each process and real memory in RAM. The entire program is not loaded and only parts of it is loaded into the main memory!

* Different programs have different memory maps and gets assigned to main memory during runtime

* Virtual Memory is a standard defined by your OS. 

* It has System, Stack, Heap, Data, Text section.

* Stack stores local variables,function calls, Heap stores additional memory.


### Dynamic Memory Allocation: 

* int *ptr; *ptr = 55; // bad as its a junk pointer!
* So far we were using memory from stack section!
* stack, heap memory is finite.
* lifetime in stack var is through scope mechanism while in heap its through developers using new, delete operators.
* int *p = nullptr; p = new int; // stored in heap!

#### Dangling Pointers: 

* Pointers that does not point to a valid memory address. 
* Types: 
	-Unitialized ptr 
	- Deleted ptr 
	- Multiple pointer pointing to same memory location.

* new fails: heap memory exhausted.

```cpp
int *a = new int[1000000000]; 
```

* Handle new fails using exception handling!. 

```cpp
for(int i=0;i<10000000;i++){	
	try{
		int *a = new int[100000000];
	}catch(exception &ex){
		cout << ex.what() << endl; // std::bad_alloc 
	}
}
```

* Null Ptr Safety: Calling delete on a nullptr is ok.

* Memory Leaks: Reassigning ptr can lose access to some heap memory and you cannot release the memory. Avoid memory leak

eg. 

```cpp
int *p = new int(55); // should delete and reset!
p = new int(44);
```

* pointer in local scope can also lose access and leads to memory leaks.

* dynamic array: int *p = new int[10] {1,2,3,4,5,6,7,8,9,10};

* static vs dynamic array. Cannot loop through a dynamic array!

eg. for(auto s: p) cout << s; 

### REFERENCES

* Alias's for variables. eg. int &var1 =  var2;

* References vs Pointers : Can't be changed to reference somthing else.

* Need initialization at declaration

* References & Const: 
	- int age = 27;
	- int &ref_age = age; 
	- const int &ref = age; // can't modify ref, but can modify age 
	- Can duplicate using const int* const refconst = &age;
	
* Range based for-loops 


```cpp
	for(auto &score: scores){
		score = score * 10; 	
	}
```	 
 	

### STRING 

* escape sequence: \", \\ 
* std::endl vs "\n": \n moves to the next line, but donot flush the buffer. 
* endl may be worse in performance. 
* At the program startup three text streams are predefined and need not be opened explicitly. stdin, stdout, stderr
* As initially opened, stderr stream is not fully buffered, stdin & stdout are fully buffered iff the stream can be determined not to refer to an interactive device.


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

	- How to split class across multiple files? 
		- move constants across other files

```cpp
	>> cylinder.h 
	#include "constants"
	
	>> main.cpp 
	#include "constants"
	#include "cylinder"
```
* Including header from nested headers can result in compile error because preprocessor directive just adds the header in the file main.cpp

* One way to solve this is use #define eg. in ex1 

* Compiling main.cpp without compiling cylinder.cpp will result in linking error
* use >> ```g++ -c *.cpp```
* ```#pragma once": for include guards```

* Arrow Pointer call:

```cpp
	// stack object: . notation 
	Cylinder c1(10, 2); 

	// Heap object: deferencing and .notation
	Cylinder *c2 = new Cylinder(11,20);
	vol = (*c2).volume(); 
	vol_2 = c2->volume();

	delete(c2); // release memory from heap
```

* Compiling main.cpp without compiling cylinder.cpp will result in linking error
* use >> ```g++ -c *.cpp```
* ```#pragma once": for include guards```

* Arrow Pointer call:

```cpp
	// stack object: . notation 
	Cylinder c1(10, 2); 

	// Heap object: deferencing and .notation
	Cylinder *c2 = new Cylinder(11,20);
	vol = (*c2).volume(); 
	vol_2 = c2->volume();

	delete(c2); // release memory from heap
```

* Destructors: Speacial methods called bu compiler to destroy your objects.

```cpp
	class Dog{
		public: 
			Dog();
			Dog(string name_param, breed_param, age_param);
			~Dog(){ // destructor declared
				delete dog_age;
				cout << "Destructor called for " << dog_name << endl;
			}
	}
```


Q. When are destructors called? 

	- when *local stack object* goes out of scope(dies)
	- when *heap object* is released with delete

	- Some non-obvious places:
		- when an object is passed by value to a function(out of scope) 
		- when a local object is returned from a function


* Destructor cannot have parameters passed to them, or compile error!

* Passing objects plainly can result in disaster. Can delete pointers twice in destructor

```cpp
	void somefunction(){
		Dog *p_dog = new Dog("Fluffy","Shepherd",2);
		// we created an object in the heap so destructor will be not called implicitly

		delete p_dog;
	}
```
* Order of Constructor and Destructor call: 

```cpp
	Dog dog1("Doggy1","Shepherd",1);
	Dog dog2("Doggy2","Shepherd",2);
	Dog dog3("Doggy3","Shepherd",3);
	Dog dog4("Doggy4","Shepherd",4);
```

* Constructors are called in the order dog1->dog2->dog3->dog4
* Destructors are called in the order dog4->dog3->dog2->dog1
* Object created first is deleted last as the compiler thinks first object can have downstream dependencies on the later objects.

#### This Pointer

* this: address of the current object

```cpp
	void set_name(string &dog_name){
		// dog_name = dog_name, compiler is confused
		this->dog_name = dog_name;	
	}

	// Chaining calls using pointers
	Dog *p_dog = new Dog("Milou","Shepherd",2);
	p_dog->print_info();

	p_dog->set_name("Mario")->set_breed("Fox")->set_age(3);	

	p_dog->print_info();

	// Setters return this ptr
	Dog *set_name(const string &dog_name){
		this.dog_name=dog_name;
		return this;
	}

	Dog *set_breed(const string &dog_breed){
		this.dog_breed=dog_breed;
		return this;
	}

	Dog *set_dog_age(const int dog_age){
		this.dog_age=dog_age;
		return this;
	}
```

* Reference Version 

```cpp
Dog *p_dog = new Dog("Milou","Shepherd",2);
	p_dog->print_info();

	p_dog->set_name("Mario").set_breed("Fox").set_age(3);	

	p_dog->print_info();

	// Setters return this pointer
	Dog &set_name(const string &dog_name){
		this.dog_name=dog_name;
		return *this; // deferenced version
	}

	Dog &set_breed(const string &dog_breed){
		this.dog_breed=dog_breed;
		return *this;
	}

	Dog &set_dog_age(const int dog_age){
		this.dog_age=dog_age;
		return *this;
	}
```

*  Setters using this for same param and member name 

```cpp
	void set_dog_name(string name){
		// name = name; gcc builds successfully but not modified
		this.name = name; // use this to affect member variable
	}
```

* Chained Function call using this pointer.

#### Struct

* Use struct to create classes.
* In classes variables are private by default, but struct public by default.

```cpp
	struct Cat{
	public:
		Cat(const string &name){
			this.name = name;
		} 
	}
```

* Sizes of class object 

```cpp
	class Wrapper{
	public:	
		...
	private:
		int m_var1 = {};
		int m_var2 = {};
		string m_name {};
	}
```

* Size of the object is sum of the sizes of member variables.

* functions are associated to blueprint so sizes are not taken into calculation

#### Boundary alignment: 

* Due to boundary alignment, size of the object is slightly off than the sum of the member variables.

```cpp
	#include <iostream>

	class Dog{
		public: 
				Dog()=default;
		private:
				size_t leg_count;
	}

	>> sizeof(Dog) = sizeof(leg_count)
```

* string: is an object of string class, so size gives sizeof `(const char *)` and not what its pointing to.

### Objects and the Const Keywords

```cpp
	const Dog dog1("Flatcher", "Shepherd", 2);
```

Imp: 
* If you define a const variable dog1 from Dog, you will be locked out of your objects. We can't modify the const objects. But we can't read from them either, which makes them useless.

## Const Objects

* const Dog dog1("Flatcher", "Shepherd", 3)

```cpp
	const Dog dog1("Flatcher", "Shepherd", 3);
	dog1.set_name("Milou"); // compiler error
	dog1.print_info(); // compiler error
	string name = dog1.get_name(); // compiler error	
```

* Because we have no speacial way to differentiate getters and setters. Compiler thinks all member functions are modifying the object.

```cpp
	const Dog dog1("Flatcher", "Shepherd", 3);
	Dog *p_dog = &dog1; //compiler error! invalid conversion from const Dog * to Dog *
	p_dog->set_name("Hillo");
	p_dog.print_info();

	const Dog dog1("Flatcher", "Shepherd", 3);
	Dog &p_dog = dog1; //compiler error! can't convert to const Dog & to Dog &

	const Dog dog1("Flatcher", "Shepherd", 3);
	const Dog* p_const_dog = &dog1; // no error
	p_const_dog->set_name("Hillo"); // Error
	p_const_dog->print_info(); // Error

	const Dog dog1("Flatcher", "Shepherd", 3);
	const Dog& ref_const_dog = &dog1; // no error
	ref_const_dog.set_name("Hillo"); // Error
	ref_const_dog.print_info(); // Error	
```

* Non-Const Pointer can't refer to a Const pointer.

Q. What if you try to use a const object as an argument?

* Pass by value: Works fine as local copy inside the function is a different copied object
* Rest face the same issue as discussed above.

### Const Member function

* Solution for const object issue.
* Tell the compiler that getters are not modifying the objects

```cpp
	class Dog{
	public: 
		string get_name() const{ // compiler knows it never modifies the objects.
			return dog_name;
		}

		// It is possible to overload member function based on constness
		void print_info() const{

		}

		void print_info(){

		}
	private:
		int age; 
		string breed;
		string dog_name;
	}

	int main(){

		return 0;
	}
```

* Mark getters as const.

### Getters that double as setters 

* function to read stuff from and class and also set them.

```cpp
	class Dog{
	public:
		Dog();
		Dog(const string &name_param, const string &breed_param, int age_param);
	
		string& name(){
			return m_name;
		}

		// Const Overloading
		const string& name() const { // must be const member function and return const string 
			return m_name;
		}

		string &breed(){
			return m_breed;
		}

		const string& breed() const{ // const member function return const references 
			return m_breed;
		}

		int &age(){
			return m_age;
		}

		const int& age() const{
			return m_age;
		} 

	private:
		int m_age;
		string m_breed, m_name;
	}

	int main(){
		
		Dog dog1("Fluffy", "Shepherd", 3);
		cout << dog1.name() << endl;
		dog1.name() = "Dandio"; // getters that double as setters
		dog1.age() = 5;

		const Dog dog2("Fluffy", "Shepherd", 3);
		cout << dog2.name() << endl;

		return 0;
	}
```
* const ref are good practises to avoid copying all arguments
* Const overloading

### Dangling Pointers/ Reference

* A pointer or reference is said to be dangling if it's dangling if it's pointing to or referencing invalid data.
Example. Manipulating deleted piece of memory

* After you delete your object, set your pointer to nullptr.

* Dangling reference is a disaster.

```cpp
	const string &Dog::compile_dog_info() const{
		string info = "dog name=" + dog_name;
		return info; // dangling references
	} 

	int *Dog::return_int_pointer() const {
		int jumps_per_minute = 50;
		return &jumps_per_minute; // dangling pointers
	}
``` 

### Mutable Objects

* Mechanism to violate const correctness

```cpp
	class Dog{
	public:
		Dog();
		void print_info() const{
			++info_print_count;
			cout << "Inside print info function" << endl;
		}
	private:
		string dog_name;
		string dog_breed;
		int *dog_size;
		mutable size_t info_print_count = 0;
	}
```

* use mutable keyword to violate constness. Can be used for debugging purposes.
* but not suggested for best practises.

### Structured Bindings

```cpp
	struct Point{
		double x;
		double y;
	}

	int main(){
		Point p = {4.4, 5.9};
		auto [a,b] = p;
	}
```

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








  


