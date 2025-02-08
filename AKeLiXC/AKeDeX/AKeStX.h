#ifndef AKEDEX_STX
#define AKEDEX_STX

typedef struct Coord Coordinate;

Coordinate *    mkCoord  (double     *, unsigned   long               );
void            stCoord  (Coordinate *, double     *   , unsigned long);
double     *    gtCoord  (Coordinate *                                );
unsigned   long gtDimsn  (Coordinate *                                );
double          distance (Coordinate *, Coordinate *                  );

#endif
