"""
Akai Keisanki Linear Algebra eXperiments (for python)
"""
import numbers


class vct(object):
  """
  vct(*args) -> vct

  vct(l: list[numbers.Complex]) -> vct

  A vector, representation of an n-dimensional arrow/force or a list of n values.

  Attributes
  ----------
  _data : list of numbers.Complex
    The content of the vector.
  _n : int
    The number of elements in the vector.

  Methods
  -------
  __init__(*args) -> None
    Class constructor for the vtc class.
  __getitem__(index: int) -> object
    [] operator for getting an indexed value from `_data` equivalent to `_data[index-1]`.
  __add__(w: vct) -> vct
    + operator for summing two vectors, adding the i-th element of the 1st to the i-th element of the 2nd.
  __sub__(w: vct) -> vct
    - operator for subtracting two vectors, subtracting the i-th element of the 1st to the i-th element of the 2nd.
  __eq__(w: vct) -> bool:
    == operator for comparing two vectors, comparing the i-th element of the 1st to the i-th element of the 2nd.
  """

  _data: list[numbers.Complex]
  _n: int

  def __init__(self, *args) -> None:
    """
    Class constructor for the vtc class.

    Parameters
    ---------
    *args
      The arguments for the constructor.

    Returns
    -------
    self
      The constructed class.

    Notes
    -----
    When using the constructor:

    - `vct(<list>)` may be used for creating a vector from a list.

    - `vct(<n, m, ...>)` may be used for creating a vector from a given amount of values.
    """

    if isinstance(args[0], list):
      self._data = args[0]
    else:
      self._data = list(args)
    self._n = len(self._data)

  def __getitem__(self, index: int) -> numbers.Complex:
    """
    [] operator for getting an indexed value from `_data` equivalent to `_data[index-1]`.

    Parameters
    ----------
    index : int
      The index of the value to be returned.

    Returns
    -------
    numbers.Complex
      The index-th value of the vector.

    Examples
    --------
    >>> vct(41, 26, 53, 61, 42, 59).__getitem__(3)
    53
    >>> vct(41, 26, 53, 61, 42, 59)[3]
    53

    Raises
    ------
    UnequalDimensions
      The index is out of the vector's dimensions.
    """

    if index > abs(self._n):
      raise ArithmeticError('UnequalDimensions')
    return self._data[index-1] if index >= 0 else self._data[index]

  def __add__(self, w: 'vct') -> 'vct':
    """
    + operator for summing two vectors, adding the i-th element of the 1st to the i-th element of the 2nd.

    Parameters
    ----------
    w : vct
      The 2nd vector

    Returns
    -------
    vct
      The resulting vector from the sum of the 1st and 2nd vectors given.

    Examples
    --------
    >>> vct(5, 2, 3).__add__(vct(4, 8, 2))
    vct(9, 10, 5)

    >>> vct(5, 2, 3) + vct(4, 8, 2)
    vct(9, 10, 5)

    Raises
    ------
    UnequalDimensions
      The 1st and 2nd vectors' dimensions are unequal.
    """

    if self._n != w._n:
      raise ArithmeticError('UnequalDimensions')
    return vct([self._data[i] + w._data[i] for i in range(self._n)])

  def __sub__(self, w: 'vct') -> 'vct':
    """
    - operator for subtracting two vectors, subtracting the i-th element of the 1st to the i-th element of the 2nd.

    Parameters
    ----------
    w : vct
      The 2nd vector

    Returns
    -------
    vct
      The resulting vector from the subtraction of the 1st and 2nd vectors given.

    Examples
    --------
    >>> vct(5, 2, 3).__sub__(vct(4, 8, 2))
    vct(1, -6, 1)

    >>> vct(5, 2, 3) - vct(4, 8, 2)
    vct(1, -6, 1)

    Raises
    ------
    UnequalDimensions
      The 1st and 2nd vectors' dimensions are unequal.
    """

    if self._n != w._n:
      raise ArithmeticError('UnequalDimensions')
    return vct([self._data[i] - w._data[i] for i in range(self._n)])

  def __eq__(self, w: 'vct') -> bool:
    """
    == operator for comparing two vectors, comparing the i-th element of the 1st to the i-th element of the 2nd.

    Parameters
    ----------
    w : vct
      The 2nd vector

    Returns
    -------
    bool
      If the 1st and 2nd vectors are equal.

    Examples
    --------
    >>> vct(5, 2, 3).__eq__(vct(4, 8, 2))
    False

    >>> vct(5, 2, 3) == vct(4, 8, 2)
    False

    >>> vct(5, 2, 3).__eq__(vct(5, 2, 3))
    True

    >>> vct(5, 2, 3) == vct(5, 2, 3)
    True

    Raises
    ------
    UnequalDimensions
      The 1st and 2nd vectors' dimensions are unequal.
    """

    if self._n != w._n:
      raise ArithmeticError('UnequalDimensions')
    for i in range(self._n):
      if w._data[i] != self._data[i]: return False
    return True
