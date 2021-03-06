/**
 * @file helperFunctions.c
 * @author Sophia Deak
 * @date August 2018
 * @brief implementations of helper functions for b+ tree
 *        defined in helperFunctions.h, for btree.c
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "btree.h"
#include "helperFunctions.h"

int sortedArrayPos(void *data, void* array[], int arraySize, int (*compare)(void *data1, void *data2)){
    int x = 0;

   //case element is smallest in array
   if (array[x] == NULL){
       printf("array 0 is null\n");
       return x;
   }

    if(compare(data, array[x]) == -1 ){
        printf("array smaller than element 0\n");
        return x;
    }

    for(x ; x < arraySize; x++){
        //if data < pos and data > pos-1 
        if((compare(data, array[x]) == -1) && (compare(data, array[x-1]) == 1)){
            //break;
            return x;
        }
     }
    return x;
}



void insertAtPos(void *element, void *array[], int pos, int numberOfElements){
    //case: first element in array
    if(pos == 0 && array[0] == NULL){
        array[pos] = element;
        return;
    }

    //case: element added at end of array
    if(pos > numberOfElements){
        array[pos] = element;
        return;
    }
    memmove(&array[pos+1], &array[pos], ((numberOfElements - pos) * sizeof(element)));
    array[pos] = element;
    return;
}

void insertNodeAtPos(Node *element, Node *array[], int pos, int numberOfElements){
    //case: first element in array
    if(pos == 0 && array[0] == NULL){
        array[pos] = element;
        return;
    }
    //case: last element in array
    if(pos > numberOfElements){
        array[pos] = element;
        return;
    }

    memmove(&array[pos+1], &array[pos], ((numberOfElements - pos) * sizeof(element)));
    array[pos] = element;
    return;
}

void overwriteNodeAtPos(Node *element, Node *array[], int pos){
    destroyNode(array[pos]);

    array[pos] = element;
    return;
}


void printLeaf(Node *theLeaf){
    int x = 0;
    printf("printing leaf. leaf has %d keys\n", theLeaf->numberOfKeys);
    while( x < theLeaf->numberOfKeys){
        printf("key: %d\n", (*(int *)theLeaf->keys[x]));
        theLeaf->myTree->print(theLeaf->data[x]);
        x++;
    }
}

void printMiddle(Node *theMiddle){
    int x = 0;
    while(x < theMiddle->numberOfKeys){
        printf("key: %d\n", (*(int *)theMiddle->keys[x]));
        x += 1;
    }
}

//helper functions for splitting nodes

//returns node ptr 
Node *grabLeft(Node *theNode){
    Node *leftNode;
    if(theNode->leaf){
        //create new node 
        leftNode = createleafNode(theNode->degree);
        leftNode->myTree = theNode->myTree;
        //copy keys over
        int n = theNode->numberOfKeys;
        memmove(&leftNode->keys[0], &theNode->keys[0], (floor (n/2) * sizeof(void *)));

        //copy datas over
        memmove(&leftNode->data[0], &theNode->data[0], (floor (n/2)  * sizeof(void *)));

        leftNode->numberOfKeys = floor (n/2) ;
    }

    else{
        printf("grabbing left of middle node\n");
        leftNode = createMidNode(theNode->degree);
        leftNode->myTree = theNode->myTree;

        int n = theNode->numberOfKeys;
        printf("grabbing %d elements for left\n", (int)(floor(n/2)));

        memmove(&leftNode->keys[0], &theNode->keys[0], (floor(n/2)) * sizeof(void *));

        memmove(&leftNode->children[0], &theNode->children[0], (floor(n / 2) + 1) * sizeof(Node *));
        leftNode->numberOfKeys = floor (n/2);
    }

    return leftNode;

}

Node *grabRight(Node *theNode){
    Node *rightNode;
    if(theNode->leaf){
        //create new node
        rightNode = createleafNode(theNode->degree);
        rightNode->myTree = theNode->myTree;
        int n = theNode->numberOfKeys;
        int middle = (floor(n/2));

        //copy keys over
        memmove(&rightNode->keys[0], &theNode->keys[middle], ((n - (floor(n/2))) * sizeof(void *)));

        //copy datas over
        memmove(&rightNode->data[0], &theNode->data[middle], ((n - middle) * sizeof(void *)));
        rightNode->numberOfKeys = (n - floor(n/2));
    }

    else{
        printf("grabbing right of middle\n");

        rightNode = createMidNode(theNode->degree);
        rightNode->myTree = theNode->myTree;
        int n = theNode->numberOfKeys;
        int middle = floor(n/2);

        printf("node being split has = %d keys\n", n);
        printf("grabbing %d elements for right keys\n", n - (int)(floor(n/2) + 1) );
        printf("keys start from pos %d\n", middle + 1);
        printf("first key is %d\n", (* (int *) theNode->keys[middle + 1]));
        
        //used to be &rightNode->keys[(int)(floor (n/2) + 1)]
        memmove(&rightNode->keys[0], &theNode->keys[middle + 1], ((n - (middle + 1)) * sizeof(void *)));

        memmove(&rightNode->children[0], &theNode->children[middle + 1], (n - floor(n / 2)) * sizeof(void *));

        rightNode->numberOfKeys = (int)(floor(n/2));
        printMiddle(rightNode);

    }
    return rightNode;
}

void *grabMiddle(Node *theNode){
    //middle key is the floor(n / 2) + 1 th element
    int n = theNode->numberOfKeys;
    return theNode->keys[(int)(floor(n / 2))];
}

void destroyNode(Node *theNode){
    if(theNode != NULL){

        free(theNode->keys);

        if(theNode->leaf){
            free(theNode->data);
        }    
        else{
            free(theNode->children);
        }
    }
}


bool isFull(Node * theNode){
    if(theNode->numberOfKeys == theNode->degree){
        printf("node full!\n");
        return true;
    }
    
    else{
        return false;
    }
}
