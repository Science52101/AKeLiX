#include <iostream>

#include "akemax/akevex.h++"

signed main()
{
  signed a[2][2]; vex::fromStream(std::cin, a);
  signed b[1][2]; vex::fromStream(std::cin, b);

  signed c[1][2];

  vex::matMul(c, a, b); // c = ab = {{7, 4}}

  vex::toStream(std::cout, c);

  return 0;
}
