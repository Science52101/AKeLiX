from akemax_py.akecax_py import *
from akemax_py.akelialx_py import *
import math

# Your global definitions go here.

def main() -> None:
  f = math.sin
  coef = approx_coef(f)
  print(coef)

  x = float(input())
  print(f(x))
  print(approx_f(f)(x))
  print(approx_f(f)(x) - f(x))

if __name__ == '__main__':
  main()
