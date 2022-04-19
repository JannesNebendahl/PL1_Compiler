%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symTab.h"
#include "error.h"
#include "synTree.h"
int yylex(void);
void initialize();
%}
%union {
    char val [101];
	int number;
    int regno;
}
%left   EQUIVALENT
%left   IMPLICATION
%left   OR
%left   AND
%left   NOT
%left   ALL     EXIST   B_O     B_C
%left  COMMA
%token  R_B_O   R_B_C
%token  SEMICOLON
%token  TRUE FALSE
%token  ID
%token  DIGIT
%token  DECLARE PREDICATE FUNCTION VARIABLE DD INT

%%

file:    
        | declarations file {}
        | formula SEMICOLON file {}
        ;

declarations:     DECLARE PREDICATE ID DD DIGIT { 
                    printf("PAR: Declare Predicate %s with %d\n", $<val>3, $<number>5);
                    char* val1 = $<val>3;
                    int val2 = $<number>5;
					insert_right(val1,Predicate,val2,NoType); 
					 printList();
                  }
                | DECLARE FUNCTION ID DD DIGIT { 
                    printf("PAR: Declare Function %s with %d\n", $<val>3, $<number>5);
					 insert_right($<val>3,Function,$<number>5,NoType);   
                    printList();

                  }

                | DECLARE VARIABLE ID DD INT { 
                    printf("PAR: Declare Variable %s with int \n", $<val>3);
					 insert_right($<val>3,Variable,0,Int); 
                    printList();
                  }
                ;

formula:      ID R_B_O term R_B_C { 
                    printf("PAR: %s\n", $<val>1); 
                     //check auf Predicate -> symboltable
                    }
            | TRUE { 
				printf("PAR: True\n"); 
				//makeTrueNode()}
            | FALSE { printf("PAR: False\n"); }
            | R_B_O formula R_B_C { printf("PAR: ( )\n"); }
            | NOT formula { printf("PAR: ~\n"); }
            | formula AND formula { printf("PAR: AND\n"); }
            | formula OR formula { 
				printf("PAR: OR\n"); 
				// make disjunktionnodde()
				}
            | formula EQUIVALENT formula { printf("PAR: EQUIVALENT\n"); }
            | formula IMPLICATION formula { printf("PAR: IMPLICATION\n"); }
            | ALL B_O ID B_C formula { printf("PAR: ALL[%s]\n", $<val>3); }
            | EXIST B_O ID B_C formula { printf("PAR: EXIST[%s]\n", $<val>3); }
            ;

term:     {printf("PAR: kein Argument\n");}
        | ID      {strcpy($<val>$,$<val>1); printf("PAR: %s\n", $<val>1);}
        | DIGIT   {strcpy($<val>$,$<val>1); printf("PAR: %s\n", $<val>1);}
        | ID R_B_O term R_B_C { printf("PAR: %s( )\n", $<val>1); }
        | term COMMA term { printf("PAR: ,\n"); }
        ;

%%


/* int yyerror(char *s){
    printf("%s\n", s);
    exit(1);
}
 */

// int main(void)
//  {
// 	// init();
//  	return yyparse();
//  } 
