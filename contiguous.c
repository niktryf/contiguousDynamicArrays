/**********************************************************************************
 *** 2D & 3D dynamic array allocator in C, contiguous in memory.
 *** Contains functions:
 *** 
 ***  - array2D_contiguous_double: allocates 2D of given dimensions and initializes 
 ***    to zero.
 ***  - free_array2D_contiguous_double: frees memory allocated by 
 ***    array2D_contiguous_double.
 ***
 ***  - array3D_contiguous_double: allocates 3D of given dimensions and initializes 
 ***    to zero.
 ***  - free_array3D_contiguous_double: frees memory allocated by 
 ***    array3D_contiguous_double.
 ***
 ***  Note: The functions have been tested with valgrind and have been shown to 
 ***        contain no memory leaks.
 ***
 ***  The current program shows the use of these functions by allocating a 2D & 3D array,
 ***  assigning values and printing the values and the memory locations, so the user
 ***  can see that they are contiguous in memory.
 ***
 ***  Remember: the hexadecimal system uses digits 0-9 and a-f to represent values
 ***  from 0 to 16.
 ***
 *** Author: Nikos Tryfonidis, 2015
 **********************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* Functions */
double **array2D_contiguous (int nRows, int nCols);
void free_array2D_contiguous(double **array2D);
double ***array3D_contiguous_double (int nRows, int nCols, int nStacks);
void free_array3D_contiguous(double ***array3D);

int main (int argc, char *argv[]) 
{
  long int i, j, k, nRows, nCols, nStacks;
  double **array2D, ***array3D;

  // Test: give dimensions for dynamic array
  nRows = 4;
  nCols = 4;
  nStacks = 4;

  /* Allocation of 2D dynamic array, contiguous in memory */
  array2D = array2D_contiguous (nRows, nCols);
  array3D = array3D_contiguous_double (nRows, nCols, nStacks);
  /* Allocation End */

  /* 2 Array: Test print array values and memory locations 
     (for sizes <= 10).
  */
  if (nRows <=10 & nCols <= 10) {
    //Test: assign values
    for (i=0;i<nRows;i++) {
      for (j=0;j<nCols;j++) {
        array2D[i][j] = i*nCols + j;
      }
    }

    //Test: print values
    printf("\nValues:\n");
    for (i=0;i<nRows;i++) {
      for (j=0;j<nCols;j++) {
        printf("%04.1f ", array2D[i][j]);
      }
      printf("\n");
    }

    //Test: print memory locations
    printf("\nMemory locations:\n");
    for (i=0;i<nRows;i++) {
      for (j=0;j<nCols;j++) {
        printf("%p ", (void *)&array2D[i][j]);
      }
      printf("\n");
    }
    printf("\n\n");
  }

  /* 3D Array: Test print array values and memory locations 
     (for sizes <= 10).
  */
  if (nRows <=10 & nCols <= 10 & nStacks <= 10) {
    //Test: assign values
    for (i=0;i<nRows;i++) {
      for (j=0;j<nCols;j++) {
        for (k=0;k<nStacks;k++) {
          array3D[i][j][k] = i;
        }
      }
    }

    //Test: print values
    printf("\nValues:\n");
    for (i=0;i<nRows;i++) {
      for (j=0;j<nCols;j++) {
        for (k=0;k<nStacks;k++) {
          printf("%04.1f ", array3D[i][j][k]);
        }
        printf("\n");
      }
      printf("\n");
    }

    //Test: print memory locations
    printf("\nMemory locations:\n");
    for (i=0;i<nRows;i++) {
      for (j=0;j<nCols;j++) {
        for (k=0;k<nStacks;k++) {
          printf("%p ", (void *)&array3D[i][j][k]);
        }
        printf("\n");
      }
      printf("\n");
    }
    printf("\n");
  }


  //Free memory:
  free_array3D_contiguous(array3D);
  free_array2D_contiguous(array2D);

  return 0;
}

/* Allocates 2D dynamic array of doubles 
   with given dimensions, contiguous in memory. 
   Array is initialized to zeros.
*/
double **array2D_contiguous (int nRows, int nCols) 
{
  int i, j;
  double **array2D;

  // Allocate row storage:
  array2D = (double **)malloc(nRows * sizeof(double *));
  if (array2D == NULL) {
    printf("Out of memory (array2D_contiguous, pointer array)! Exiting...\n");
    exit(-1);
  }

  // Allocate big chunk o' memory:
  array2D[0] = (double *)malloc(nRows * nCols * sizeof(double));
  if (array2D[0] == NULL) {
    printf("Out of memory (array2D_contiguous, chunk array)! Exiting...\n");
    exit(-1);
  }

  // Point
  for (i=1;i<nRows;i++) {
    array2D[i] = array2D[i-1] + nCols;
  }

  // Initialize to zero:
  for (i=0;i<nRows;i++) {
    for (j=0;j<nCols;j++) {
      array2D[i][j] = 0;
    }
  }

  return array2D;
}

/* Allocates 3D dynamic array of doubles 
   with given dimensions, contiguous in memory. 
   Array is initialized to zeros.
*/
double ***array3D_contiguous_double (int nRows, int nCols, int nStacks) 
{
  int i, j, k;
  double ***array3D;

  // Allocate pointers to pointers to rows
  array3D = (double ***) malloc(nRows*sizeof(double **));
  if (array3D == NULL) {
      printf("ERROR: array3d_contiguous_double : pointers to pointers to rows allocation failed!\n");
      exit(1);
  }

  // Allocate pointer to rows
  array3D[0] = (double **) malloc(nRows*nCols*sizeof(double *));
  if (array3D[0] == NULL) {
      printf("ERROR: array3d_contiguous_double : pointers to rows allocation failed!\n");
      exit(1);
  }

  // Allocate rows
  array3D[0][0] = (double *) malloc(nRows*nCols*nStacks*sizeof(double));
  if (array3D[0][0] == NULL) {
      printf("ERROR: array3d_contiguous_double : rows allocation failed!\n");
      exit(1);
  }

  // Point First Row "Pencils"
  for (j=1;j<nCols;j++) {
    array3D[0][j] = array3D[0][j-1] + nStacks;
  }

  // Point all pencils
  for (i=1;i<nRows;i++) {
    array3D[i] = array3D[i-1] + nCols;
    array3D[i][0] = array3D[i-1][0] + nCols*nStacks;
    for (j=1;j<nCols;j++) {
        array3D[i][j] = array3D[i][j-1] + nStacks;
    }
  }

  // Initialize to zero:
  for (i=0;i<nRows;i++) {
    for (j=0;j<nCols;j++) {
      for (k=0;k<nStacks;k++) {
        array3D[i][j][k] = 0.0;
      }
    }
  }

  return array3D;
}

/* Frees memory reserved for 2D array that has been created with
   the "array2D_contiguous" function.
 */
void free_array2D_contiguous(double **array2D)
{
  free(array2D[0]); 
  free(array2D);
}

/* Frees memory reserved for 3D array that has been created with
   the "array3D_contiguous_double" function.
 */
void free_array3D_contiguous(double ***array3D)
{
  free(array3D[0][0]);
  free(array3D[0]); 
  free(array3D);
}
