#include "../AKeDeX/AKeStX.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Coord
{
  double   *     coords;
  unsigned long  dimsns;
};

Coordinate* mkCoord (double* coords, unsigned long dimsns)
{
  Coordinate* this = (Coordinate*)malloc(sizeof(Coordinate));
  
  this->coords = (double*)malloc(sizeof(double)*dimsns);
  this->dimsns = dimsns                                ;

  memcpy(this->coords, coords, sizeof(double)*dimsns);

  return this;
}

void stCoord (Coordinate* this, double* coords, unsigned long dimsns)
{
  double* tmp = this->coords;

  this->coords = (double*)malloc(sizeof(double)*dimsns);

  free(tmp);

  memcpy(this->coords, coords, sizeof(double)*dimsns);

  return;
}

double* gtCoord (Coordinate* this)
{
  return this->coords;
}

unsigned long gtDimsn (Coordinate* this)
{
  return this->dimsns;
}

double distance (Coordinate* this, Coordinate* that)
{
  if (this->dimsns != that->dimsns) return 0;

  double r = 0;

  for (unsigned long i = 0; i < this->dimsns; i ++)
    r += pow(this->coords[i] - that->coords[i], 2);

  return sqrt(r);
}
