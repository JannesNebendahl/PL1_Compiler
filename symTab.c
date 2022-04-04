#include "symTab.h"
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

/*
* Funktion um einen Eintrag rechts in der Liste einzufügen 
*/
tableEntry insert_right(tableEntry list, char *identifier, typ typ, int arity){
	tableEntry new_tableEntry = (tableEntry) malloc(sizeof(struct list_tableEntry));
	new_tableEntry->identifier = identifier;
	new_tableEntry->typ = typ;
	new_tableEntry->arity = arity;
	new_tableEntry->next = list->next;
	list->next     = new_tableEntry;
	return new_tableEntry;
}

/*
* Funktion um einen Eintrag rechts von dem Eintrag list zu löschen
*/
tableEntry delete_right(tableEntry list){
	tableEntry tmp   = list->next;
	list->next = list->next->next;
	free(tmp);
	return list;
}

/*
* Löschen eines Eintrages ,mit Hilfe eines identifiers
* 
*/
tableEntry delete(tableEntry entry, char *identifier) {

	tableEntry temp = entry, previous;
	
		// wenn der erste Eintrag der richtige ist 
		if (temp != NULL && temp->identifier == identifier) {
			entry = temp->next;
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
		// löschen des Eintrags
		previous->next = temp->next;
		free(temp);
	
}


void printList(tableEntry entry)
{
	char const* typen[] = { "Predicate", "Function", "Variable"};

	while (entry != NULL) {
		printf(" %c \n ", entry->identifier);
		printf(" %s \n ", entry->typ);
		printf(" %s \n ", typen[entry->identifier]);
		printf(" %d \n ", entry->arity);
		entry = entry->next;
	}
}

/*
* Funktion um einen Eintrag auf basis des Identifiers zu suchen
* Zeiger geht die Liste durch, bis er den Eintrag findet oder auf NULL stößt
*/
tableEntry search_for(tableEntry list, char *identifier) {
	while (list != NULL) {
		if (list->identifier == identifier)
			return list;
		list = list->next;
	}
	return NULL;
}