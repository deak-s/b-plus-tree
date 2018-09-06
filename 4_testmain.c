/**
 * @file 4_testmain.c
 * @author Sophia Deak
 * @date Setp 2018
 * @brief  main function for testing a degree 4 b+ tree using functions from btree.c
 */



#include <stdio.h>
#include <stdlib.h>

#include "btree.h"
#include "test.h"
#include "helperFunctions.h"


int main(){

    int intArray[13] =  { 2, 5, 3, 4, 8, 6, 1, 13, 16, 11, 15, 18, 23};
    void *keyArray[13];

    char charArray[13] ={ 'a', 'b', 'c', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'm', 'o', 'p'}; 
    void *dataArray[13];

    makeIntPtrsVoid(intArray, keyArray, 13);
    makeCharPtrsVoid(charArray, dataArray, 13);



    printInt(keyArray[3]);
    printChar(dataArray[3]);
    }
