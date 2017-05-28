#include <stdio.h>
#include <stdlib.h>
#include "lab6.h"

void initQueue(struct Queue ** qPtr)
{
    struct Queue* qPr = (struct Queue*)malloc(sizeof(struct Queue));
    if (qPr != NULL) {
        qPr->currSize = 0;
        qPr->front = 0;
        qPr->rear = 0;
        *qPtr = qPr;
    }
}

int isEmpty(struct Queue * Q)
{
    if (Q->currSize == 0) {
        return 1;
    } else {
        return 0;
    }
}

void enqueue(struct Queue * Q, struct Data d)
{
    //int isFull = (Q->currSize >= MaxQueueSize) ? 1 : 0;
    //if (!isFull) {
        Q->queueArray[Q->rear].data.data = d.data;
        Q->rear = (Q->rear + 1)%MaxQueueSize;
        Q->currSize++;
    //}
}

void dequeue(struct Queue * Q, struct Data *d)
{
    if (!isEmpty(Q)) {
        *d = Q->queueArray[Q->front].data;
        Q->front = (Q->front+1)%MaxQueueSize;
        Q->currSize--;
    }
    
}

void freeQueue(struct Queue * q)
{
    free(q);
}