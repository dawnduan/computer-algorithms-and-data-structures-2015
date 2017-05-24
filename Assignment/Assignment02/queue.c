#include "queue.h"

struct Queue initQueue()
{
    struct Queue Queue;
    
    Queue.currSize = 0;
    Queue.rear = NULL;
    Queue.front = NULL;
    //*qPtr = Queue;
    return Queue;
}

void enqueue(struct Queue *qPtr, struct Data d)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->data = d;
        newNode->next = NULL;
        // Check if the queue is empty [if Head]
        if (qPtr->rear == NULL) {
            qPtr->rear = newNode;
            qPtr->front = newNode;
        } else {
            qPtr->rear->next = newNode;
            qPtr->rear = newNode;
        }
    qPtr->currSize++;
    }
}

struct Data dequeue(struct Queue *qPtr)
{
    struct Node* temp = qPtr->front;
    struct Data nodeVal = temp->data;
    // if Head
    if (qPtr->front == qPtr->rear) {
        qPtr->front = NULL;
        qPtr->rear = NULL;
    } else {
        qPtr->front = temp->next;
    }
    //free(temp);
    qPtr->currSize--;
    free(temp);
    return nodeVal;
}
void freeQueue(struct Queue *qPtr)
{
    while (qPtr->currSize != 0) {
        dequeue(qPtr);
    }
    //free(qPtr);
}
