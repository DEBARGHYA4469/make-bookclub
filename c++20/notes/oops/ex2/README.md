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
