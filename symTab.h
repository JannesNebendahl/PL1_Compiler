#include <stdio.h>


// mögliche Typen in PL1
enum typ{Predicate, Function, Variable};
typedef enum typ typ;
// datentyp eines Symboltabelleneintrags
struct tableEntry{
	char *identifier;
	typ typ;
	int arity;
	struct tableEntry *next; // Zeiger auf nächstes Element
};
typedef struct tableEntry* tableEntry;


tableEntry insert_right( char* identifier, typ typ, int arity);
void init();

void delete_right();

void delete( char* identifier);

void printList();

tableEntry search_for( char* identifier);

/*
Globale Tabelle
*/


