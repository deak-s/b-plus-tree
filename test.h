/*
 * @file test.h
 * @author Sophia Deak
 * @date May 2018
 * @brief header file for functions used in test harness
 **/

#ifndef TEST_H
#define TEST_H

int printTestResult(const int result);

void printUpdate(const char * update);


int compareInt(void *data1, void *data2);

void destroyInt(void *data);

void printInt(void *data);

void *copyInt(void *data);



int compareChar(void *data1, void *data2);
void destroyChar(void *data);
void printChar(void *data);

#endif
