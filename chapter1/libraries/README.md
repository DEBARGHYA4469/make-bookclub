
### STATIC VS DYNAMIC LIBRARIES


#### Static Libraries

* static lib contains object code linked with an end user application, that becomes a part of the executable, also called archive. 

* also can be viewed as package of all compiled object files.

* libraries are in directories such as /lib, /usr/lib, /usr/local/lib

* Static linking/ early binding: linking of the function references from lib to exe 

Ref : https://www.bogotobogo.com/cplusplus/libraries.php

* Resulting stand-alone file is known as the **static build** of the program.

* filename starts with lib and ends with .a in UNIX/LINUX

* Compile Time Linking 

#### Dynamic Libraries

* shared lib/ shared object: intended to be shared by executables.

* dynamic libs are linked at compile time to resolve undefined references and then distributed with the end user application.

* uses dynamic linker on end user machines

* Linux dynamic linker is called ld.so.

* .so: shared object, dynamically linked libraries 

* Using dynamic libraries can be more efficient that static in terms of disk space.

* OS level optimization for linking dynamic libs 

* It is also possible to link a dynamic lib as plugin interface on demand w/o compile phase. 
  
#### 

To display the symbol tables use nm tool:

'''>> nm -A ./*.o | grep sqrt '''

To create a shared library, 

'''>> gcc -shared -fPIC -o libcalc.so calc.o''' 

* This command tells the compiler driver to generate a shared library libcal.so from the object module calc.o. 

* The -fPIC tells the compiler to generate position independent code.

* To link, '''gcc main.o ./libcalc.so -lm'''

* The above command creates a partially executable file which has to be resolved at the runtime.(Symbol Resolution + Address Relocation)

* List of tools: ar, ldd, nm, objdump, strings, c++filt 


## LINKER VS LOADER 

* After compilation the fragments of a program are glued together by a linker 

* Relocation and resolution of external references are performed by a linker 

* Loader: Loading an executable into main memory for execution

 





