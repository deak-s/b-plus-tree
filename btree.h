/**
 * @file btree.h
 * @author Sophia Deak
 * @date August 2018
 * @brief header file w function definitions for b tree
 **/

#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
typedef struct tree BTree;
typedef struct node Node;


struct node{
    bool leaf;
    int degree;
    int numberOfKeys;
    BTree *myTree;
    Node *parent;
    void **keys;
    
    Node **children;
    void **data;
};

struct tree {
    int degree;
    Node *root;
    int (*compare)(void *data1, void *data2);
    void (*destroy)(void *data);
    void (*print)(void *data);
};


//create empty leaf node of a certain degree
Node *createleafNode(int degree);

//create empty middle node of certain degree
Node *createMidNode(int degree);


BTree *createBTree(int degree, 
                   int (*compare)(void *data1, void *data2),
                   void (*destroy)(void *data),
                   void (*print)(void *data));

Node *insert(Node *root, void *key, void *data);

/* inserts a key/data pair to a leaf node
 * @param theLeaf leafNode pointer to node to insert to
 * @param key void ptr to key to insert
 * @param data void ptr to data to insert
 * @return leafNode ptr of leafNode with key and data inserted
 **/
Node * insertToLeaf(Node *theLeaf, void *key, void *data);

Node *insertToMiddle(Node *theMiddle, void *key, Node *leftChild, Node *rightChild);

Node *insertAbove(Node *theNode, void *key, Node *leftChild, Node *rightChild);
//return pointer to new root node
Node *splitNode(Node *theNode);

Node *findLeaf(Node *root, void *key);
#endif
