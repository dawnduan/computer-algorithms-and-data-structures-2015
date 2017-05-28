#include "lab7.h"

struct flowNetwork * initFlowNetwork(){
    int i;
    struct flowNetwork* fN = (struct flowNetwork*)malloc(sizeof(struct flowNetwork));
    if (fN != NULL) {
        fN->adjMatrix = initAdjMatrix();
        for (i = 0; i < NODES; i++) {
            fN->visitedNodes[i] = 0;
            fN->parent[i] = -1;
        }
        
    }
    return fN;
}

void deleteFlowNetwork(struct flowNetwork * fN){
    deleteAdjMatrix(fN->adjMatrix);
    free(fN);
}