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

	
