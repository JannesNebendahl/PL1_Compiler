#include "SynTree.h"
#include <stdlib.h>
//enum nodeT{all, exist, and, or, implication, equivalence, negation, predicate, function, variable,true_node, false_node, number_t, argument_t};
/**
 * @brief Function to 
 * 
 * @param node 
 * @return struct node* 
 */
struct node* entfDoppNegation(struct node* node)
{
    struct node* rueck;
	switch (node->nodeType)
	{
		case negation:
            if(node->unary_junctor.formula->nodeType == negation){
                printf("OPT: Found double negation\n");
				rueck = entfDoppNegation(node->unary_junctor.formula->unary_junctor.formula);
                free(node->unary_junctor.formula);
                free(node);
            }else{
                rueck = entfDoppNegation(node->unary_junctor.formula);
				rueck = node;

            }
			break;
        case all:
		case exist:
			rueck = entfDoppNegation(node->quantor_struct.formula);
            node->quantor_struct.formula = rueck;
            rueck = node;
			break;
		case and:
		case or:
		case implication:
		case equivalence:
            struct node* left = entfDoppNegation(node->binary_struct.formula_left);
			struct node* right = entfDoppNegation(node->binary_struct.formula_right);
            node->binary_struct.formula_left = left;
            node->binary_struct.formula_right = right;
            rueck = node;
			break;
		default:
		    rueck = node;
	}
    return rueck;
}

struct node* verschiebeNegation(struct node* node){
	struct node* rueck;
	switch (node->nodeType){
	    case negation:
            struct node* newLeft;
            struct node* newRight;
			struct node* newNegationNode ;
            switch(node->unary_junctor.formula->nodeType){
                case and:
                    printf("OPT: Shift Negation in Conjunction\n");
                    newLeft = makeNegationNode(node->unary_junctor.formula->binary_struct.formula_left);
                    newRight = makeNegationNode(node->unary_junctor.formula->binary_struct.formula_right);
                    rueck = makeDisjunctionNode(newLeft, newRight);
                    free(node->unary_junctor.formula);
                    free(node);
                    break;
                case or:
                    printf("OPT: Shift Negation in Disjunction\n");
                    newLeft = makeNegationNode(node->unary_junctor.formula->binary_struct.formula_left);
                    newRight = makeNegationNode(node->unary_junctor.formula->binary_struct.formula_right);
                    rueck = makeConjunctionNode(newLeft, newRight);
                    free(node->unary_junctor.formula);
                    free(node); 
                    break;
                case exist:
                    printf("OPT: Shift Negation in Exist\n");
					newNegationNode = makeNegationNode(node->unary_junctor.formula->quantor_struct.formula);
					rueck = makeAllNode(node->unary_junctor.formula->quantor_struct.var,newNegationNode);
                    free(node->unary_junctor.formula);
					free(node);
                    break;
                case all:
                    printf("OPT: Shift Negation in All\n");
                    newNegationNode = makeNegationNode(node->unary_junctor.formula->quantor_struct.formula);
					rueck = makeExistNode(node->unary_junctor.formula->quantor_struct.var,newNegationNode);
                    free(node->unary_junctor.formula);
                    free(node);
                    break;
                default:
                    rueck = node;
					break;
            }
			break;
        case all:
		case exist:
			rueck = verschiebeNegation(node->quantor_struct.formula);
            node->quantor_struct.formula = rueck;
            rueck = node;
			break;
		case and:
		case or:
		case implication:
		case equivalence:
            struct node* left = verschiebeNegation(node->binary_struct.formula_left);
			struct node* right = verschiebeNegation(node->binary_struct.formula_right);
			node->binary_struct.formula_left = left;
            node->binary_struct.formula_right = right;
            rueck = node;
			break;
		default:
			rueck = node;
	}
	return rueck;
}

struct node* makeFormulaEasier(struct node* node){
    struct node* rueck;
    struct node* left;
    struct node* right;
	switch (node->nodeType){
		case and:
		case or:
	    case negation:
        case all:
		case exist:
			rueck = makeFormulaEasier(node->quantor_struct.formula);
            node->quantor_struct.formula = rueck;
            rueck = node;
			break;
		case implication:
            printf("OPT: Make Implication easier\n");
            left = makeConjunctionNode(node->binary_struct.formula_left, node->binary_struct.formula_right);
            struct node* rightNegLeft = makeNegationNode(node->binary_struct.formula_left);
            struct node* rightNegRight = makeNegationNode(node->binary_struct.formula_right);
            right = makeConjunctionNode(rightNegLeft, rightNegRight);
            rueck = makeDisjunctionNode(left, right);
            free(node);
            break;
		case equivalence:
            printf("OPT: Make Equivalence easier\n");
            left = makeNegationNode(node->binary_struct.formula_left);
            right = node->binary_struct.formula_left;
            rueck = makeDisjunctionNode(left, right);
            free(node);
			break;
		default:
			rueck = node;
	}
	return rueck;
}

struct node* makeBoolOperations(struct node* node){
    struct node* rueck;
    switch (node->nodeType){
		case and:
            if(node->binary_struct.formula_left->nodeType == true_node){
                printf("OPT: Refactor unnecessary Conjunction with left Formula\n");
                rueck = node->binary_struct.formula_left;
            }
            else if(node->binary_struct.formula_right->nodeType == true_node){
                printf("OPT: Refactor unnecessary Conjunction with right Formula\n");
                rueck = node->binary_struct.formula_right;
            }
            else if(node->binary_struct.formula_left->nodeType == false_node || node->binary_struct.formula_right->nodeType == false_node){
                printf("OPT: Refactor unnecessary Conjunction with False\n");
                rueck = makeFalseNode();
                free(node);
            }
            else{
                rueck = node;
            }
		case or:
            if(node->binary_struct.formula_left->nodeType == true_node || node->binary_struct.formula_right->nodeType == true_node){
                printf("OPT: Refactor unnecessary Disjunction with True\n");
                rueck = makeTrueNode();
                free(node);
            }
            else if(node->binary_struct.formula_left->nodeType == false_node){
                printf("OPT: Refactor unnecessary Disjunction with left Formula\n");
                rueck = node->binary_struct.formula_left;
            }
            else if(node->binary_struct.formula_right->nodeType == false_node){
                printf("OPT: Refactor unnecessary Disjunction with right Formula\n");
                rueck = node->binary_struct.formula_right;
            }
            else{
                rueck = node;
            }
	    case negation:
            if(node->unary_junctor.formula == true_node){
                printf("OPT: Refactor Negation True with False\n");
                rueck = makeFalseNode();
                free(node);
            }else if(node->unary_junctor.formula == false_node){
                printf("OPT: Refactor Negation False with True\n");
                rueck = makeTrueNode();
                free(node);
            }else{
                rueck = node;
            }
        case equivalence:
		case implication:
        case all:
		case exist:
			rueck = makeFormulaEasier(node->quantor_struct.formula);
            node->quantor_struct.formula = rueck;
            rueck = node;
			break;
		default:
			rueck = node;
	}
	return rueck;
}

struct node* optimzeFormula(struct node* node)
{
    node = makeBoolOperations(node);
    node = makeFormulaEasier(node);
	node = verschiebeNegation(node);
		printTree(node, 0);
    node = entfDoppNegation(node);
		printTree(node, 0);

    return node;
}	