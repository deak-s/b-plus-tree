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

void *testArray[4] = {xPt, yPt, zPt};

BTree *testTree = createBTree(3, compareChar, destroyChar, printChar);

Node *root = createleafNode(3);
root->myTree = testTree;

//inserting 2 and 'a'
printf("inserting 2 and a\n");
//insertToLeaf(root, xPt, cxPt); 
insert(root, xPt, cxPt);

//inserting 5 and 'b'
printf("inserting 5 and b\n");
//insertToLeaf(root, yPt, cyPt);
insert(root, yPt, cyPt);

//inserting 3 and 'c'
printf("inserting 3 and c\n");
//insertToLeaf(root, zPt, czPt);
Node *newRoot = insert(root, zPt, czPt);

printUpdate("printing middle");
printf("leaf d %d\n", root->numberOfKeys);
//printLeaf(root);
printMiddle(newRoot);

/*
printUpdate("node is splitting");
Node *newRoot = splitNode(root);
printLeaf(newRoot->children[0]);
printf("other child\n");
printLeaf(newRoot->children[1]);
*/

printUpdate("split complete");
/*
printf("inserting 4 and e\n");
Node *located = findLeaf(newRoot, aPt);
printLeaf(located);
insertToLeaf(located, aPt, caPt);

printf("middle after 4 and e\n");
printMiddle(newRoot);

*/

/*
printUpdate(" inserting 8 and f");

Node *loc8 = findLeaf(newRoot, bPt);
printf("leaf for 8 and f located\n");
printLeaf(loc8);

printf("inserting 8 and f to leaf\n");
insertToLeaf(loc8, bPt, cbPt);
*/




return 0;
}
