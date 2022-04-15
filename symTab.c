#include "symTab.h"
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

int initialized;
tableEntry actSymTable;
int firstEntry = 0;

void init() { 
	printf("\n------------initialize table ----------\n");
	
}
/**
 * @brief Function to insert a new entry into the list
 * 
 * @param identifier ID 
 * @param typ 
 * @param arity 
 * @return tableEntry the new TableENtry
 */
tableEntry insert_right(char *identifier, typ typ, char *arity){
	printf("SYM: Inserting %s into the symboltable with arity %s\n",identifier, arity);
	tableEntry temp = actSymTable;
	// finding the last entry
	while (temp->next != NULL)
	{
		printf("-->s");
		temp = temp->next;
	}
	printf("\n");

	tableEntry new_tableEntry;
	new_tableEntry = (tableEntry) malloc(sizeof(struct tableEntry_struct));
	new_tableEntry->identifier = identifier;
	printf("new_tableEntry->identifier: %s\n", new_tableEntry->identifier);
	new_tableEntry->typ = typ;
	printf("new_tableEntry->typ: %d\n", new_tableEntry->typ);
	new_tableEntry->arity = arity;
	printf("new_tableEntry->arity: %s\n", new_tableEntry->arity);
	new_tableEntry->next = NULL;
	// Initializing actSymTable with the first entry
	if (firstEntry==1){
		actSymTable = new_tableEntry;
		printf("\nInitializing actSymTable->identifier: %s\n", actSymTable->identifier);
		firstEntry = 0;
	}
	// appending
	else{
		temp->next = new_tableEntry;
		printf("\nWhen actSymTable should not be changed: actSymTable->identifier: %s\n", actSymTable->identifier);

	}
	return new_tableEntry;
}

/**
 * @brief function to check if the table has been initialized and if not, initialize it
 * 
 */
void checkListe()
{
	if (initialized != 1)
	{
		printf("\n------------initializing symboltable----------\n");
		actSymTable = malloc(sizeof(struct tableEntry_struct));
		actSymTable->next = NULL;
		initialized = 1;
		firstEntry = 1;
	}
	else{

	}
} 
/**
 * @brief funciton to delete an entry
 * NOT USED
 * 
 */
void delete_right(){
	tableEntry tmp   = actSymTable->next;
	actSymTable->next = actSymTable->next->next;
	free(tmp);
	
}

/**
 * @brief deleting an entry with help of an identifier
 * NOT USED
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

/**
 * @brief Function to print the table
 * 
 */
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

/**
 * @brief  Funktion um einen Eintrag auf basis des Identifiers zu suchen
* Zeiger geht die Liste durch, bis er den Eintrag findet oder auf NULL steht
* NOT USED
*/


tableEntry search_for(char *identifier) {
	while (actSymTable != NULL) {
		if (actSymTable->identifier == identifier)
			return actSymTable;
		actSymTable = actSymTable->next;
	}
	return NULL;
}