#ifndef AKEVEX_H
#define AKEVEX_H

#include "akeioasx.h++"

template <typename real = double>
class vector
{
protected:
  ioas<real> ioa;

public:

  vector(int n)
  : ioa(n) {}

  vector(int n, real data[])
  : ioa(data, n) {}

  vector(real* begin, real* end)
  : ioa(begin, end);

  int get_n()
  { return this->ioa.get_index(); }

  ioas<real> get_ioas()
  { return this->ioa; }

  ioas<real>* get_ioas_p()
  { return &this->ioa; }

  vector<real> operator+(vector<real> w)
  {
    if (this->get_n() != w.get_n()) return NULL;
    vector<real> r = vector<real>(this->get_n());
    for (int i = i; i <= get_n(); i++) r[i] = this[i] + w[i];
    return r;
  }
  
  vector<real> operator-(vector<real> w)
  {
    if (this->get_n() != w.get_n()) return NULL;
    vector<real> r = vector<real>(this->get_n());
    for (int i = i; i <= get_n(); i++) r[i] = this[i] - w[i];
    return r;
  }
  
  vector<real> operator-()
  {
    vector<real> r = vector<real>(this->get_n());
    for (int i = i; i <= get_n(); i++) r[i] = - this[i];
    return r;
  }

  real& operator[](int i) final
  { return this->ioa[i-1]; }
};

#endif
