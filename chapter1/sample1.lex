
/*
* Sample Scanner 1:
* Replace the string username from stdin to user's login name
*/

%{

/* unistd is the header file that gives access to POSIX APIs */
/* getlogin() is a UNIX function that gives the username */
/* Anything written in this brackets is copied directly to the file lex.yy.c */

#include <unistd.h>

%}

%% 
username printf("%s", getlogin());
%%

main(){
	yylex();
}

