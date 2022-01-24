## RULES

* Chain of dependencies : Dependency Graph!
* Types of Rules:
	- Explicit Rules
	- Pattern Rules: wildcards instead of explicit filenames
	- Implicit Rules: Found in rules database in make!
	- Static Pattern Rules: pattern rules to specific list of target files!
* GNU Make is a "drop-in" replacement for many other versions of make.


#### Explicit Rules: 

* A rule can have more than one target. Each target has same set of prerequisites as others.

```Makefile
	vpath.o variable.o: make.h config.h getopt.h gettext.h dep.h	
```

* A rules does not have to be defined all at once. Each time make sees a target file it adds the target and prerequisites to the dep graph!

#### Wildcards

* A makefile contains long list of files. To simplify the process make supports wildcards(also known as globbing!). 

* make's wildcards are similar to Bourne shell's.

* ~ : current user's home directory.

* Wildcard expansions are performed by make if it appears in target/ prerequisite. If it appears in command the expansion is performed by subshell.

#### PHONY TARGETS

* Targets that does not represent files are known as phony targets.

```Makefile
	clean: 
		rm -f *.o lexer.c
``` 

* Phony targets are always executed.

* Phony target will always be executed because the commands associated with the rule do not create target name.

* make cannot distinguish btw file target and a phony target.

```Makefile
	.PHONY: make-documentation
	make_documentation:
				df -k . | awk 'NR==2 {printf("%d available: "), $4}'
				javadoc
	.PHONY: df
	df: 
		df -k . | awk 'NR==2 { printf(.....)}'
``` 

* Use phony targets as shell scripts and aliases in a Makefile

* Some standard PHONY targets that many makefile include:
	- all
	- install
	- clean
	- distclean
	- TAGS
	- info 
	- check

* Empty Targets

	- Just like Phony Target
	- No file as output in the rules
	- No trigger its downstream build

```Makefile
	prog: size prog.o
		$(CC) $(LDFLAGS) -o $@ $^
	size: prog.o 
		size $^
		touch size
``` 

* prog will not trigger unless we have prog.o updated. size is a empty target.

### Variables

* $(variable-name): expand the variable whose name is variable-name

* Single character variable does not require parenthesis. Else use ${} or $()

* Automatic Variables are set by make after a rule is matched.

* Core automatic variables: 
	- $@ : filename representing target 
	- $% : filename element of an archive member specification
	- $< : filename of the first prerequisite
	- $? : names of prerequisites newer than the target
	- $^ : filenames of all prerequisites separated by spaces
	- $+ : same as above with duplicates
	- $* : stem of the target filename. filename without suffix.

### Finding Files with VPATH and vpath

* VPATH: tell make to look into other directories for source files

* CPPFLAGS = -I include : to include the header files

* VPATH: grabs any filename matching from the listed directories

* Better way to overcome this is using vpath.

```Makefile
	vpath pattern directory-list
	vpath %.c src
	vpath %.l src
	vpath %.h include
```

* The problem becomes more complex when the object files are written into a binary tree while the source files live in a separate source tree. 

### PATTERN RULES

* Implicit Rules helps to avoid writing few obvious prerequisites.

* Rule Chaining: sequence of rules implicit/ explicit

* make --print-data-base

#### STATIC PATTERN RULES

* % is equivalent to * in Linux.

* A static pattern rule is one that applies only to a specific list of targets.

```
	$(OBJECTS): %.o: %.c
		$(CC) -c $(CFLAGS) $< -o $@
```	

#### SUFFIX RULES

* Suffix Rules consist of one or two suffixes concatenated and used as a target.

```
	.c.o: 
		$(COMPILE.c) $(OUTPUT_OPTION) $<
```

It is same as 

```
	%.o: %.c
		$(COMPILE.c) $(OUTPUT_OPTION) $<
```

* Every time you see a .c file use the rule below to make a .o file

* The known suffixes are: 
	- .SUFFIXES: .out .a .ln .o .c .cc .C .cpp .p .f .F .r .y .l

* You can add your own suffixes by simply adding .SUFFIXES rule to you make

 	- .SUFFIXES: .pdf .fo .html .xml

* Make deletes all the intermediate files it creates using the implicit rules.

#### RULES STRUCTURE

* The built-in rules have a standard structure intended to make them easily customizable.

eg.

```
	%.o: %.c 
		$(COMPILE.c) $(OUTPUT_OPTION) $<
``` 

* The customization of this rule can be controlled entirely by set of variable it uses like COMPILE.c and OUTPUT_OPTION.

```
	COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
	CC = gcc
	OUTPUT_OPTION = -o $@
```

#### Implict Rules for Source Control

* Make knows about two source code control system, RCS and SCCS.

#### SPEACIAL TARGETS

* A speacial target is a built-in phony target used to change make's default benhaviour, eg. .PHONY

* Some other useful target modifiers: 

	- INTERMEDIATE: Prerequisites of this speacial target are treated as intermediate files. If make creates the file while updating another target the file will be deleted automatically when make exits.

	- .SECONDARY: Prerequisites of this special target are treated as intermediate files but are never
automatically deleted. The most common use of .SECONDARY is to mark object
files stored in libraries. Normally these object files will be deleted as soon as they
are added to an archive.

	- PRECIOUS: When make is interrupted during execution it may delete the target file if it is updating the file when make started. So that make does not leave a partially constructed file laying around in the build tree.

	- DELETE_ON_ERROR


#### Automatic Dependency Generation

* To list the depedency of headers use -M flag

```
	echo "#include <stdio.h>" > stdio.c
	gcc -M stdio.c 
```  

* - suppresses the warnings.

* ar crv libcounter.a counter.o lexer.o : Archive contents to library
	- c: create 
	- r: replace
	- v: verbose

#### Double Colon Rules:

* Same target to be updated with different commands depending on which set of prerequisites are newer than the other.

```
	file-list::generate-list-script
		chmod +x $<
		....	
	file-list:: $(files)
		.....
```


