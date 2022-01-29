## VARIABLES AND MACROS

* Make is sort of two languanges in one, the first describes the dependency graphs consisting of targets and prerequisites, second is the macro language for performing textual substitution. 

* Other macro languages like C preprocessor, m4, TEX, macro assemblers.

* Difference between macro and a normal variable is that macro variable can be expanded in-place into a text string which can be expanded further.

* To get the variable name enclose the variable name in $()

* Single letter variables can omit the parenthesis.

* Also in older Makefiles, people used ${}

* Value of a variable consists of all the words to the right of the assigments with the leading spaces trimmed. The trailing spaces are not trimmed and can cause error.

* Use variables to represent external programs, eg. there may be several versions of awk on the system: awk, gawk, nawk, etc.

* Use absolute paths for system programs to reduce the likelyhood of a trojan attack.

* Downside of using absolute paths is less portability.

```
	DF = df 
	AWK = awk
	free-space := $(DF) . | $(AWK) 'NR==2 { print $4 }'
	
```  

* Variable Types
	- Simply expanded variables
	- Recursively expanded variables.

* Simply expanded variables defined using ':=' operator.

* Recursively defined varialbe using = operator

```
	MAKE_DEPEND = $(CC) -M
	...
	# some time later 
	CC = gcc 
```

* Also called **lazily expanded** variable as evaluation is deferred until it is actually used.

* Each time a recusive variable is used, the right-hand side is reevaluated. 

* eg. if the right hand side has dynamic variables like date, it can change every time we are calling it.

* Other types of assigment are conditional variable assigment operator, represented by ?=.

* ?= will perform assigment if the variable does not yet have the value.

eg. 

``` 
	OUTPUT_DIR ?= $(PROJECT_DIR)/out
```

* += append operator. 
eg.

```
simple := $(simple) new_stuff
simple += new_suff
```

* += was invented mostly to get rid of the problem with append in case of recursive variables.

### MACROS

* "Canned sequences" created by the define directive also called macro

* They are not much different from normal make variable, but normally we callvariables defined by define directive as macro and assignment operator as variables.

```Makefile
	define create-jar
	@echo Creating $@...
	$(RM) $(TMP_JAR_DIR)
	...
	endef
```

* @ : commands prefixed with an @ character are not echoed by make when the command is executed. 

* To make the entire macro body hidden, @ can be used on the macro reference eg. @$(create_jar)

* @ is a command modifier.

### VARIABLE EXPANSION

* When make runs, it performs its job in two phases. In the first phase it reads the makefile and any included makefiles, at this time variables and rules are loaded into make's internal database and dependency graph is created. 

* In the second phase make analyses the dep graph and determines the targets that need to be updated, then executes the command scripts to perform the required updates

### TARGETS AND PATTERN SPECIFIC VARIABLES

* What if we wanted to redefine our variable for one specific operation? 

	- Files: variables can be defined in the makefile or a file included by the makefile
	- command line: defined/ redefined directly from make command line
	eg.
	 	```
			>> make CFLAGS=-g CPPFLAGS='-DBSD -DDEBUG'
		```

	- Assignment of a variable in a command line overrides any value from the environment and any assignment in the makefile.

	- Command line assignments can set either simple or recursive variables using = or := operator.
	- It is possible using the override directive to allow makefile assigment to be used instead of a command-line assignment.

	```Makefile
		# Use big-endian objects or the program crashes!
		override LDFLAGS = -EB 
	```
	- Use override to ignore user's explicit assigment request like to prevent the above crash!
	- Environment variables are already loaded into make variables when make starts. 	The variables has very low precedence so assigment within makefile/ command line will automatically override it.
	- To cause environment variables to override makefile variables use 
		--environemnt-overrides (or -e)
	- When make is invoked recursively some variables from the parent make are passed through the environement to the child make. By default only those variables which come from the environment are exported to child but to explicitly port a variable to child make use export directive.
	
	```
		export CLASSPATH := $(HOME)/classes: $(PROJECT)/classes
		SHELLOPTS = -x
		export SHELLOPTS
	```

	- To prevent an environment variable from being exported to the subprocess:
	
	```
		unexport DISPLAY
	```	

* Conditional assigment examples:
	```
		# Assume the output directory $(PROJECT_DIR)/out
		OUTPUT_DIR ?= $(PROJECT_DIR)/out

		# use ifndef to check for non-emptiness
		ifndef OUTPUT_DIR
			OUTPUT_DIR = $(PROJECT_DIR)/out
		endif
	```

* Environment variables are typically used for having multiple development/ production mode, 

### CONDITIONAL AND INCLUDE PROCESSING

* ifdef, ifndef, ifeq, ifneq. 

* Conditional directive should not have a leading tab or else they will be identified asa command and passed onto the subshell.

```
	libGui.a: $(gui_objects)
		$(AR) $(ARFLAGS) $@ $<
	    ifdef RANLIB
		$(RANLIB) $@
	    endif
```

* Whitespace present during variable expansion can pose problems. Use strip function to avoid such issues.

```
	ifeq "$(strip $(OPTIONS))" "-d"
		COMPILATION_FLAGS += -DDEBUG
	endif
```

### INCLUDE DIRECTIVE

* A makefile can include other files. All the common definitions are sometimes placed in a make definitions in a make header file 

	- include definitions.mk

* Include and Dependencies

* $(warning Hello This is a Warning) : can be used to trigger warnings in make!

```
all: 
include support.mk

all: $(programs)
```

### STANDARD MAKE VARIABLES

* MAKE_VERSION: version number of GNU Make.  
* CURDIR: current working directory
	- --include=dir-name or -C dir-name will contain the dir argument to --include-dir
	- Within the makefile all paths are relative to the makefile directory.
* MAKEFILE_LIST: This variable contains list of each file make has read including the default makefile and makefiles specified on the command line or through include directives.

* MAKECMDGOALS 

