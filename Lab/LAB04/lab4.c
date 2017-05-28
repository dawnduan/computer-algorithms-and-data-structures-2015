#include "lab4.h"

void insertNode(int d, struct Node ** lPtr)
{
    // Initialization
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    
    // Assignment of newNode
    if (newNode != NULL) {
        newNode -> data = d;
        newNode -> next = NULL;
    }
    
    // check if the list's head
    if (*lPtr == NULL) {
        *lPtr = newNode;
    }
    
    // either in the middle or end
    else {
        
        // front
        if ((*lPtr) -> data > d) {
            newNode -> next = *lPtr;
            *lPtr = newNode;
        }
        
        // middle or end
        else {
            struct Node *currNode = *lPtr;
            
            while (currNode -> next != NULL) {
                // middle
                if (currNode -> next -> data > d) {
                    newNode -> next = currNode -> next;
                    currNode -> next = newNode;
                    break;
                }
                
                // end
                else if (currNode -> next -> next == NULL) {
                    newNode -> next = currNode -> next -> next;
                    currNode -> next -> next = newNode;
                    break;
                }
                
                // update the currNode
                currNode = currNode -> next;
            }
            
        }
    
    }

}
void deleteNode(int d, struct Node ** lPtr)
{
    // Initilization
    struct Node * currNode = *lPtr, *prevNode = NULL;
    
    while (currNode != NULL) {
        // find d
        if (currNode -> data == d) {
            
            // head
            if (prevNode == NULL) {
                *lPtr = currNode -> next;
                free(currNode);
                break;
            }
            
            // either middle or end
            else {
                prevNode -> next = currNode -> next;
                free(currNode);
                break;
            }
        }
        prevNode = currNode;
        currNode = currNode -> next;
    }
}

void printList(struct Node * L)
{
    // Initilization
    struct Node * currNode = L;
    
    // print until the end
    while (currNode != NULL) {
        printf("%d ", currNode -> data);
        currNode = currNode -> next;
    }
    printf("\n");
}

struct Node ** createTable(int buckets)
{
    struct Node** tablePtr = (struct Node**)malloc(sizeof(struct Node*)*(unsigned long)buckets);
    struct Node* table[buckets];
    
    if (tablePtr != NULL) {
        *tablePtr = table[0];
        
        for (int i = 0; i < buckets; i++) {
            tablePtr[i] = NULL;
        }
    }
    return tablePtr;
}

int findHash(int key, int buckets)
{
    int res = key%buckets;
    
    return res;
}

void insertTable(int key, int buckets, struct Node ** tablePtr)
{
    int res = findHash(key, buckets);
    
    insertNode(key, &(tablePtr[res]));
}

void freeTable(struct Node ** tablePtr, int buckets)
{
    for (int i = 0; i < buckets; i++) {
        // delete the chain
        struct Node* currNode = tablePtr[i] -> next;
        while (currNode != NULL) {
            struct Node* prevNode = currNode;
            currNode = currNode -> next;
            free(prevNode);
        }
        
        // free the elem of hash
        //if (i + 1 < buckets) *tablePtr = tablePtr[i + 1];
        free(tablePtr[i]);
    }
    
    free(tablePtr);
}


