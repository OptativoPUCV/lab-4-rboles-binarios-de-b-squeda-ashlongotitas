#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{

    TreeMap *new = (TreeMap *) malloc(sizeof(TreeMap));
    if(new == NULL) return NULL;

    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    if (tree == NULL || key == NULL || value == NULL) return;
    if (searchTreeMap(tree, key) != NULL) return; 

    TreeNode *new = createTreeNode(key, value);
    if (new == NULL) return;

    TreeNode *parent = NULL;
    TreeNode *current = tree->root;
    while (current != NULL)
    {
        parent = current;
        if (tree->lower_than(key, current->pair->key))
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    new->parent = parent;
    if (parent == NULL) tree->root = new;
    else if (tree->lower_than(key, parent->pair->key)) 
    {
        parent->left = new;
    }
    else 
    {
        parent->right = new;
    }
    tree->current = new;
}

TreeNode * minimum(TreeNode * x)
{
    if (x == NULL) return NULL;
    while (x->left != NULL) 
    {
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
    if (tree == NULL || node == NULL) return;
    TreeNode *parent = node->parent;
    if (node->left == NULL && node->right == NULL)
    {
        if(parent == NULL) tree->root = NULL;
        else if (parent->left == node)
        {
            parent->left = NULL;
        } 
        else 
        {
            parent->right = NULL;
        }
        free(node->pair);
        free(node);
    }

    else if (node->left == NULL || node->right == NULL)
    {
        TreeNode *hijo = (node->left != NULL) ? node->left : node->right;
        hijo->parent = parent;
        if (parent == NULL) tree->root = hijo;
        else if (parent->left == node)
        {
            parent->left = hijo;
        } 
        else
        {
            parent->right = hijo;
        }
        free(node->pair);
        free(node);
    }

    else
    {
        TreeNode *sucesor = minimum(node->right);
        node->pair->key = sucesor->pair->key;
        node->pair->value = sucesor->pair->value;
        removeNode(tree, sucesor);
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode *current = tree->root;
    while (current != NULL)
    {
        if (is_equal(tree, key, current->pair->key))
        {
            tree->current = current;
            return current->pair;
        }
        else if (tree->lower_than(key, current->pair->key))
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    tree->current = NULL;
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
