#ifndef AKEALX_GRX
#define AKEALX_GRX

// Akai Keisanki Algorithm eXperiments - Algorithm eXperiments

#include <cstddef>
#include <utility>
#include <iterator>

namespace akelix
{

namespace alx
{
  #define for_range(i, b, e) for (auto i = b; i < e; i ++)
  #define count(i, n) for_range (i, 0, n)
  #define repeat(n) count (__alx_idx, n)

  template <class T>
  void minMax(T& x, T& y)
  {
    if (x <= y) return;

    x ^= y;
    y ^= x;
    x ^= y;

    return;
  }

  template <class T>
  void bubbleSort(T begin, T end)
  {
    const size_t n = std::distance(begin, end);

    T it;

    repeat (n - 1)
    {
      it = begin;
      repeat (n - 1)
        minMax(*it, *++it);
    }

    return;
  }

  template <class T>
  void sortedMerge (T begin, T middle, T end)
  {
    const size_t n = std::distance(begin, end);

    if (n <= 1) return;

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
    const size_t n = std::distance(begin, end);

    if (n <= 1) return;

    const size_t ln = n / 2;
    const size_t rn = n - ln;

    T middle = std::next(begin, ln);

    mergeSort(begin, middle);
    mergeSort(middle, end);

    sortedMerge(n, begin, middle, end);

    return;
  }

}

}

#endif
