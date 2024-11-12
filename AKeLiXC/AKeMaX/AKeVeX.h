#ifndef AKEDEX_STX
#define AKEDEX_STX

typedef struct mtx Matrix;

Matrix   *      mkMatrix (double * *, unsigned long  , unsigned long               );
void            stMatrix (Matrix *  , double   *    *, unsigned long, unsigned long);
void            dlMatrix (Matrix *                                                 );
double   *    * gtArrays (Matrix *                                                 );
unsigned long * gtDimsns (Matrix *                                                 );
signed          vdElBIdx (Matrix *  , unsigned long  , unsigned long               );
double          gtElBIdx (Matrix *  , unsigned long  , unsigned long               );

#endif
