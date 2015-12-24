/**********************************************************************************
 *** 2D dynamic array allocator in C, contiguous in memory.
 *** Contains functions: 
 ***  - array2D_contiguous: allocates 2D of given dimensions and initializes to zero.
 ***  - free_array2D_contiguous: frees memory allocated by array2D_contiguous
 ***  The current program show the use of these functions by allocating a 2D array,
 ***  assigning values and printing the values and the memory locations, so the user
 ***  can see that they are contiguous in memory.
 ***
 ***  Remember: the hexadecimal system uses digits 0-9 and a-f to represent values
 ***  from zero to sixteen.
 ***
 *** Author: Nikos Tryfonidis, 2015
 **********************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* Functions */
double **array2D_contiguous (int nRows, int nCols);
void free_array2D_contiguous(double **array2D);

int main (int argc, char *argv[]) 
{
  long int i, j, nRows, nCols;
  double **array2D;

  // Test: give dimensions for dynamic array
  nRows = 4;
  nCols = 4;

  /* Allocation of 2D dynamic array, contiguous in memory */
  array2D = array2D_contiguous (nRows, nCols);
  /* Allocation End */

  /* Test print array values and memory locations 
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


  //Free memory:
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

/* Frees memory reserved for 2D array that has been created with
   the "array2D_contiguous" function.
 */
void free_array2D_contiguous(double **array2D)
{
  free(array2D[0]); 
  free(array2D);
}
