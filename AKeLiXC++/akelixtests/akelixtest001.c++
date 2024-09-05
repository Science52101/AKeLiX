// g++ ./akelixtests/akelixtest001.c++ -o akelixtest001 -I .
// ./akelixtest001

#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

#include <akepox/akeioasx.h++>
#include <akemax2/akemax2.h++>

using namespace std;
using namespace akemax;
using namespace akepox;

int main()
{
  ioas<double> a = ioas<double>::get();
  ioas<double> b = ioas<double>::get();

  a << 2598 << 5027 << 5397 << 3507 << 42607 << 248;
  b << 4358 << 2780 << 298 << 570;

  cout << a << endl;
  cout << a.size() << endl;

  cout << b << endl;
  cout << b.size() << endl;

  cout << endl;

  cout << (a+b) << endl;
  cout << (a+b).size() << endl;
  
  cout << (a-b) << endl;
  cout << (a-b).size() << endl;

  cout << (b-a) << endl;
  cout << (b-a).size() << endl;

  return 0;
}
