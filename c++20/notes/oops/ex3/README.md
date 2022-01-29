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