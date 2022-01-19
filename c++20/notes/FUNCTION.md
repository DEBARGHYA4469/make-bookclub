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
	- 














