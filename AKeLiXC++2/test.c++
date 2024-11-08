#include <iostream>

#include "akedex/aketyx.h++"

signed main()
{
  erx::Secure<int> s(256);

  tyx::SecPtr<int> p = tyx::some(s);

  std::cout << *p << '\n'; // 256

  tyx::SecPtr<int> p2 = tyx::some<int>(128);

  std::cout << *p2 << '\n'; // 128

  return 0;
}


