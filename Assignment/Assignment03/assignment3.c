#include "assignment3.h"

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

int breadthFirstPathSearch(struct flowNetwork * fN, int s, int t){
    // initialization
    int i;
    struct Data d;
    for (i = 0; i < NODES; i++) {
        fN->visitedNodes[i] = 0;
    }
    // enqueue the starting Node
    struct Queue *Q;
    initQueue(&Q);
    d.vertex = s;
    enqueue(Q, d);
    // path finding
    while (Q->currSize != 0) {
        d = *(Q->front->data);
        dequeue(Q, &d);
        int vi = d.vertex;
        // find children(adj)
        for (i = 0; i < NODES; i++) {
            if (fN->adjMatrix[vi][i].flowCap != 0) {
                if (fN->visitedNodes[i] == 0) {
                    if (fN->adjMatrix[vi][i].flowCap > fN->adjMatrix[vi][i].flow) {
                        fN->visitedNodes[i] = 1;
                        fN->parent[i] = vi;
                        d.vertex = i;
                        enqueue(Q, d);
                    }
                }
            }
        }
    }
    // free Q
    while (Q->currSize != 0) {
        d = *(Q->front->data);
        dequeue(Q, &d);
    }
    free(Q);
    // conclusion
    if (fN->visitedNodes[t] == 0) {
        return 0;
    } else {
        return 1;
    }
}

void maximizeFlowNetwork(struct flowNetwork * fN, int s, int t){
    int temp = -1;
    
    while (breadthFirstPathSearch(fN, s, t) == 1) {
        // Bread First Path
        // initialize currFlow & minFlow in the new Round
        int currFlow = -1;
        int minFlowCap = INF;
        
        while ((currFlow < minFlowCap) && (breadthFirstPathSearch(fN, s, t) == 1)) {
            int vi = -1, vj = t;
            int maxFlowAdd = INF;
            
            // find the maxFlowAdd in this round
            while (vi != s) {
                vi = fN->parent[vj];
                temp = fN->adjMatrix[vi][vj].flowCap - fN->adjMatrix[vi][vj].flow;
                minFlowCap = (minFlowCap < fN->adjMatrix[vi][vj].flowCap) ? minFlowCap : fN->adjMatrix[vi][vj].flowCap;
                maxFlowAdd = (maxFlowAdd < temp) ? maxFlowAdd : temp;
                vj = vi;
            }
            
            vj = t;
            vi = -1;
            // Add maxFlowAdd to the current path
            while (vi != s) {
                vi = fN->parent[vj];
                fN->adjMatrix[vi][vj].flow += maxFlowAdd;
                // back flow
                fN->adjMatrix[vj][vi].flow -= maxFlowAdd;
                currFlow = fN->adjMatrix[vi][vj].flow;
                vj = vi;
            }
        }
    }
}