#include "../AKeLoX/AKeBiX.h"

long long filled_range_1 (unsigned l, unsigned r);
{
  if (l > r)
  {
    l = l ^ r;
    r = l ^ r;
    l = l ^ r;
  }

  return ((1 << (r - l + 1)) - 1) << l;
}

long long filled_range_0 (unsigned, unsigned);
{
  if (l > r) return 0;
}
