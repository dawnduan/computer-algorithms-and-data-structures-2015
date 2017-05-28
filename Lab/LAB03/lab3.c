#include "lab3.h"
#include <stdio.h>
#include <stdlib.h>

struct functionCall * createStructArray(int n)
{
    struct functionCall * array = (struct functionCall * )malloc(sizeof(struct functionCall)*(unsigned long)n);
    
    if (array != NULL) {
        return array;
    } else {
        return NULL;
    }
}

void assignValues(struct functionCall * array, int index, int currentValueRes, int recursiveCallNumber, int exp )
{
    
    array[index].currentValueRes = currentValueRes;
    array[index].recursiveCallNumber = recursiveCallNumber;
    array[index].exp = exp;
}

void initArray(struct functionCall * array, int n)
{
    int i;
    
    for (i = 0; i < n ; i++) {
        array[i].currentValueRes = 0;
        array[i].recursiveCallNumber = 0;
        array[i].exp = 0;
    }
}

void recordRecursiveCalls(struct functionCall * array, int exp, int base)
{
    int res, i;
    
    for (i = 0; i < exp + 1; i++) {
        if (i == 0) {
            res = 1;
            assignValues(array, exp - i, res, exp + 1 - i, i);
        } else {
            res *= base;
            assignValues(array, exp - i, res, exp + 1 - i, i);
        }
    }
}

void printArray(struct functionCall * array, int n)
{
    int i;
    
    for (i = 0; i < n ; i++) {
        printf("%d %d %d\n", array[i].currentValueRes, array[i].recursiveCallNumber, array[i].exp);
    }
}

void freeArray(struct functionCall * array)
{
    free(array);
}
