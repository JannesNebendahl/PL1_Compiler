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