#include <stdio.h>


// mögliche Typen in PL1
enum typ{Predicate, Function, Variable};
typedef enum typ typ;
// datentyp eines Symboltabelleneintrags
struct tableEntry_struct{
	char *identifier;
	typ typ;
	char *arity;
	struct tableEntry_struct *next; // Zeiger auf nächstes Element
};
typedef struct tableEntry_struct* tableEntry;
tableEntry insert_right(char *identifier, typ typ, char *arity);
	void init();

void delete_right();

void delete(char* identifier);

void printList();
void checkListe();

tableEntry search_for( char* identifier);

/*
Globale Tabelle
*/

