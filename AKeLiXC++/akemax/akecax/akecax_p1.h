#ifndef AKECAX_P1_H
#define AKECAX_P1_H

#include <iostream>
#include <cmath>

// Akai Keisanki Calculus eXperiments - Part 1

// Get Instantaneous Rate of Change by Forward Difference
double getIRoC_bFD(double (*f)(double), double x, bool printprogress=false, double precision = 1e-12, double mindx = 1e-15)
{
  double dx = 1, piroc = (f(x+dx)-f(x))/dx, iroc = 0;
  while(dx > mindx)
  {
    dx /= 10;
    iroc = (f(x+dx)-f(x))/dx;
    if (printprogress) { std::cout << iroc << " "; }
    if ( std::abs(piroc - iroc) < precision) { break; }
    piroc = iroc;
  }
  return iroc;
}

// Get Instantaneous Rate of Change by Backward Difference
double getIRoC_bBD(double (*f)(double), double x, bool printprogress=false, double precision = 1e-12, double mindx = 1e-15)
{
  double dx = 1, piroc = (f(x)-f(x-dx))/dx, iroc = 0;
  while(dx > mindx)
  {
    dx /= 10;
    iroc = (f(x)-f(x-dx))/dx;
    if (printprogress) { std::cout << iroc << " "; }
    if ( std::abs(piroc - iroc) < precision) { break; }
    piroc = iroc;
  }
  return iroc;
}

// Get Instantaneous Rate of Change by Central Difference
double getIRoC_bCD(double (*f)(double), double x, bool printprogress=false, double precision = 1e-12, double mindx = 1e-15)
{
  double dx = 1, piroc = (f(x + dx) - f(x - dx)) / (2 * dx), iroc = 0;
  while(dx > mindx)
  {
    dx /= 10;
    iroc = (f(x + dx) - f(x - dx)) / (2 * dx);
    if (printprogress) { std::cout << iroc << " "; }
    if ( std::abs(piroc - iroc) < precision) { break; }
    piroc = iroc;
  }
  return iroc;
}

// Get Instantaneous Rate of Change (Auto)
double getIRoC(double (*f)(double), double x, bool printprogress=false, double precision = 1e-12, double mindx = 1e-15)
{
  try
  { return getIRoC_bCD(f, x, printprogress, precision); }
  catch (...)
  { try
    { return getIRoC_bFD(f, x, printprogress, precision); }
    catch (...)
    { return getIRoC_bBD(f, x, printprogress, precision); } }
}

// Get Area Under the Graph
double getAUtG(double (*f)(double), double a, double b, bool printprogress=false, double dx = 1e-6)
{
  double autg = 0;
  for (double x = a; x < b; x += dx)
  {
    if (printprogress) { std::cout << autg << " "; }
    autg += f(x) * dx;
  }
  return autg;
}

// Get Limit (Correction by Medium)
double getLim_CM(double (*f)(double), double x, bool from, double precision = 1e-12, double mindx = 1e-15, double max = 1e+200, double min = 1e-100, bool printprogress=false)
{
  double dx = 1, pm = (from)?1:-1, plim = f(x+dx), lim = 0;
  while(dx > mindx)
  {
    dx /= 10;
    lim = f(x+pm*dx) - pm*( f(x+dx) - f(x-dx) ) / 2;
    if (printprogress) { std::cout << lim << " "; }
    if ( std::abs(plim - lim) < precision) { break; }
    if ( std::abs(lim) > max ) { lim = INFINITY; break;}
    if ( std::abs(lim) < min ) { lim = 0; break;}
    plim = lim;
  }
  return lim;
}

// Get Limit (by Medium)
double getLim_bM(double (*f)(double), double x, double precision = 1e-12, double mindx = 1e-15, double max = 1e+200, double min = 1e-100, bool printprogress=false)
{
  double dx = 1, plim = f(x+dx), lim = 0;
  while(dx > mindx)
  {
    dx /= 10;
    lim = ( f(x+dx) + f(x-dx) ) / 2;
    if (printprogress) { std::cout << lim << " "; }
    if ( std::abs(plim - lim) < precision) { break; }
    if ( std::abs(lim) > max ) { lim = INFINITY; break;}
    if ( std::abs(lim) < min ) { lim = 0; break;}
    plim = lim;
  }
  return lim;
}

// Get Limit (Correction by Spacing)
double getLim_CS(double (*f)(double), double x, bool from, double precision = 1e-12, double mindx = 1e-15, double max = 1e+200, double min = 1e-100, bool printprogress=false)
{
  double dx = 1, pm = (from)?1:-1, plim = f(x+dx), lim = 0;
  while(dx > mindx)
  {
    dx /= 10;
    lim = f(x+pm*dx) - pm*( f(x+2*pm*dx) - f(x+pm*dx) );
    if (printprogress) { std::cout << lim << " "; }
    if ( std::abs(plim - lim) < precision) { break; }
    if ( std::abs(lim) > max ) { lim = INFINITY; break;}
    if ( std::abs(lim) < min ) { lim = 0; break;}
    plim = lim;
  }
  return lim;
}

// Get Limit (Correction by IRoC)
double getLim_CIRoC(double (*f)(double), double x, bool from, double precision = 1e-12, double mindx = 1e-15, double max = 1e+200, double min = 1e-100, bool printprogress=false)
{
  double dx = 1, pm = (from)?1:-1, plim = f(x+dx), lim = 0;
  while(dx > mindx)
  {
    dx /= 10;
    lim = f(x+pm*dx) - pm*dx*getIRoC(f, x+pm*dx);
    if (printprogress) { std::cout << lim << " "; }
    if ( std::abs(plim - lim) < precision) { break; }
    if ( std::abs(lim) > max ) { lim = INFINITY; break;}
    if ( std::abs(lim) < min ) { lim = 0; break;}
    plim = lim;
  }
  return lim;
}

// Get Limit (Auto)
double getLim(double (*f)(double), double x, bool from, double precision = 1e-12, double mindx = 1e-15, double max = 1e+200, double min = 1e-100, bool printprogress=false)
{
  try
  {
    return getLim_CM(f, x, from, precision, mindx, max, min, printprogress);
  } catch (...)
  { try
    {
      return getLim_bM(f, x, precision, mindx, max, min, printprogress);
    } catch (...)
    {
      try
      {
        return getLim_CS(f, x, from, precision, mindx, max, min, printprogress);
      } catch(...)
      {
        return getLim_CIRoC(f, x, from, precision, mindx, max, min, printprogress);
      }
    }
  }
}

#endif
