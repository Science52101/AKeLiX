#ifndef AKEDEX_STX
#define AKEDEX_STX

typedef struct CdMg CodeManager;

signed pccsCode1 (CodeManager *);


#include <math.h>

struct CdMg
{
  signed code;

  signed (*pccsCode)();
};

signed pccsCode1 (CodeManager* this)
{
  double y = (double) this->code / 10;
  
  y = 512 * log(sin(y) * sin(y/2) * cos(y+3) + cos(y/3) * sin(y*2) * sin(y*2-1) + 2);

  this->code = (int) y;

  return this->code;
}

#endif
