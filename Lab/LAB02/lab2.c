#include "lab2.h"
#include <stdlib.h>
#include <stdio.h>

void initMatrix(int ***mat,int n)
{
    int i, j, **matrix = (int **)malloc(sizeof(int*)*(unsigned long)n);
    if (matrix != NULL) {
        {
            for (i=0; i<n; i++) {
                matrix[i] = (int*)malloc(sizeof(int)*(unsigned long)n);
                for (j=0; j<n; j++) {
                    matrix[i][j] = 0;
                }
            }
        }
    *mat = matrix;
    free(matrix);    
}

void freeMatrix(int n, int ** matrix)
{
    int i;
    for (i=0; i<n; i++) {
        free(matrix[i]);
    }
    free(matrix);
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

void printMatrix(int n, int ** A)
{
    int i, j;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
    freeMatrix(n, A);
}

int **sum(int ** A, int ** B, int x1, int y1, int x2, int y2, int n)
{
    int **matA, **matB, **sum, i, j;
    initMatrix(&sum, n);
    initMatrix(&matA, n);
    initMatrix(&matB, n);
    
    //conduct two submatrix from A, B from the A(x1, y1) and B(x2, y2) with matrix size of n
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            matA[i][j] = A[x1+i][y1+j];
            matB[i][j] = B[x2+i][y2+j];
        }
    }
    
    //perform sub-matrix addtion
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            sum[i][j] = matA[i][j]+matB[i][j];
        }
    }
    return sum;
}

int **sub(int **A, int **B, int x1, int y1, int x2, int y2, int n)
{
    int **matA, **matB, **sub, i, j;
    initMatrix(&sub, n);
    initMatrix(&matA,n);
    initMatrix(&matB,n);
    
    //conduct two submatrix from A, B from the A(x1, y1) and B(x2, y2) with matrix size of n
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            matA[i][j] = A[x1+i][y1+j];
            matB[i][j] = B[x2+i][y2+j];
        }
    }
    
    //perform sub-matrix subtraction
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            sub[i][j] = matA[i][j]-matB[i][j];
        }
    }
    return sub;
}