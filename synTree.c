#include "symTab.h"
#include "synTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct node* makeTrueNode(){
	struct node* new_node = malloc(sizeof(struct node));
	new_node->nodeType = true_node;
}

struct node* makeFalseNode(){
	struct node* new_node = malloc(sizeof(struct node));
	new_node->nodeType = false_node;
}

struct node* makeAllNode(struct node* formula_node){
	struct node* new_node = malloc(sizeof(struct node));
	new_node->nodeType = all_node;
	new_node->formula = formula_node;
}

struct node* makeExistNode(struct node* formula_node){
	struct node* new_node = malloc(sizeof(struct node));
	new_node->nodeType = exist_node;
	new_node->formula = formula_node;
}

/**
 * @brief Creates Conjunction
 * 
 * @param formula_left_node 
 * @param formula_right_node 
 * @return struct node* 
 */
struct node* makeConjunctionNode(struct node* formula_left_node, struct node* formula_right_node){
	struct node* new_node = malloc(sizeof(struct node));
	new_node->nodeType = and_node;
	new_node->formula_left = formula_left_node;
	new_node->formula_right = formula_right_node;

}
/**
 * @brief Creates Disjunction
 * 
 * @param formula_left_node 
 * @param formula_right_node 
 * @return struct node* 
 */
struct node* makeDisjunctionNode(struct node* formula_left_node, struct node* formula_right_node){
	struct node* new_node = malloc(sizeof(struct node));
	new_node->nodeType = or_node;
	new_node->formula_left = formula_left_node;
	new_node->formula_right = formula_right_node;

}

struct node* makeNegationNode(struct node* formula_node){
	struct node* new_node = malloc(sizeof(struct node));
	new_node->nodeType = negation;
	new_node->formula = formula_node;
}

struct node* makePredicateNode(struct node* argument_node){
	struct node* new_node = malloc(sizeof(struct node));
	new_node->nodeType = predicate;
	new_node->argument = argument_node;
}

struct node* makeFunctionNode(struct node* argument_node){
	struct node* new_node = malloc(sizeof(struct node));
	new_node->nodeType = func;
	new_node->argument = argument_node;
}

struct node* makeVariableNode(){
	struct node* new_node = malloc(sizeof(struct node));
	new_node->nodeType = variable;
}

struct node* makeNumNode(int num_value){
	struct node* new_node = malloc(sizeof(struct node));
	new_node->nodeType = num;
	new_node->number = num_value;
}

struct node* makeArgumentNode(struct node* argument_node, struct node* next_node){
	struct node* new_node = malloc(sizeof(struct node));
	new_node->nodeType = arg;
	new_node->argument = argument_node;
	new_node->next = next_node;
}