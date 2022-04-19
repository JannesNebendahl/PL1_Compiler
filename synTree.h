#include "symTab.h"
typedef enum nodeT{all_node, exist_node, and_node, or_node, negation, predicate, func, variable,true_node, false_node, num, arg};
struct node
{
    enum nodeT nodeType; //Knotentyp zuordnen
    union {
        struct quantor { 
            struct node* var;
            struct node* formula;
        };
        struct binary_juctor {  
            struct node* formula_left;
            struct node* formula_right;
        };
        struct unary_juctor { 
            struct node* formula;
        };
        struct predicate { 
            tableEntry tableEntry; //struct tableEntry*
            struct node* argument;
        };
        struct function { 
			tableEntry tableEntry; //struct tableEntry*
            struct node* argument;
        };
		struct variable { 
		tableEntry tableEntry; //struct tableEntry*
		};
		// = TRUE
		// 
        bool True;
        bool False;
		struct number{ 
		int number;
		}number_struct;
        struct argument { 
            struct node* argument;
            struct node* next;
        }argument_struct;
    };
    
};

// make_binary_node, ...
// Symboltabelleneintrag �bergeben und argumentliste
