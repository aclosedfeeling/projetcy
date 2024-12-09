#include "avl.h"

AVLNode *AVLNode_init(void *element, int keyFunction(void *element)){
	
	AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
	node->element = element;
	node->left = NULL;
	node->right = NULL;
	node->balance = 0;
	node->height = 1;
	
	node->keyFunction = keyFunction;
	node->key = node->keyFunction(element);
	return node;
	
}
AVLNode *AVLNode_initwkey(void *element, int key){
	
	AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
	node->element = element;
	node->left = NULL;
	node->right = NULL;
	node->balance = 0;
	node->height = 1;
	node->key = key;
		
	return node;
	
}
/******************************************************Fonction utilitaire***************************************************/
int max(int a, int b){
	return (a > b) ? a : b;
}
int getHeight(AVLNode *node){
	return (node != NULL) ? node->height : 0;
}
int getBalance(AVLNode *node){
	return (node != NULL) ? getHeight(node->left) - getHeight(node->right) : 0;
}
/******************************************************Fonction AVL***************************************************/
AVLNode *AVLNode_searchFromID(AVLNode *node, int key){
	
	if(node == NULL){
		return NULL;
	}else if(node->key == key){
		return node;
	}else if(node->key < key){
		return AVLNode_searchFromID(node->left, key);
	}else if(node->key > key){
		return AVLNode_searchFromID(node->right, key);
	}
	
}
AVLNode *AVLNode_insertionwkey(AVLNode *node, void *element, int key) {
    if (node == NULL) {
        return AVLNode_initwkey(element, key);
    }
    if (key < node->key) {
        node->left = AVLNode_insertionwkey(node->left, element, key);
    } else if (key > node->key) {
        node->right = AVLNode_insertionwkey(node->right, element, key);
    } else {
        printf("Error, equal keys\n");
        return node;
    }

    // Update height of this node
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // Balance the node
    return AVLNode_balance(node, element);
}

AVLNode *AVLNode_insertion(AVLNode *node, void *element, int keyFunction(void *element)) {
    if (node == NULL) {
        return AVLNode_init(element, keyFunction);
    }

    int key = keyFunction(element);
    if (key < node->key) {
        node->left = AVLNode_insertion(node->left, element, keyFunction);
    } else if (key > node->key) {
        node->right = AVLNode_insertion(node->right, element, keyFunction);
    } else {
        printf("Error, equal keys\n");
        return node;
    }

    // Update height of this node
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // Balance the node
    return AVLNode_balance(node, element);
}

AVLNode *AVLNode_balance(AVLNode *node, void *element) {
    int balance = getBalance(node);
    int key = node->keyFunction(element);

    // Left Left Case
    if (balance > 1 && key < node->left->key) {
        return AVLNode_rotation_right(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->right->key) {
        return AVLNode_rotation_left(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = AVLNode_rotation_left(node->left);
        return AVLNode_rotation_right(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = AVLNode_rotation_right(node->right);
        return AVLNode_rotation_left(node);
    }

    return node; // No rotation needed
}

AVLNode *AVLNode_rotation_right(AVLNode *node) {
    AVLNode *newRoot = node->left;
    AVLNode *temp = newRoot->right;

    // Perform rotation
    newRoot->right = node;
    node->left = temp;

    // Update heights
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

AVLNode *AVLNode_rotation_left(AVLNode *node) {
    AVLNode *newRoot = node->right;
    AVLNode *temp = newRoot->left;

    // Perform rotation
    newRoot->left = node;
    node->right = temp;

    // Update heights
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}