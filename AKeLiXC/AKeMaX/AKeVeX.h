#ifndef AKEDEX_STX
#define AKEDEX_STX

typedef struct mtx Matrix;

Matrix*        mkMatrix (double**, unsigned long, unsigned long)         ;
void           stMatrix (Matrix*, double**, unsigned long, unsigned long);
double**       gtArrays (Matrix*)                                        ;
unsigned long* gtDimsns (Matrix*)                                        ;
#endif
