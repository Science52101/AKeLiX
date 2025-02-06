#include "../AKeDeX/AKeMeX.h"

void ord (signed* a, signed* b)
{
  if (*a > *b)
  { *a ^= *b; *b ^= *a; *a ^= *b; }
}

void ord (unsigned* a, unsigned* b)
{
  if (*a > *b)
  { *a ^= *b; *b ^= *a; *a ^= *b; }
}

void ord (signed long* a, signed long* b)
{
  if (*a > *b)
  { *a ^= *b; *b ^= *a; *a ^= *b; }
}

void ord (unsigned long* a, unsigned long* b)
{
  if (*a > *b)
  { *a ^= *b; *b ^= *a; *a ^= *b; }
}

void ord (long long* a, long long* b)
{
  if (*a > *b)
  { *a ^= *b; *b ^= *a; *a ^= *b; }
}

void ord (float* a, float* b)
{
  if (*a > *b)
  { *a ^= *b; *b ^= *a; *a ^= *b; }
}

void ord (double* a, double* b)
{
  if (*a > *b)
  { *a ^= *b; *b ^= *a; *a ^= *b; }
}


