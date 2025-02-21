#ifndef AKEDEX_SAX
#define AKEDEX_SAX

// Akai Keisanki Definition eXperiments - Prettifying eXperiments

#include <iostream>

namespace akelix
{

namespace prx
{

  namespace io
  {

    const char* oSeparator = "\t";

    template <class ... T>
    void out (const T& ... x)
    {
      ((std::cout << x << oSeparator), ...);
    }

    template <class ... T>
    void outln (const T& ... x)
    {
      ((std::cout << x << oSeparator), ...);
      std::cout << '\n';
    }


    template <class ... T>
    void err (const T& ... x)
    {
      ((std::cerr << x << oSeparator), ...);
    }

    template <class ... T>
    void errln (const T& ... x)
    {
      ((std::cerr << x << oSeparator), ...);
      std::cerr << '\n';
    }


    template <class ... T>
    void in (T& ... x)
    {
      ((std::cin >> x), ...);
    }

  }

  namespace io2
  {
    void wait (size_t time = 1000)
    {
      time *= 10000;
      size_t cnt = 0;
      for (; cnt < time ; cnt ++) std::cout.flush();
    }

    void write (const char* str, size_t time = 500)
    {
      for (const char* c = str; *c != '\0'; c ++)
      {
        std::cout << *c;
        wait(time);
      }
    }
  }

}

}

#endif
