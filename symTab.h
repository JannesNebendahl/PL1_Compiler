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


tableEntry insert_right(tableEntry list, char* identifier, typ typ, int arity);


tableEntry delete_right(tableEntry list);

tableEntry delete(tableEntry entry, char* identifier);

void printList(tableEntry entry);

tableEntry search_for(tableEntry list, char* identifier);

/*
Globale Tabelle
*/
tableEntry actSymTable;


