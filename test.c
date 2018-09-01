/*
 * @file test.c
 * @author Sophia Deak
 * @date May 2018
 * @brief implements functions used in test harness
 * **/

#include <stdio.h>
#include <stdlib.h>

#include "test.h"

int printTestResult(const int result){
        if(result){
                printf("test passed\n");
        }
        else {
                printf("test failed\n");
        }
        return result;
}


void printUpdate (const char * update){
        printf("********************** %s *************************\n", update);
}


int compareInt(void *data1, void *data2){
        if(*(int *)data1 == *(int *)data2){
                return 0;
        }
        if(*(int *)data1 < *(int *)data2){
                return -1;
        }
        if(*(int *)data1 > *(int *)data2){
                return 1;
        }
        else{
                printf("Error occured\n");
                return 99;
        }
}

void destroyInt(void *data){

}

void printInt(void *data){
    printf("node data: %d\n", (*(int *)data));
}

void *copyInt(void *data){
    int x = *((int *)data);
    void *xPt = &x;
    return xPt;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~ char functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int compareChar(void *data1, void *data2){ 
        if(*(char *)data1 == *(char *)data2){
                return 0;
        }
        if(*(char *)data1 < *(char *)data2){
                return -1;
        }
        if(*(char *)data1 > *(char *)data2){
                return 1;
        }
        else{
                printf("Error occured\n");
                return 99;
        }
}


void destroyChar(void *data){
    return;
}

void printChar(void *data){
    printf("char: %c\n", (*(char *)data));
}
