#include "symTab.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int initialized;
tableEntry actSymTable = NULL;

void init()
{
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
tableEntry insert_right(char identifier[], typ typ, int arity)
{
	printf("SYM: Inserting %s into the symboltable with arity %d\n", identifier, arity);
	tableEntry new_tableEntry;
	new_tableEntry = (tableEntry)malloc(sizeof(struct tableEntry_struct));
	strcpy(new_tableEntry->identifier, identifier);
	new_tableEntry->typ = typ;
	new_tableEntry->arity = arity;
	new_tableEntry->next = NULL;

	// Initializing actSymTable with the first entry
	if (actSymTable == NULL)
	{
		printf("\n------------initializing symboltable----------\n");
		actSymTable = new_tableEntry;
	}


	// appending
	else
	{
		tableEntry temp = actSymTable;
		// finding the last entry
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_tableEntry;
		temp = NULL;
		// free(temp);
	}
	return new_tableEntry;
}


/**
 * @brief funciton to delete an entry
 * NOT USED
 *
 */
void delete_right()
{
	tableEntry temp = actSymTable;
	tableEntry tmp = temp->next;
	temp->next = temp->next->next;
	free(tmp);
}

/**
 * @brief deleting an entry with help of an identifier
 * NOT USED
 */
void delete (char *identifier)
{
	tableEntry begin = actSymTable;
	tableEntry del = begin, previous;

	// wenn der erste Eintrag der richtige ist
	if (del != NULL && del->identifier == identifier)
	{
		begin = del->next;
		free(del);
		return;
	}
	// durchiterieren der Liste
	while (del != NULL && del->identifier == identifier)
	{
		previous = del;
		del = del->next;
	}

	// wenn kein Eintrag gefunden werden kann
	if (del == NULL)
		return;
	// löschen des Eintrags
	previous->next = del->next;
	free(del);
	begin =NULL;
}

/**
 * @brief Function to print the table
 *
 */
void printList()
{
	printf("\n------Actual symboltable-------:\n");
	char const *typen[] = {"Predicate", "Function", "Variable"};
	int index = 1;
	tableEntry temp = actSymTable;
	while (temp != NULL)
	{
		printf("\n----%d----\n", index);
		printf("ID: %s \n", temp->identifier);
		printf("Typ: %s \n", typen[temp->typ]);
		printf("Arity: %d \n", temp->arity);
		index++;
		temp = temp->next;
	}
	temp = NULL;
	printf("\n-----------------------------\n", index);
}
	

/**
 * @brief  Funktion um einen Eintrag auf basis des Identifiers zu suchen
 * Zeiger geht die Liste durch, bis er den Eintrag findet oder auf NULL steht
 */

tableEntry search_for(char *identifier)
{
	tableEntry temp = actSymTable;
	while (temp != NULL)
	{
		if ((strcmp(temp->identifier, identifier)==0))
			return temp;
		temp = temp->next;
	}
	return NULL;
}