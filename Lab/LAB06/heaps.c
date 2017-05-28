#include <stdio.h>
#include <stdlib.h>
#include "lab6.h"

struct Heap * initMinHeap()
{
    struct Heap* hPtr = (struct Heap*)malloc(sizeof(struct Heap));
    hPtr->count = 0;
    return hPtr;
}

void insertMinHeap(struct Heap * h, struct Data d)
{
    // initilaztion with Child/Parent Index
    int childIndex = ++(h->count);
    int parentIndex = childIndex/2;
    // insert
    while (parentIndex > 0) {
        // Compare with data @ Parent Index
        if (h->heapArray[parentIndex].data.data > d.data) {
            h->heapArray[childIndex].data.data = h->heapArray[parentIndex].data.data;
            childIndex = parentIndex;
            parentIndex = childIndex/2;
        } else {
            h->heapArray[childIndex].data.data = d.data;
            return;
        }
    }
    // when this is the first node;
    (h->heapArray[childIndex]).data.data = d.data;
}

void heaprify(struct Heap * h, int c)
{
    // initialization
    int parentIndex = c, childIndex = 2*c;
    struct Data temp;
    // bubble down
    while (childIndex <= h->count) {
        if (childIndex < h->count) {
            if (h->heapArray[childIndex].data.data > h->heapArray[childIndex+1].data.data) {
                childIndex++;
            }
        }
        if (h->heapArray[parentIndex].data.data > h->heapArray[childIndex].data.data) {
            temp = h->heapArray[parentIndex].data;
            h->heapArray[parentIndex] = h->heapArray[childIndex];
            h->heapArray[childIndex].data = temp;
        }
        parentIndex = childIndex;
        childIndex = 2*parentIndex;
        
    }
}


struct Data removeMinHeap(struct Heap * h)
{
    struct Data returnD = h->heapArray[1].data;
    h->heapArray[1] = h->heapArray[h->count];
    h->count--;
    heaprify(h, 1);
    return returnD;
}


void freeMinHeap(struct Heap * h)
{
    free(h);
}