#include "assignment1.h"
#include <stdio.h>
#include <stdlib.h>

void denseMatrixMult(int ** A, int ** B, int *** resultMatrix, int n)
{
    
}
int **sum(int ** A, int ** B, int x1, int y1, int x2, int y2, int n)
{
    // TODO

}

int **sub(int **A, int **B, int x1, int y1, int x2, int y2, int n)
{
    // TODO
}

void initMatrix(int ***mat,int n)
{
    int **matrix = (int **)malloc(sizeof(int)*(unsigned long)n);
    
    if (*matrix == NULL) {
        printf("Error\n");
    }
    for (int i = 0; i < n ; i++) {
        matrix[i] = (int*)malloc(sizeof(int)*(unsigned long)n);
    }
    if (matrix == NULL) {
        printf("Error\n");
    }


    for (int i = 0; i<n ; i++) {
        for (int j = 0; j < n ; j ++) {
            matrix[i][j] = 0;
            }
        }
    *mat = matrix;
}

int **readMatrix(char * filename)
{
    int **mat, i, j;
    initMatrix(&mat, MATSIZE);
    
    //open filename and read it
    FILE *fp = fopen(filename, "r");
    
    //store every content in 2D array
    for (i=0; i<MATSIZE; i++) {
        for (j=0; j<MATSIZE; j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    fclose(fp);
    return mat;
}

void freeMatrix(int n, int ** matrix)
{
    for (int i = 0; i < n ; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void printMatrix(int n, int ** A)
{
    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n ; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}
