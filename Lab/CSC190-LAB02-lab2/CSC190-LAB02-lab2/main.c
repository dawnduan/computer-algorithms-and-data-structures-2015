#include "lab2.h"
#include <stdlib.h>
#include <stdio.h>

void initMatrix(int ***mat,int n)
{
    int i,j;
    int **matrix = (int **)malloc(sizeof(int*)*(unsigned long)n);
    for (i=0; i<n; i++) {
        matrix[i] = (int*)malloc(sizeof(int)*(unsigned long)n);
        for (j=0; j<n; j++) {
            matrix[i][j] = 0;
        }
    }
    *mat = matrix;
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
    int **mat;
    initMatrix(&mat, MATSIZE);
    int i,j;
    FILE *fp = fopen(filename, "r");
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
    initMatrix(&matA, n);
    initMatrix(&matB, n);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            sum[i][j] = matA[i][j]+matB[i][j];
        }
    }
    return sum;
}

int **sub(int **A, int **B, int x1, int y1, int x2, int y2, int n)
{
    //int subA, subB,i,j,sum;
    //for (i=0; i<n; i++) {
    //for (j=0; j<n; j++) {
    //  subA[i][j] = A[x1][y1];
    //subB[i][j] = B[x2][x2];
    // }
    //  }
    //for (i=0; i<n; i++) {
    //for (j=0; j<n; j++) {
    //   sum = subA[i][j] - subB[i][j];
    //  }
    //}
    int **matA, **matB, **sub, i, j;
    initMatrix(&matA, n);
    initMatrix(&matB, n);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            sub[i][j] = matA[i][j]-matB[i][j];
        }
    }
    return sub
}