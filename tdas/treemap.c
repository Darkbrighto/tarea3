#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}

TreeNode* createTreeNode(void* key, void* value)
{
    TreeNode* new = (TreeNode*)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair*)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap* createTreeMap(int (*lower_than)(void* key1, void* key2))
{
    TreeMap* nuevoarbol = (TreeMap*)malloc(sizeof(TreeMap));
    if (nuevoarbol == NULL) {
        return NULL;
    }

    nuevoarbol->root = NULL;        
    nuevoarbol->current = NULL;     
    nuevoarbol->lower_than = lower_than;  

    return nuevoarbol;
}

void insertTreeMap(TreeMap* tree, void* key, void* value)
{
   
    Pair* existingPair = searchTreeMap(tree, key);

    if (existingPair != NULL) {
        return;  
    }

    
    TreeNode* actual = tree->root;
    TreeNode* padre = NULL;

    
    while (actual != NULL) {
        padre = actual;
        if (tree->lower_than(key, actual->pair->key)) {
            actual = actual->left;
        } else {
            actual = actual->right;
        }
    }

    TreeNode* nuevoNodo = createTreeNode(key, value);

    nuevoNodo->parent = padre;

    if (padre == NULL) {
        tree->root = nuevoNodo;
    }

    else if (tree->lower_than(key, padre->pair->key)) {
        padre->left = nuevoNodo;
    }
    else {
        padre->right = nuevoNodo;
    }

    tree->current = nuevoNodo;
}

TreeNode* minimum(TreeNode* x) {
    while (x->left != NULL) {
        x = x->left;
    }
    return x;  
}

void removeNode(TreeMap* tree, TreeNode* node)
{
    if (node->left == NULL && node->right == NULL) {
        if (node->parent != NULL) {
            if (node->parent->left == node) {
                node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }
        } else {
            
            tree->root = NULL;
        }
        free(node);
    }
    else if (node->left == NULL || node->right == NULL) {
        TreeNode* child;
        
        if (node->left != NULL) {
            child = node->left;
        } else {
            child = node->right;
        }

        if (node->parent != NULL) {
            if (node->parent->left == node) {
                node->parent->left = child;
            } else {
                node->parent->right = child;
            }
        } else {
            tree->root = child;
        }

        child->parent = node->parent;

        free(node); 
    }
    else {
        
        TreeNode* successor = minimum(node->right);

    
        node->pair = successor->pair;

        removeNode(tree, successor);
    }
}

void eraseTreeMap(TreeMap* tree, void* key)
{
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return; 

    TreeNode* node = tree->current; 
    removeNode(tree, node); 
}

Pair* searchTreeMap(TreeMap* tree, void* key) {
    TreeNode* actual = tree->root;


    while (actual != NULL) {
        if (tree->lower_than(key, actual->pair->key) == 0 && tree->lower_than(actual->pair->key, key) == 0) {
            tree->current = actual;  
            return actual->pair;     
        }

        
        if (tree->lower_than(key, actual->pair->key)) {
            actual = actual->left;
        }
        
        else {
            actual = actual->right;
        }
    }

    
    return NULL;
}

Pair* upperBound(TreeMap* tree, void* key)
{
    TreeNode* currentNode = tree->root;
    TreeNode* ub_node = NULL;  
    
    
    while (currentNode != NULL) {
        if (is_equal(tree, currentNode->pair->key, key)) {
            
            return currentNode->pair;
        } else if (tree->lower_than(key, currentNode->pair->key)) {
          
            ub_node = currentNode;
            currentNode = currentNode->left;
        } else {
           
            currentNode = currentNode->right;
        }
    }

  
    return (ub_node != NULL) ? ub_node->pair : NULL;
}

Pair* firstTreeMap(TreeMap* tree)
{
    if (tree == NULL || tree->root == NULL) {
        return NULL;  
    }
    
  
    TreeNode* currentNode = tree->root;
    
   
    while (currentNode->left != NULL) {
        currentNode = currentNode->left;
    }
    
    
    tree->current = currentNode;
    
    
    return currentNode->pair;
}

Pair* nextTreeMap(TreeMap* tree)
{
    if (tree == NULL || tree->current == NULL) {
        return NULL;  
    }

    TreeNode* currentNode = tree->current;

   
    if (currentNode->right != NULL) {
        currentNode = currentNode->right;
        while (currentNode->left != NULL) {
            currentNode = currentNode->left;
        }
        tree->current = currentNode; 
        return currentNode->pair;
    }

   
    TreeNode* parentNode = currentNode->parent;
    while (parentNode != NULL && parentNode->right == currentNode) {
        currentNode = parentNode;
        parentNode = parentNode->parent;
    }

    
    tree->current = parentNode;
    
   
    return (parentNode != NULL) ? parentNode->pair : NULL;
}