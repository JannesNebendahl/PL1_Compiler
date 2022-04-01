%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"
int yylex(void);
int yyerror(char *);
%}

%union {
    char val [101];
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
                    printf("PAR: Declare Predicate %s with %s\n", $<val>3, $<val>5);
                    addSymbolEntry($<val>3, $<val>5, 1); 
                  }
                | DECLARE FUNCTION ID DD DIGIT { 
                    printf("PAR: Declare Function %s with %s\n", $<val>3, $<val>5);
                    addSymbolEntry($<val>3, $<val>5, 0);
                  }
                | DECLARE VARIABLE ID DD INT { 
                    printf("PAR: Declare Variable %s with int \n", $<val>3);
                    addSymbolEntry($<val>3, $<val>5, 2);
                  }
                ;

formula:      ID R_B_O term R_B_C { printf("PAR: %s\n", $<val>1); }
            | TRUE { printf("PAR: True\n"); }
            | FALSE { printf("PAR: False\n"); }
            | R_B_O formula R_B_C { printf("PAR: ( )\n"); }
            | NOT formula { printf("PAR: ~\n"); }
            | formula AND formula { printf("PAR: AND\n"); }
            | formula OR formula { printf("PAR: OR\n"); }
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
int yyerror(char *s){
    printf("%s\n", s);
    exit(1);
}



// KOMENTAR AN MICH: 
// Wieso hört der Parser nach dem Declarations Abschnitt auf?
// Um nur die Parser Printfs auszugeben wie folgt starten:  ./pl1c BEISPIELE/complex_in.pl1 | grep PAR

