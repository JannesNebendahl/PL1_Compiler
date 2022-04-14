#include "symTab.h"
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

tableEntry actSymTable;

void init() { 
	printf("init---------------");
	actSymTable= (tableEntry) malloc(sizeof(struct tableEntry));
}
/*
* Funktion um einen Eintrag rechts in der Liste einzuf�gen 
*/
tableEntry insert_right(char *identifier, typ typ, int arity){
	tableEntry new_tableEntry = (tableEntry) malloc(sizeof(struct tableEntry));
	new_tableEntry->identifier = identifier;
	new_tableEntry->typ = typ;
	new_tableEntry->arity = arity;
	new_tableEntry->next = actSymTable->next;
	actSymTable->next     = new_tableEntry;
	return new_tableEntry;
}

/*
* Funktion um einen Eintrag rechts von dem Eintrag list zu l�schen
*/
void delete_right(){
	tableEntry tmp   = actSymTable->next;
	actSymTable->next = actSymTable->next->next;
	free(tmp);
	
}

/*
* L�schen eines Eintrages ,mit Hilfe eines identifiers
* 
*/
void delete( char *identifier) {

	tableEntry temp = actSymTable, previous;
	
		// wenn der erste Eintrag der richtige ist 
		if (temp != NULL && temp->identifier == identifier) {
			actSymTable = temp->next;
			free(temp);
			return;
		}
		// durchiterieren der Liste
		while (temp != NULL && temp->identifier == identifier) {
			previous = temp;
			temp = temp->next;
		}

		// wenn kein Eintrag gefunden werden kann
		if (temp == NULL)
			return;
		// l�schen des Eintrags
		previous->next = temp->next;
		free(temp);
	
}


void printList()
{
	char const* typen[] = { "Predicate", "Function", "Variable"};

	while (actSymTable != NULL) {
		printf(" %c \n ", actSymTable->identifier);
		printf(" %s \n ", actSymTable->typ);
		printf(" %s \n ", typen[actSymTable->typ]);
		printf(" %d \n ", actSymTable->arity);
		actSymTable = actSymTable->next;
	}
}

/*
* Funktion um einen Eintrag auf basis des Identifiers zu suchen
* Zeiger geht die Liste durch, bis er den Eintrag findet oder auf NULL st��t
*/
tableEntry search_for(char *identifier) {
	while (actSymTable != NULL) {
		if (actSymTable->identifier == identifier)
			return actSymTable;
		actSymTable = actSymTable->next;
	}
	return NULL;
}