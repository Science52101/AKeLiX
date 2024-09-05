#ifndef AKECOX_H
#define AKECOX_H

#include <sstream>
#include <cmath>

// Akai Keisanki Complex eXperiments

/*

--------------------------------W--------------------------------

W = a + bi

double W.a                      | double W.b

W(double a, double b) -> W a + bi
W(double r) -> W r + 0i
W(double v[2]) -> W v[0] + v[1]i

W.getR() -> double a
W.getIM() -> double b
W.getStr() -> string "<a>+<b>i"
W.getM() -> double |z|
W.getTR() -> double (Radians) θ
W.getTD() -> double (Degrees) θ
W.getC() -> W a - bi

double = W -> double            | W + W -> W
W + double -> W                 | W + double[2] -> W
W - W -> W                      | W - double -> W
W - double[2] -> W              | W * W -> W
W * double -> W                 | W * double[2] -> W
W / W -> W                      | W / double -> W
W / double[2] -> W              | W ^ W -> W

-----------------------------Methods-----------------------------

i(double b) -> W 0 + bi

*/

// -------------------- COMPLEX NUMBER STRUCTURE --------------------
struct W // Complex number
{
  // -------------------- PRIVATE --------------------
private:

  // -------------------- ATRIBUTES --------------------

  double a; double b; // z = a + bi

  // -------------------- PUBLIC --------------------
public:

  // -------------------- CONSTRUCTOR --------------------

  // Constructor 0
  // W(b) -> W 0 + 0i
  W() : a(0), b(0){  }

  // Constructor 1
  // W(double a, double b) -> W a + bi
  W(double a, double b) : a(a), b(b){  }

  // Constructor 2
  // W(double r) -> W r + 0i
  W(double r) : a(r), b(0) {  }

  // Constructor 3
  // W(double v[2]) -> W v[0] + v[1]i
  W(double v[2]) : a(v[0]), b(v[1]) {  }

  // Destructor 3
  // W() ->
  ~W() {  }

  // -------------------- INFORMATION RETURNING --------------------

  // Get Real
  // getR() -> double a
  // ( z = a + bi )
  double getR() { return a; }

  // Get Imaginary Multiplier
  // getIM() -> double b
  // ( z = a + bi )
  double getIM() {return b; }

  // -------------------- OTHER INFORMATION RETURNING --------------------

  // Get String
  // getStr() -> string "<a>+<b>i"
  // ( z = a + bi )
  std::string getStr()
  { std::ostringstream oss; oss << a << "+" << b << "i";  return oss.str(); }

  // Get Modulus / Magnitude
  // getM() -> double |z|
  // ( z = a + bi )
  double getM() { return sqrt(a * a + b * b); }

  // Get Theta / Argument (Radians)
  // getTR() -> double (Radians) θ
  // ( θ = arctan(b, a), z = a + bi = |z| ( cos(θ) + sin(θ) i ), a = |z| cos(θ), b = |z| sin(θ) )
  double getTR() { return atan2(b, a); }

  // Get Theta / Argument (Degrees)
  // getTD() -> double (Degrees) θ
  // ( θ = arctan(b, a), z = a + bi = |z| ( cos(θ) + sin(θ) i ), a = |z| cos(θ), b = |z| sin(θ) )
  double getTD() { return getTR() * 180.0 / 3.14159265358979323846; }

  // Get Conjulgate
  // getC() -> W a - bi
  // ( | a + bi | = | a - bi |, a + bi =  a + b(i) -> a + b(-i) = a - bi )
  W getC() { return W(a, -b); };

  // -------------------- OPERATORS --------------------

  // double = W -> double
  double* operator=(W z)
  { double r[2] = { z.getR(), z.getIM() }; return r; }

  // W + W -> W
  W operator+(W z)
  { return W( a + z.getR(), b + z.getIM() ); }

  // W + double -> W
  W operator+(double r)
  { return W( a + r, b ); }

  // W + double[2] -> W
  W operator+(double r[2])
  { return W(a, b) + W(r[0], r[1]); }

  // W - W -> W
  W operator-(W z)
  { return W( a - z.getR(), b - z.getIM() ); }

  // W - double -> W
  W operator-(double r)
  { return W( a - r, b ); }

  // W - double[2] -> W
  W operator-(double r[2])
  { return W(a, b) - W(r[0], r[1]); }

  // W * W -> W
  W operator*(W z)
  { return W( a * z.getR() - b * z.getIM(), a * z.getIM() + b * z.getR() ); }

  // W * double -> W
  W operator*(double r)
  { return W( a * r, b * r ); }

  // W * double[2] -> W
  W operator*(double r[2])
  { return W(a, b) * W(r[0], r[1]); }

  // W / W -> W
  W operator/(W z)
  { return W( ( a * z.getR() + b * z.getIM() ) / ( z.getR() * z.getR() + z.getIM() * z.getIM() ),
              ( b * z.getR() - a * z.getIM() ) / ( z.getR() * z.getR() + z.getIM() * z.getIM() ) ); }

  // W / double -> W
  W operator/(double r)
  { return W( a / r, b / r ); }

  // W / double[2] -> W
  W operator/(double r[2])
  { return W(a, b) / W(r[0], r[1]); }

  // W ^ W -> W
  W operator^(int n)
  { W z = {a, b}; for (int i = i; i <= n; i++)
                  { z = { z.getR() * z.getR() - z.getIM() * z.getIM(), z.getR() * z.getIM() * 2 }; }
    return z; }
};

// -------------------- COMPLEX NUMBER PROCESSING FUNCTIONS --------------------

// Multiply by i
// i(double b) -> W 0 + bi
// OTHER USAGES: " z = (W) a + i(b) " -> z = a + bi
W i(double b)
{ return W(0, b); }


#endif
