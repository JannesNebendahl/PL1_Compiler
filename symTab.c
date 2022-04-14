#include "symTab.h"
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

int initialized;
 tableEntry actSymTable;

void init() { 
	printf("\n------------initialize table ----------\n");
	
}
/*
* Funktion um einen Eintrag rechts in der Liste einzuf�gen 
*/
tableEntry insert_right(char *identifier, typ typ, char *arity){
	printf("SYM: Inserting %s into the symboltable with arity %s\n",identifier, arity);
	tableEntry temp = actSymTable;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	tableEntry new_tableEntry;
	new_tableEntry = (tableEntry) malloc(sizeof(struct tableEntry_struct));
	new_tableEntry->identifier = identifier;
	printf("new_tableEntry->identifier: %s\n", new_tableEntry->identifier);
	new_tableEntry->typ = typ;
	printf("new_tableEntry->typ: %d\n", new_tableEntry->typ);
	new_tableEntry->arity = arity;
	printf("new_tableEntry->arity: %s\n", new_tableEntry->arity);
	new_tableEntry->next = temp->next;
	temp->next = new_tableEntry;
	return new_tableEntry;
}
void checkListe()
{
	if (initialized != 1)
	{
		printf("\n------------initializing symboltable----------\n");
		actSymTable = malloc(sizeof(struct tableEntry_struct));
		actSymTable->next = NULL;
		initialized = 1;
	}
	else{

	}
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
* Löschen eines Eintrages ,mit Hilfe eines identifiers
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
	printf("\n------Actual symboltable-------:\n");
	char const* typen[] = { "Predicate", "Function", "Variable"};
	int index = 1;
	tableEntry temp = actSymTable;
	temp = temp->next;
	while (temp != NULL) {
		printf("\n----%d----\n", index);
		printf("ID: %s \n", temp->identifier);
		// printf(" %s \n ", actSymTable->typ);
		printf("Typ: %s \n", typen[temp->typ]);
		printf("Arity: %s \n", temp->arity);
		index++;
		temp = temp->next;
	}
	
	printf("\n-----------------------------\n", index);

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