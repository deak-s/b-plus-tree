/**
 * @file helperFunctions.h
 * @author Sophia Deak
 * @date August 2018
 * @brief helper functions for implementation of b+ tree in file btree.c
 **/

#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H


//finds position in array sorted least to greatest
//returns int index

int sortedArrayPos(void *data, void *array[], int (*compare)(void *data1, void *data2));

// inserts element at index int - shifts existing element rightwards
// arrayCapacity is number of elements - not total capacity
void insertAtPos(void *element, void *array[], int pos, int numberOfElements);

// inserts node at index int - shifts existing elements rightwards
void insertNodeAtPos(Node *element, Node *array[], int pos, int numberOfElements);

void printLeaf(Node *theLeaf);

void printMiddle(Node *theMiddle);


//helper functions for splitting nodes

//returns ptr to left segment of node
Node *grabLeft(Node *);

//returns ptr to right segment of node
Node *grabRight(Node *);

//returns key from middle of node (to insert above)
void *grabMiddle(Node *);

void destroyNode(Node *);
#endif
