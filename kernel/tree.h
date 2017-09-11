#ifndef _TREE_H
#define _TREE_H

#include <stdint.h>
#include <stddef.h>

//An AVL Tree Implementation 

struct node {
	uint32_t start;
	uint32_t size; 
	struct node* left;
	struct node* right;
}; 

typedef struct node node_t; 

struct tree {
	node_t root; 
};

typedef struct tree tree_t;





#endif