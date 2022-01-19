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
 	





  

