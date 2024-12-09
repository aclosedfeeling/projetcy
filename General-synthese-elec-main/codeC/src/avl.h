#include <stdio.h>
#include <stdlib.h>

#ifndef __AVL_H__
#define __AVL_H__

typedef struct AVLNode
{
	void *element;
	struct AVLNode *left, *right;
	int height, balance, key;
	
	int (*keyFunction)(void *element); //Fonction pour calculer la clé
	
}AVLNode;

AVLNode *AVLNode_init(void *element, int keyFunction(void *element));
AVLNode *AVLNode_insert(void *element);
AVLNode *AVLNode_insertion(AVLNode *node, void *element, int keyFunction(void *element));

AVLNode *AVLNode_balance(AVLNode *node, void *element);

AVLNode *AVLNode_rotation_left(AVLNode *node);
AVLNode *AVLNode_rotation_right(AVLNode *node);

AVLNode *AVLNode_initwkey(void *element, int key);
AVLNode *AVLNode_insertionwkey(AVLNode *node, void *element, int key);
#endif