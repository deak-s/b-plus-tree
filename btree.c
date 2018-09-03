/**
 * @file btree.c
 * @author Sophia Deak
 * @date August 2018
 * @brief implementations of functions in btree.h for creation of b tree
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "btree.h"
#include "helperFunctions.h"


Node *createleafNode(int degree){
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->leaf = true;
    newNode->degree = degree;
    newNode->numberOfKeys = 0;
    newNode->myTree = NULL;
    newNode->parent = NULL;
    //allocate 1 extra space so node can go over capacity before splitting
    newNode->keys = calloc(sizeof(void *), degree);
    newNode->data = calloc(sizeof(void *), degree);

    newNode->children = NULL;
    return newNode;
}


Node *createMidNode(int degree){
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->leaf = false;
    newNode->degree = degree;
    newNode->myTree = NULL;
    newNode->parent = NULL;
    newNode->numberOfKeys = 0;
    //add 1 extra space so node can go over capacity
    newNode->keys = calloc(sizeof(void *), (degree ));
    newNode->children = calloc(sizeof(Node *), degree + 1);

    newNode->data = NULL;
    return newNode;
}




BTree *createBTree(int degree,
        int (*compare)(void *data1, void *data2),
        void (*destroy)(void *data),
        void (*print)(void *data)){

    BTree *newTree = (BTree *)malloc(sizeof(BTree));
    newTree->degree = degree;
    newTree->root = NULL;
    newTree->compare = compare;
    newTree->destroy = destroy;
    newTree->print = print;
    return newTree;
}

//
Node *insert(Node *root, void *key, void *data){

    //if root is not leaf - go to leaf
    if(root->leaf == false){
        root = findLeaf(root, key);
    }

    //insert data to leaf
    root = insertToLeaf(root, key, data);

    while(isFull(root)){
        root = splitNode(root);
    }

    return root;
}

Node * insertToLeaf(Node *theLeaf, void *key, void *data){
    int pos = sortedArrayPos(key, theLeaf->keys, theLeaf->myTree->compare);
    insertAtPos(data, theLeaf->data, pos, (theLeaf->numberOfKeys));
    insertAtPos(key, theLeaf->keys, pos, (theLeaf->numberOfKeys));

    theLeaf->numberOfKeys++;
    printf("leaf now has %d\n", theLeaf->numberOfKeys);
    printf("leaf degree is %d\n", theLeaf->degree);
    return theLeaf;
}



Node *insertToMiddle(Node *theMiddle, void *key, Node *leftChild, Node *rightChild){
    printf("inserting to middle\n");

    int pos = sortedArrayPos(key, theMiddle->keys, theMiddle->myTree->compare);
    printf("break 1\n");
    insertAtPos(key, theMiddle->keys, pos, (theMiddle->numberOfKeys - 1)); 
    printf("break 2\n");

    insertNodeAtPos(leftChild, theMiddle->children, pos, theMiddle->numberOfKeys);
    printf("break 3\n");
    insertNodeAtPos(rightChild, theMiddle->children, (pos+1), theMiddle->numberOfKeys);
    printf("break 4\n");

    theMiddle->numberOfKeys +=1;
    return theMiddle;
}


Node *insertAbove(Node *theNode, void *key, Node *leftChild, Node *rightChild){
    Node *upperNode;
    //if node is already root - must create parent
    if(theNode->parent == NULL){
        upperNode = createMidNode(theNode->degree);
        upperNode->myTree = theNode->myTree;
    }
    else{
        upperNode = theNode->parent;
    }

    //at this point upperNode should definitely exist
    leftChild->parent = upperNode;
    rightChild->parent = upperNode;
    insertToMiddle(upperNode, key, leftChild, rightChild);

    return upperNode;

}

//splits node and calls insertAbove to add keys/children to parent node
Node *splitNode(Node *theNode){
    
    printf("splitting node\n");
    Node *newRoot = insertAbove(theNode, grabMiddle(theNode), grabLeft(theNode), grabRight(theNode));
    
    return newRoot;
}


Node *findLeaf(Node *root, void *key){
    //base case
    if(root->leaf){
        return root;
    }
    else{
        int pos = sortedArrayPos(key, root->keys, root->myTree->compare);
        root = findLeaf(root->children[pos], key);
    }
}

