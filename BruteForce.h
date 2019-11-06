#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

struct Path
{
    int cost;
    int *shortestPath;
};

int sumCosts(int *arr, int **costs, int size);

void copyArray(int *from, int *to, int size);

Path *bruteForce(int *a, int **costs, int n);

void printResult(Path *p, int size);

#endif // BRUTEFORCE_H