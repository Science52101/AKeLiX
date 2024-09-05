#ifndef AKEVEX_P1_H
#define AKEVEX_P1_H

#include <iostream>
#include <math.h>
#include <cstdarg>

// Akai Keisanki Vector eXperiments - Part 1

struct vct
{
private:

  int v_n;
  float* v_arr;

public:

  vct(int n) : v_n(n)
  {
    v_arr = (float*) malloc(sizeof(float)*n);
    for (int i = 0; i< v_n; i++) { *(v_arr+i) = 0; }
  }

  vct(int n, float el, ...) : v_n(n)
  {
    v_arr = (float*) malloc(sizeof(float)*n);
    va_list args;
    va_start(args, el);
    for ( int i = 0; i < n; i++ )
    {
      float value = ( i == 0 ) ? el : (float) va_arg(args, double);
      *(v_arr+i) = value;
    }
    va_end(args);
  }

  vct(int n, float (*f)(int)) : v_n(n)
  {
    v_arr = (float*) malloc(sizeof(float)*n);
    for (int i = 0; i< v_n; i++) { *(v_arr+i) = f(i); }
  }

  vct(int n, float array[]) : v_n(n), v_arr(array) {  }

  vct(float i, float j)
  {
    v_arr = (float*) malloc(sizeof(float)*2);
    *(v_arr+0) = i;
    *(v_arr+1) = j;
  }

  ~vct()
  { free(v_arr); }

  float* getArr()
  { return v_arr; }

  int getDim()
  { return v_n; }

  double getM()
  {
    int s; for (int i = 0; i < v_n; i++) { s += *(v_arr+i); }
    return pow(s,1.0/v_n);
  }

  std::string getStr()
  {
    std::ostringstream oss; 
    for (int i = 0; i < v_n; i++)
    { oss << ( ( i != 0 ) ? " " : "" ) << *(v_arr+i); }
    return oss.str();
  }

  vct operator+(vct vct2)
  {
    float* n_arr = (float*) malloc(sizeof(float)*v_n); float* v_arr2 = vct2.getArr();
    for (int i = 0; i < v_n; i++) { *(n_arr+i) = *(v_arr+i) + *(v_arr2+i); }
    return vct(v_n, n_arr);
  }

  float* operator&()
  { return v_arr; }

  float operator+(int i)
  { return *(v_arr+i); }

};

struct mtx
{
private:

  int m_n;
  int m_m;
  vct* m_arr;

public:

  mtx(int n, int m) : m_n(n), m_m(m)
  {
    m_arr = (vct*) malloc(sizeof(vct)*m);
    for (int i = 0; i< m_m; i++) { *(m_arr+i) = vct(n); }
  }

  mtx(int n, int m, vct* array) : m_n(n), m_m(m), m_arr(array) {  }

  mtx(int n, int m, float (*f)(int, int)) : m_n(n), m_m(m)
  {
    m_arr = (vct*) malloc(sizeof(vct)*m);
    float* v_arr = (float*) malloc(sizeof(float)*n);
    for (int i = 0; i < m; i++) { for (int j = 0; j < n; j++ )
    { *(v_arr+j) = f(n, m); } *(m_arr+i) = vct(n, v_arr); }
    free(v_arr);
  }

  ~mtx()
  { free(m_arr); }

  vct* getArr()
  { return m_arr; }

  int* getDim()
  { int r[] = { m_n, m_m }; return r; }

  std::string getStr()
  {
    std::string s = "";
    for (int i = 0; i < m_m; i++)
    { s += ( ( i != 0 ) ? "\n" : "" ) + (*(m_arr+i)).getStr(); }
    return s;
  }

  mtx operator+(mtx mtx2)
  {
    vct* n_arr = (vct*) malloc(sizeof(vct)*m_n); vct* m_arr2 = mtx2.getArr();
    for (int i = 0; i < m_n; i++)
    { *(n_arr+i) = *(m_arr+i) + *(m_arr2+i); }
    return mtx(m_n, m_m, n_arr);
  }

  vct* operator&()
  { return m_arr; }

  vct operator+(int i)
  { return *(m_arr+i); }
};

#endif
