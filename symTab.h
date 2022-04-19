#include <stdio.h>

#define MAX 100
// mögliche Typen in PL1
enum typ{Predicate, Function, Variable};
typedef enum typ typ;
// datentyp eines Symboltabelleneintrags
struct tableEntry_struct{
	char identifier[MAX];
	typ typ;
	int arity;//= Anz. der Argumente
	struct tableEntry_struct *next; // Zeiger auf nächstes Element
};
typedef struct tableEntry_struct* tableEntry;
tableEntry insert_right(char *identifier, typ typ, int arity);
	void init();

void delete_right();

void delete(char* identifier);

void printList();

tableEntry search_for( char* identifier);

/*
Globale Tabelle
*/

