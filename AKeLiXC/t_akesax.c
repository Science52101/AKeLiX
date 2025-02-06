#include <stdio.h>

#include "AKeDeX/AKeSaX.h"

signed main()
{
  int x = 3;

  Secure s = s_wrap(&x);

  if (s_check(s))
    printf("%d", *s_uwrap(s));
  else
    printf("No value");

  return 0;
}
