#ifndef AKENUSYX_H
#define AKENUSYX_H

#include "../akecox2/akecox2.h++"

namespace akemax
{

class N
{
private:
  // ...
protected:
  int value;
public:
  N(int value) : value(value) {}

  int getIntV()
  { return value; }

  N operator + ()
  { return N( + value ); }
  N operator + (N n)
  { return N( value + n.getIntV() ); }

  N operator - (N n)
  { if (value - n.getIntV() >= 0) return N( value + - n.getIntV() ); }

  N operator * (N n)
  { return N( value * n.getIntV() ); }
  N operator / (N n)
  { return N( value / n.getIntV() ); }

  N operator ^ (N n)
  { int r = 1; for ( int i = 0; i < n.getIntV(); i++ ) r *= n.getIntV();
    return N( r ); }
  N operator % (N n)
  { return N( value % n.getIntV() ); }

  bool operator > (N n)
  { return value > n.getIntV(); }
  bool operator < (N n)
  { return value < n.getIntV(); }

  bool operator >= (N n)
  { return value >= n.getIntV(); }
  bool operator <= (N n)
  { return value <= n.getIntV(); }

  bool operator == (N n)
  { return value == n.getIntV(); }
  bool operator != (N n)
  { return value != n.getIntV(); }

  bool operator += (N n)
  { *this = *this + n;
    return *this == n; }
  bool operator -= (N n)
  { if (value - n.getIntV() >= 0) *this = *this - n; 
    return *this == n; }

  bool operator *= (N n)
  { *this = *this * n; 
    return *this == n; }
  bool operator /= (N n)
  { *this = *this / n; 
    return *this == n; }

  bool operator ^= (N n)
  { *this = *this ^ n; 
    return *this == n; }
  bool operator %= (N n)
  { *this = *this % n; 
    return *this == n; }
};

N operator""_n(unsigned long long val)
{ return N(val); }

class Z : public N
{
private:
  // ...
protected:
  // ...
public:
  Z(int value) : N(value) {}

  Z operator + ()
  { return Z( + value ); }
  Z operator + (Z n)
  { return Z( value + n.getIntV() ); }

  Z operator - ()
  { return Z( - value ); }
  Z operator - (Z n)
  { return Z( value + - n.getIntV() ); }

  Z operator * (Z n)
  { return Z( value * n.getIntV() ); }
  Z operator / (Z n)
  { return Z( value / n.getIntV() ); }

  Z operator ^ (Z n)
  { int r = 1; for ( int i = 0; i < n.getIntV(); i++ ) r *= n.getIntV();
    return Z( r ); }
  Z operator % (Z n)
  { return Z( value % n.getIntV() ); }

  bool operator > (Z n)
  { return value > n.getIntV(); }
  bool operator < (Z n)
  { return value < n.getIntV(); }

  bool operator >= (Z n)
  { return value >= n.getIntV(); }
  bool operator <= (Z n)
  { return value <= n.getIntV(); }

  bool operator == (Z n)
  { return value == n.getIntV(); }
  bool operator != (Z n)
  { return value != n.getIntV(); }

  bool operator += (Z n)
  { *this = *this + n;
    return *this == n; }
  bool operator -= (Z n)
  { *this = *this - n;
    return *this == n; }

  bool operator *= (Z n)
  { *this = *this * n; 
    return *this == n; }
  bool operator /= (Z n)
  { *this = *this / n; 
    return *this == n; }

  bool operator ^= (Z n)
  { *this = *this ^ n; 
    return *this == n; }
  bool operator %= (Z n)
  { *this = *this % n; 
    return *this == n; }
};

Z operator""_z(unsigned long long val)
{ return Z(val); }

}

#endif
