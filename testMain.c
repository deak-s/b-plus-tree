/**
 * @file testMain.c
 * @author Sophia Deak
 * @date August 2018
 * @brief main function for testing functions from btree.c
 **/


#include <stdio.h>
#include <stdlib.h>

#include "btree.h"
#include "test.h"
#include "helperFunctions.h"

int main(){


int deg = 3;

int x = 2;
int y = 5;
int z = 3;
int a = 4;
int b = 8;

void *xPt = &x;
void *yPt = &y;
void *zPt = &z;
void *aPt = &a;
void *bPt = &b;

int q = 9;
void *qPt = &q;


char cx = 'a';
char cy = 'b';
char cz = 'c';
char ca = 'e';
char cb = 'f';
void *cxPt = &cx;
void *cyPt = &cy;
void *czPt = &cz;
void *caPt = &ca;
void *cbPt = &cb;

void *testArray[4] = {xPt, zPt};


BTree *testTree = createBTree(3, compareInt, destroyChar, printChar);

Node *root = createleafNode(3);
root->myTree = testTree;

//inserting 2 and 'a'
printf("inserting 2 and a\n");
//insertToLeaf(root, xPt, cxPt); 
insert(root, xPt, cxPt);

//inserting 5 and 'b'
printf("inserting 5 and b\n");
insert(root, yPt, cyPt);

//inserting 3 and 'c'
printf("inserting 3 and c\n");
Node *newRoot = insert(root, zPt, czPt);

printUpdate("printing middle");
printf("leaf d %d\n", root->numberOfKeys);
printMiddle(newRoot);
printLeaf(newRoot->children[0]);
printLeaf(newRoot->children[1]);

printf("inserting 4 and e\n");
newRoot = insert(newRoot, aPt, caPt);

printf("middle after 4 and e\n");
printMiddle(newRoot);



printUpdate(" inserting 8 and f");

Node *loc8 = findLeaf(newRoot, bPt);

printf("inserting 8 and f to leaf\n");
newRoot = insert(loc8, bPt, cbPt);



return 0;
}
