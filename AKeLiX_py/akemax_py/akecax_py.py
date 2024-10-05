"""
Akai Keisanki Calculus eXperiments (for python)
"""

from math import factorial as _factorial

_n0: float = 1e-5
"""
A value very close to 0.

Notes
-----
The value of `_n0` (or :math:`n_0`) shall be represented by 1e-10 or

.. math:: n_0 = 1^{-10}

Which is very close or approaches 0.

.. math:: n_0 \\rightarrow 0

See Also
--------
lim : Calculate the tendency of a function around a point.
"""


def lim(x: float, f: callable) -> float:
  """
  Calculate the tendency of a function around a point.

  Parameters
  ----------
  x : float
    The `x` input to where the function tends to.
  f : function
    The function whose values tend to `f(x)`.

  Returns
  -------
  y : float
    The `y` output to where the function tends to.

  Raises
  ------
  UnrealNeighborhood
    Neighbor function output values are not real/calculable.

  Notes
  -----
  This function returns an approximate result and may have reduced functionality due to its limitations.

  The values presented shall be defined as:

  .. math:: \\lim_{n \\rightarrow x}{f(n)} = y

  Where the tendency [0]_ is calculated by the usage of a median [1]_:

  .. math::
    \\frac{f(x + h) + f(x - h)}{2}
    \\\\
    h \\rightarrow 0

  References
  ----------
  .. [0] A tendency is where some value approaches or is close to.
  .. [1] A median is the middle value of a finite ammount of numbers.

  See Also
  --------
  _n0 : A value very close to 0.

  Examples
  -------
  >>> lim(1, lambda x : (x*x-1)/(x-1))
  2.0
  """

  try:
    return (f(x + _n0) + f(x - _n0))/2
  except ZeroDivisionError:
    raise ZeroDivisionError('UnrealNeighborhood')


def _IRoC(f: callable, x: float) -> float:
  """
  Calculate the instantaneous rate of change of a function around a point.

  Parameters
  ----------
  f : function
    The function.
  x : float
    The `x` input.

  Returns
  -------
  r : float
    The instantaneous rate of change of `f` around x.

  Notes
  -----
  This function returns an approximate result and may have reduced functionality due to its limitations.

  The values presented shall be defined as:

  .. math:: \\frac{df}{dx}(x) = r

  Where the instantaneous rate of change is calculated by the usage of a limit:

  .. math:: \\lim_{h \\rightarrow 0}{\\frac{f(x + h) - f(x - h)}{2h}} = r

  See Also
  --------
  lim : Calculate the tendency of a function around a point.

  Examples
  -------
  >>> _IRoC(lambda x : 2*x*x*x, 3)
  54.000004467980034
  """

  return lim(0, lambda h : (f(x + h) - f(x - h))/(2 * h))


def derivative(f: callable) -> callable:
  """
  Get the derivative of a function.

  Parameters
  ----------
  f : function
    The function to be derivated.

  Returns
  -------
  g : function
    The derivative of `f`.

  Notes
  -----
  This function returns an approximate result and may have reduced functionality due to its limitations.

  The values presented shall be defined as:

  .. math:: f'(x) = \\frac{df}{dx}(x) = g(x)

  Where the instantaneous rate of change is calculated by the usage of a limit:

  .. math:: \\lim_{h \\rightarrow 0}{\\frac{f(x + h) - f(x - h)}{2h}} = g(x)

  See Also
  --------
  lim : Calculate the tendency of a function around a point.
  _IRoC : Calculate the instantaneous rate of change of a function around a point.

  Examples
  -------
  >>> derivative(lambda x : 2*x*x*x)(3)
  54.000004467980034
  = _IRoC(lambda x : 2*x*x*x, 3)
  """

  return lambda x : _IRoC(f, x)


def reg_lin(*data: list[tuple[float, float]]) -> tuple[float, float]:
  a: float = 0
  b: float = 0
  tmp: float = 0
  count: int = 0
  for i in range(len(data)):
    for j in range(i+1, len(data)):
      tmp = (data[j][1] - data[i][1]) / (data[j][0] - data[i][0])
      a += tmp
      b += (data[i][1] - tmp * data[i][0] + data[j][1] - tmp * data[j][0]) / 2
      count += 1
  a /= count
  b /= count
  return a, b


def approx_coef(f: callable, iterations: int = 4) -> tuple[float, ...]:
  coef: list[float] = []
  for i in range(iterations):
    coef.append(f(0) / _factorial(i))
    f = derivative(f)
  return tuple(coef)

def approx_f(f: callable, iterations: int = 4) -> callable:
  def f2(x: float) -> float:
    r: float = 0.0;
    coef = approx_coef(f, iterations)
    for i in range(iterations):
      r += coef[i]*x**i
    return r
  return f2
