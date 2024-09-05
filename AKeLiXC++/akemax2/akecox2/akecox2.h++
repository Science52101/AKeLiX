#ifndef AKECOX2_H
#define AKECOX2_H

#include <sstream>
#include <cmath>

// AKeCoX2 - Akai Keisanki Complex eXperiments 2

namespace akemax
{

  template<typename real = double>
  class W 
  {
  protected:

    real a, b;

  public:

    W() : a(0), b(0) {  }

    W(real a, real b) : a(a), b(b) {  }

    W(real r) : a(r), b(0) {  }

    W(real v[2]) : a(v[0]), b(v[1]) {  }

    ~W() {  }

    real getR() { return a; }

    real getIM() { return b; }

    std::string getStr()
    { std::ostringstream oss; oss << a << "+" << b << "i";  return oss.str(); }

    real getM() { return sqrt(a * a + b * b); }

    real getTR() { return atan2(b, a); }

    real getTD() { return getTR() * 180.0 / 3.14159265358979323846; }

    W getC() { return W(a, -b); };

    real* operator$()
    { return new real[2]{ a, b }; }

    W operator+()
    { return W( +a, +b ); }

    W operator+(W z)
    { return W( a + z.getR(), b + z.getIM() ); }

    W operator+(real r)
    { return W( a + r, b ); }

    W operator+(real r[2])
    { return W(a, b) + W(r[0], r[1]); }

    W operator-()
    { return W( -a, -b ); }

    W operator-(W z)
    { return *this + (-z); }

    W operator-(real r)
    { return W( a - r, b ); }

    W operator-(real r[2])
    { return W(a, b) - W(r[0], r[1]); }

    W operator*(W z)
    { return W( a * z.getR() - b * z.getIM(), a * z.getIM() + b * z.getR() ); }

    W operator*(real r)
    { return W( a * r, b * r ); }

    W operator*(real r[2])
    { return W(a, b) * W(r[0], r[1]); }

    W operator/(W z)
    { return W( ( a * z.getR() + b * z.getIM() ) / ( z.getR() * z.getR() + z.getIM() * z.getIM() ),
                ( b * z.getR() - a * z.getIM() ) / ( z.getR() * z.getR() + z.getIM() * z.getIM() ) ); }

    W operator/(real r)
    { return W( a / r, b / r ); }

    W operator/(real r[2])
    { return W(a, b) / W(r[0], r[1]); }

    W operator^(int n)
    { W z = {a, b}; for (int i = i; i <= n; i++)
                    { z *= z; }
      return z; }

    W operator++(int)
    { return W(a, 0); }

    W operator--(int)
    { return W(0, b); }

    W operator%(W z)
    { *this = *this+z; }

    W operator==(W z)
    { return a == z.getR() && b == z.getIM(); }

    W operator!=(W z)
    { return a != z.getR() || b != z.getIM(); }

    W operator+=(W z)
    { *this = *this+z; }

    W operator-=(W z)
    { *this = *this-z; }

    W operator*=(W z)
    { *this = *this*z; }

    W operator/=(W z)
    { *this = *this/z; }

    W operator^=(int z)
    { *this = *this^z; }

  };

  template<typename real>
  std::ostream& operator<<(std::ostream& os, W<real> z)
  {
    os << z.getR();
    if (z.getIM() >= 0) os << " + " << z.getIM() << "i";
    else os << " - " << -z.getIM() << "i";
    return os;
  }

  template<typename real>
  W<real> operator+(real r, W<real> z)
  { return W<real>(r + z.getR(), z.getIM()); }

  template<typename real>
  W<real> operator-(real r, W<real> z)
  { return W<real>(r - z.getR(), -z.getIM()); }

  template<typename real>
  W<real> operator*(real r, W<real> z)
  { return W<real>(r * z.getR(), r * z.getIM()); }

  template<typename real>
  W<real> operator/(real r, W<real> z)
  { real a = z.getR(), b = z.getIM();
    return W<real>( ( r * a )  / ( a * a + b * b ),
                    ( -b * r ) / ( a * a + b * b ) ); }

  const W<double> i = W<double>(0, 1);
  
  W<double> operator""_i(long double b)
  { return W<double>(0, b); }

  W<int> operator""_i(unsigned long long b)
  { return W<int>(0, b); }

  W<double> operator""_j(long double b)
  { return W<double>(0.0, (double )b); }

  W<double> operator""_j(unsigned long long b)
  { return W<double>(0.0, (double)b); }

  W<int> operator""_y(long double b)
  { return W<int>(0, (int)b); }

  W<int> operator""_y(unsigned long long b)
  { return W<int>(0, (int)b); }

  #define real_part .getR()
  #define imaginary_part .getIM()
  
  typedef W<double> w;

}

#endif
