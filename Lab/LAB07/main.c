#include "lab7.h"

struct flowNetwork * createGraph(){
    struct flowNetwork * fN = initFlowNetwork();
    insertAdjMatrix(fN->adjMatrix, 0, 3, 0, 10);
    insertAdjMatrix(fN->adjMatrix, 0, 2, 0, 12);
    insertAdjMatrix(fN->adjMatrix, 0, 1, 0, 5);
    insertAdjMatrix(fN->adjMatrix, 1, 4, 0, 6);
    insertAdjMatrix(fN->adjMatrix, 2, 5, 0, 11);
    insertAdjMatrix(fN->adjMatrix, 4, 5, 0, 5);
    insertAdjMatrix(fN->adjMatrix, 3, 5, 0, 5);
    insertAdjMatrix(fN->adjMatrix, 3, 7, 0, 5);
    insertAdjMatrix(fN->adjMatrix, 4, 5, 0, 5);
    insertAdjMatrix(fN->adjMatrix, 5, 7, 0, 10);
    insertAdjMatrix(fN->adjMatrix, 5, 6, 0, 8);
    insertAdjMatrix(fN->adjMatrix, 7, 8, 0, 16);
    insertAdjMatrix(fN->adjMatrix, 6, 8, 0, 9);
    return fN;
}

int main( int argc, char *argv[] ){
    struct flowNetwork * fN =createGraph();
    int i;
    printAdjMat(fN->adjMatrix);
    printf("Parent Array: ");
    for (i=0; i<NODES; i++) {
        printf("%d ", fN->parent[i]);
    }
    printf("\nVisited Nodes Array: ");
    for (i=0; i<NODES; i++) {
        printf("%d ", fN->visitedNodes[i]);
    }
    printf("\n");
    deleteFlowNetwork(fN);
}
