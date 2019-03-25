#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double *matrixSolver(double *matrix[], int r, int c) {
   double **tMatrix = (double **)malloc(sizeof(double *) * r);
   //i, j: row and column indices of temp matrix
   //ti: temp index for getting pivot = 1 & for solving row echelon
   //td: temp double that holds value of first non-zero item in a row
   int i, j, ti;
   double td;
   //get temporary matrix
   for(i = 0; i < r; i++)
      tMatrix[i] = (double *)malloc(sizeof(double) * c);
   for(i = 0; i < r; i++) {
      for(j = 0; j < c; j++)
         tMatrix[i][j] = matrix[i][j];
   }

   //get row echelon form of matrix
   for(i = 0; i < r; i++) {
      //set i-th column values to 1
      for(ti = i; ti < r; ti++) {
         td = tMatrix[ti][i];
         for(j = i; j < c; j++)
            tMatrix[ti][j] /= td;
      }

      //subtract i-th row from lower rows
      for(ti = i+1; ti < r; ti++) {
         for(j = i; j < c; j++)
            tMatrix[ti][j] -= tMatrix[i][j];
      }
   }
   
   //solve for variables
   double *result = (double *)malloc(sizeof(double) * r);
   for(i = r-1; i >= 0; i--) {
      result[i] = tMatrix[i][c-1];
      for(ti = c-2; ti > i; ti--) {
         result[i] -= tMatrix[i][ti] * result[ti];
      }
      result[i] /= tMatrix[i][i];
   }
   
   return result;
}

void main() {
   double **matrix;
   double *result;
   int ir, ic, r, c, useRand;
   double d;
   printf("Enter rows: ");
   scanf("%d", &r);
   printf("Enter columns: ");
   scanf("%d", &c);
   matrix = (double **)malloc(sizeof(double *) * r);
   printf("Use random numbers to fill matrix?(1/0) ");
   scanf("%d", &useRand);
   for(ir = 0; ir < r; ir++)
      matrix[ir] = (double *)malloc(sizeof(double) * c);
   for(ir = 0; ir < r; ir++) {
      for(ic = 0; ic < c; ic++) {
         if(!useRand) {
            printf("Enter matrix[%d][%d]: ", ir, ic);
            scanf("%lf", &d);
            matrix[ir][ic] = d;
         }
         else {
            matrix[ir][ic] = rand() % (r*4);
            printf("matrix[%d][%d] = %f\n", ir, ic, matrix[ir][ic]);
         }
      }
   }
   result = matrixSolver(matrix, r, c);
   for(ir = 0; ir < r; ir++) {
      printf("X%d = %f\n", ir+1, result[ir]);
   }
}
