#include "../AKeLoX/AKeBiX.h"

#include <stdint.h>
#include <string.h>

struct bs
{
  addr begin;
  addr end;
}


bytes mkBytes(size s)
{
  bytes bss = (bytes) malloc(sizeof(bs));

  bss.begin = (addr) malloc(sizeof(byte) * s);
  bss.end = bss.begin + s;

  return b;
}

bytes cpBytes(bytes* bss)
{
  bytes bs2 = (bytes) malloc(sizeof(bs));
  size s = bss->end - bss->begin;

  bs2.begin = (addr) malloc(sizeof(byte) * s);
  bs2.end = bs2.begin + s;

  memcpy(bs2, bss, s);

  return bs2;
}


byte gtByte (bytes bss, size s)
{
  if (s + 1 >= bss.end - bss.begin) return 0;
  return *(bss.begin + s);
}

bit gtBit (bytes bss, size s)
{
  if (s / 8 + 1 >= bss.end - bss.begin) return 0;
  return (gtByte(bss, s / 8) << (s % 8)) & 1;
}

word gtWord (bytes bss, size s)
{
  if ((s + 1) * 2 >= bss.end - bss.begin) return 0;
  return *(bss.begin + 2 * s);
}

dword gtDWord (bytes bss, size s)
{
  if ((s + 1) * 4 >= bss.end - bss.begin) return 0;
  return *(bss.begin + 4 * s);
}


bytes stByte (bytes bss, size s, byte B)
{
  if (s + 1 >= bss.end - bss.begin) return NULL;
  *(bss.begin + s) = B;
  return bss;
}

bytes stBit (bytes bss, size s)
{
  if (s / 8 + 1 >= bss.end - bss.begin) return NULL;
  *(bss.begin + s / 8) &= ~ (b << (s % 8));
  *(bss.begin + s / 8) |= (b << (s % 8));
  return bss;
}

bytes stWord (bytes bss, size s)
{
  if ((s + 1) * 2 >= bss.end - bss.begin) return NULL;
  return *(bss.begin + 2 * s);
}

bytes stDWord (bytes bss, size s)
{
  if ((s + 1) * 4 >= bss.end - bss.begin) return NULL;
  return *(bss.begin + 4 * s);
}


bytes shl (bytes bss, size s)
{
  bit c = 0;

  for (addr b = bss.begin; b < bss.end; b ++)
  {
    c = ;
    *b = *b << 1;
  }

  return bss;
}

bytes shr (bytes bss, size s)
{
  return bss;
}


// ...