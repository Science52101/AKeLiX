#include "../AKeMaX/AKeVeX.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

struct mtx
{
  double* els;
  unsigned long n, m;
};

Matrix* mkMatrix (double** arrs, unsigned long n, unsigned long m)
{
  Matrix* this = (Matrix*)malloc(sizeof(Matrix));
  
  this->els = (double*)malloc(sizeof(double)*n*m);
  this->n   = n                                  ;
  this->m   = m                                  ;

  for (unsigned long i = 0; i < n; i ++)
    memcpy(this->els + (i * m), arrs[i], m);

  return this;
}

void stMatrix (Matrix* this, double** arrs, unsigned long n, unsigned long m)
{
  double* tmp = this->els;

  this->els = (double*)malloc(sizeof(double)*n*m);
  this->n   = n                                  ;
  this->m   = m                                  ;

  free(tmp);

  for (unsigned long i = 0; i < this->n; i ++)
    memcpy(this->els + (i * this->m), arrs[i], this->m);

  return;
}

double** gtArrays (Matrix* this)
{
  double** arrs = (double**)malloc(sizeof(double*)*this->n);

  for (unsigned long i = 0; i < this->n; i ++)
  {
    arrs[i] = (double*)malloc(sizeof(double)*this->m);
    memcpy(arrs[i], this->els + (i * this->m), this->m);
  }

  return arrs;
}

unsigned long* gtDimsns (Matrix* this)
{
  return (unsigned long[]){this->n, this->m};
}
