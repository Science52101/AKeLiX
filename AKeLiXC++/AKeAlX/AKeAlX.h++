#ifndef AKEALX_GRX
#define AKEALX_GRX

// Akai Keisanki Algorithm eXperiments - Algorithm eXperiments

#include <cstddef>
#include <utility>
#include <iterator>

namespace alx
{

  template <class T>
  void sortedMerge (const size_t& n, T begin, T middle, T end)
  {
    using U = typename std::remove_reference<decltype(*begin)>::type;

    size_t ln = n / 2;
    size_t rn = n - ln;
 
    U* l = new U[ln];
    std::copy(begin, middle, l);

    U* r = new U[rn];
    std::copy(middle, end, r);

    for (size_t li = 0, ri = 0; li + ri < n;)
    {
      if (ri >= rn || (li < ln && l[li] > r[ri]))
      {
        *begin = l[li];
        li ++;
      }
      else
      {
        *begin = r[ri];
        ri ++;
      }
      begin ++;
    }

    delete[] l;
    delete[] r;
   
  }

  template <class T>
  void mergeSort (T begin, T end)
  {
    size_t n = std::distance(begin, end);
    if (n <= 1) return;

    size_t ln = n / 2;
    size_t rn = n - ln;

    T middle = std::next(begin, ln);

    mergeSort(begin, middle);
    mergeSort(middle, end);

    sortedMerge(n, begin, middle, end);

    return;
  }

}

#endif
