#include <stdlib.h>
#include <stdio.h>

#include "AKeMaX/AKeVeX.h"

signed main()
{
  tmp0[0] = (double*)malloc(sizeof(double)*2);
  tmp0[1] = (double*)malloc(sizeof(double)*2);

  tmp0[0][0] = 1; tmp0[1][0] = 0;
  tmp0[0][1] = 0; tm

  Matrix* basis = mkMatrix(tm

  free(tmp0[0]); free(tmp0[1]);
  free(tmp0   );

  tmp0 = (double**)malloc(sizeof(double*)*3);
  
  tmp0[0] = (double*)malloc(sizeof(double)*3);
  tmp0[1] = (double*)malloc(sizeof(double)*3);
  tmp0[2] = (double*)malloc(sizeof(double)*3);

  tmp0[0][0] = 3; tmp0[1][0] = 3; tmp0[2][0] = 0;
  tmp0[0][1] = 3; tmp0[1][1] = 1; tmp0[2][1] = 2;
  tmp0[0][2] = 0; tmp0[1][2] = 1; tmp0[2][2] = 1;
 
  Matrix* X = mkMatrix(tmp0, 3, 3);

  free(tmp0[0]); free(tmp0[1]); free(tmp0[2]);
  free(tmp0   );

  printf("declared `X    ` as   `Matrix *` with `mkMatrix` .\n");

  printf("%f\n", gtElBIdx(X, 3, 2));

  printf("got      `2, 3 ` from `X       ` with `gtElBIdx` .\n");

  return 0;
}
