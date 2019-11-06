#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H
#include "BruteForce.h"

unsigned int addToSet(unsigned int set, int vertex);

unsigned int removeFromSet(unsigned int set, int vertex);

bool isInSet(unsigned int set, int vertex);

int howManyElementsInSet(unsigned int set);

int count(int **lookupCosts, int **lookupPath, int vertex, unsigned int set, int *arr, int **costs, int size);

Path * dynamicProgramming(int *arr, int **costs, int size);

#endif // DYNAMICPROGRAMMING_H
