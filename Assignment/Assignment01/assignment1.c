#include "assignment1.h"
#include <stdio.h>
#include <stdlib.h>

void denseMatrixMult(int ** A, int ** B, int *** resultMatrix, int n)
{
    //initialization
    int **M0,**M1,**M2,**M3,**M4,**M5,**M6,**M0B,**M0A,**M1A,**M1B,**M2A,**M2B,**M3A,**M3B,**M4A,**M4B,**M5A,**M5B,**M6A,**M6B,**zeroMat;
    int **C2,**C3,**C4,**C1,i,j, **C11,**C12,**C41,**C42,**result;
    initMatrix(&zeroMat,n);
    initMatrix(&result,n);
    
    
    //base case
    if (n == 1) {
        result[0][0] =  A[0][0]*B[0][0];
        *resultMatrix = result;
    } else {
        //Strassen's Algorithm
        M0A = sum(A,A,0,0,n/2,n/2,n/2);
        M0B = sum(B,B,0,0,n/2,n/2,n/2);
        denseMatrixMult(M0A,M0B,&M0,n/2);
        
        M1A = sum(A,A,n/2,0,n/2,n/2,n/2);
        M1B = sum(B,zeroMat,0,0,0,0,n/2);
        denseMatrixMult(M1A,M1B,&M1,n/2);
        
        M2A = sum(A,zeroMat,0,0,0,0,n/2);
        M2B = sub(B,B,0,n/2,n/2,n/2,n/2);
        denseMatrixMult(M2A,M2B,&M2,n/2);
        
        M3A = sum(A,zeroMat,n/2,n/2,0,0,n/2);
        M3B = sub(B,B,n/2,0,0,0,n/2);
        denseMatrixMult(M3A,M3B,&M3,n/2);
        
        M4A = sum(A,A,0,0,0,n/2,n/2);
        M4B = sum(B,zeroMat,n/2,n/2,0,0,n/2);
        denseMatrixMult(M4A,M4B,&M4,n/2);
        
        M5A = sub(A,A,n/2,0,0,0,n/2);
        M5B = sum(B,B,0,0,0,n/2,n/2);
        denseMatrixMult(M5A,M5B,&M5,n/2);
        
        M6A = sub(A,A,0,n/2,n/2,n/2,n/2);
        M6B = sum(B,B,n/2,0,n/2,n/2,n/2);
        denseMatrixMult(M6A,M6B,&M6,n/2);
    
    
    //compute Matrix C
        C11 = sub(M3,M4,0,0,0,0,n/2);
        C12 = sum(C11,M0,0,0,0,0,n/2);
        C1 = sum(M6,C12,0,0,0,0,n/2);
        C2 = sum(M2,M4,0,0,0,0,n/2);
        C3 = sum(M1,M3,0,0,0,0,n/2);
        C41 = sub(M0,M1,0,0,0,0,n/2);
        C42 = sum(M2,M5,0,0,0,0,n/2);
        C4 = sum(C41,C42,0,0,0,0,n/2);
        
        
        //Combine 4 matrices
        for (i = 0; i<n/2 ; i++) {
            for (j = 0; j<n/2; j++) {
                result[i][j] = C1[i][j];
                result[i][n/2+j] = C2[i][j];
                result[n/2+i][j] = C3[i][j];
                result[n/2+i][n/2+j] = C4[i][j];
            }
        }
        *resultMatrix = result;
        
        //free ptrs
        freeMatrix(n/2,M0);
        freeMatrix(n/2,M1);
        freeMatrix(n/2,M2);
        freeMatrix(n/2,M3);
        freeMatrix(n/2,M4);
        freeMatrix(n/2,M5);
        freeMatrix(n/2,M6);
        freeMatrix(n/2,M0A);
        freeMatrix(n/2,M0B);
        freeMatrix(n/2,M1A);
        freeMatrix(n/2,M1B);
        freeMatrix(n/2,M2A);
        freeMatrix(n/2,M2B);
        freeMatrix(n/2,M3A);
        freeMatrix(n/2,M3B);
        freeMatrix(n/2,M4A);
        freeMatrix(n/2,M4B);
        freeMatrix(n/2,M5A);
        freeMatrix(n/2,M5B);
        freeMatrix(n/2,M6A);
        freeMatrix(n/2,M6B);
        freeMatrix(n/2,C1);
        freeMatrix(n/2,C2);
        freeMatrix(n/2,C3);
        freeMatrix(n/2,C4);
        freeMatrix(n/2,C11);
        freeMatrix(n/2,C12);
        freeMatrix(n/2,C41);
        freeMatrix(n/2,C42);
        //freeMatrix(n,result); NEVER EVER FREE THSI!!!!!!
    }
    freeMatrix(n,zeroMat);
}

int **sum(int ** A, int ** B, int x1, int y1, int x2, int y2, int n)
{
    int **sum;
    initMatrix(&sum, n);
    
    for (int i = 0; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            sum[i][j] = A[x1 + i][y1 + j] + B[x2 + i][y2 + j];
        }
    }
    return sum;
}

int **sub(int **A, int **B, int x1, int y1, int x2, int y2, int n)
{
    int **sub;
    initMatrix(&sub, n);
    
    for (int i = 0; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            sub[i][j] = A[x1 + i][y1 + j] - B[x2 + i][y2 + j];
        }
    }
    return sub;
}

void initMatrix(int ***mat,int n)
{
    int **matrix = (int **)malloc(sizeof(int*)*(unsigned long)n);
    
    if (matrix != NULL) {
        for (int i = 0; i < n ; i++) {
            matrix[i] = (int*)malloc(sizeof(int)*(unsigned long)n);
            
        }
        for (int i = 0; i<n ; i++) {
            for (int j = 0; j < n ; j ++) {
                matrix[i][j] = 0;
            }
        }
    }
    *mat = matrix;
}

int **readMatrix(char * filename)
{
    //initialization
    int **mat;
    initMatrix(&mat, MATSIZE);
    
    FILE *fp=fopen(filename,"r");
    for (int i = 0; i < MATSIZE ; i++) {
        for (int j = 0 ; j < MATSIZE ; j++ ) {
            fscanf(fp, "%d", &mat[i][j]);
        }
        //fscanf(fp,"");
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
