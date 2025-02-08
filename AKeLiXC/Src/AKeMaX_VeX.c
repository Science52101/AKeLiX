#include "../AKeMaX/AKeVeX.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

struct mtx
{
  double   *    els   ;
  unsigned long n  , m;
};

Matrix* mkMatrix (double** arrs, unsigned long n, unsigned long m)
{
  if (!arrs || n == 0 || m == 0) return NULL;

  Matrix* this = (Matrix*)malloc(sizeof(Matrix));

  if (!this) return NULL;
  
  this->els = (double*)malloc(sizeof(double)*n*m);

  if (!this->els)
  {
    free(this);

    return NULL;
  }

  this->n = n;
  this->m = m;

  for (unsigned long i = 0; i < n; i ++)
    memcpy(this->els + (i * m), arrs[i], sizeof(double)*m);

  return this;
}

void stMatrix (Matrix* this, double** arrs, unsigned long n, unsigned long m)
{
  if (!arrs || n == 0 || m == 0) return;

  this->els = (double*)realloc(this->els, sizeof(double)*n*m);

  if (!this->els) return;

  this->n = n;
  this->m = m;

  for (unsigned long i = 0; i < this->n; i ++)
    memcpy(this->els + (i * this->m), arrs[i], sizeof(double)*this->m);

  return;
}

void dlMatrix (Matrix* this)
{
  
  if (!this) return;

  if (this->els) free(this->els);

  free(this);

  return;
}

double** gtArrays (Matrix* this)
{
  double** arrs = (double**)malloc(sizeof(double*)*this->n);

  for (unsigned long i = 0; i < this->n; i ++)
  {
    arrs[i] = (double*)malloc(sizeof(double)*this->m);

    memcpy(arrs[i], this->els + (i * this->m), sizeof(double)*this->m);
  }

  return arrs;
}

unsigned long* gtDimsns (Matrix* this)
{
  return (unsigned long[]){this->n, this->m};
}

signed vdElBIdx (Matrix* this, unsigned long i, unsigned long j)
{
  return i <= this->m && j <= this->n && i > 0 && j > 0;
}

double gtElBIdx (Matrix* this, unsigned long i, unsigned long j)
{
  if (!vdElBIdx(this, i, j)) return NAN;

  i --;
  j --;

  return this->els[i*this->m+j];
}
