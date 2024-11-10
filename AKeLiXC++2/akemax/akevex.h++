#ifndef AKEMAX_VEX
#define AKEMAX_VEX

#define relforif(start, cond, loop, c2, el, rel) for (start, cond, loop) if (c2) el = rel

namespace vex
{
  /* AKeMaX - VeX -- Akai Keisanki Mathematic eXperiments - Vector eXperiments */

  template <class T, unsigned long N, unsigned long M>
  using vex = T[N][M];

  template <class T, unsigned long N, unsigned long M, unsigned long L>
  void matMul(T (&r)[M][N], const T (&a)[L][N], const T (&b)[M][L])
  {
    /*
    Basic matrix multiplication.

    Parameters
    ----------
    r : T (&)[M][N]
      Reference to resulting matrix of the matrix multiplication ab.
    a : const T (&)[L][N]
      Reference to the left matrix of the matrix multiplication ab.
    b : const T (&)[M][L]
      Reference to the right matrix of the matrix multiplication ab.

    Returns
    -------
    void
      Result is put in r.
    */

    for (unsigned long i = 0; i < M; i++)
      for (unsigned long j = 0; j < N; j++)
      {
        r[i][j] = 0;
        for (unsigned long k = 0; k < L; k++)
          r[i][j] += a[k][j] * b[i][k];
      }
    return;
  }

  template <class T, unsigned long N>
  void to2d(T (&a)[1][N], T (&b)[N])
  {
    /*
    Make array 2-dimensional / make matrix.

    Parameters
    ----------
    a : T (&)[1][N]
      Reference to resulting 2-dimensional array / matrix.
    b : T (&)[N]
      Reference to 1-dimensional array content.

    Returns
    -------
    void
      Result is put in a.
    */

    a[0] = b;
    return;
  }

  template <class T, unsigned long N, unsigned long M, unsigned long K, unsigned long L>
  void reDefine(T (&a)[N][M], const T (&b)[K][L])
  {
    /*
    Migrate matrix content to other matrix with the same number of elements.

    Parameters
    ----------
    a : T (&)[N][M]
      Reference to the resulting matrix, which will receive content.
    b : const T (&)[K][L]
      Reference to the matrix with content to migrate.

    Returns
    -------
    void
      Result is put in a.
    
    Warnings
    --------
    If N * M != K * L, the resulting matrix may loose data or initialize new data.
    */

    for (unsigned long i = 0; i < N * M; i++)
      a[i / M][i % M] = (i < K*L) ? b[i / L][i % L] : T();
    return;
  }

  template <class T, unsigned long N, unsigned long M, class T2 = char, class T3 = char>
  void toStream(const T (&a)[N][M], std::ostream& os, const bool& linAlgLike = true, const T2& elend = '\t', const T3& lnend = '\n')
  {
    /*
    Put a matrix's content in a stream.

    Parameters
    ----------
    a : const T (&)[N][M]
      The matrix whose content is read.
    os : std::ostream&
      The output stream which will receive content.
    linAlgLike : const bool&, optional, default = true
      Tell when to write lines and columns like mathematical or programming notation.
    elend : const T2&, optional, default = '\t'
      Tell which value is writen after every element.
    lnend : const T3&, optional, default = '\n'
      Tell which value is writen after every line.

    Returns
    -------
    void
      The content of the matrix is put in the stream.
    */

    for (unsigned long i = 0; i < M; i++)
    {
      for (unsigned long j = 0; j < N; j++)
        os << ((linAlgLike) ? a[j][i] : a[i][j]) << elend;
      if (i < M-1) os << lnend;
    }
    return;
  }

  template <class T, unsigned long N, unsigned long M>
  void fromStream(T (&a)[N][M], std::istream& is, const bool& linAlgLike = true)
  {
    /*
    Get content from a stream to a matrix.

    Parameters
    ----------
    a : T (&)[N][M]
      The matrix which will receive content.
    is : std::istream&
      The input stream whose content is read.
    linAlgLike : const bool&, optional, default = true
      Tell when to read lines and columns like mathematical or programming notation.

    Returns
    -------
    void
      The content of the stream is put in the matrix.
    */

    for (unsigned long i = 0; i < M; i++)
      for (unsigned long j = 0; j < N; j++)
        is >> ((linAlgLike) ? a[j][i] : a[i][j]);
    return;
  }

  template <class T, unsigned long N, unsigned long M>
  void fromFunction(T (&a)[N][M], const T (*f)(const unsigned long& i, const unsigned long& j))
  {
    /*
    Get content from a function of indexes to a matrix.

    Parameters
    ----------
    a : T (&)[N][M]
      The matrix which will receive content.
    f: const T (*)(const unsigned long& i, const unsigned long& j)
      The function whose returning content is read.

    Returns
    -------
    void
      The returning content of the function is put in the matrix.
    */

    for (unsigned long i = 0; i < N; i++)
      for (unsigned long j = 0; j < M; j++)
        a[i][j] = f(i, j);
    return;
  }

  template <class T, class T2, unsigned long N, unsigned long M>
  void fromFunction(T (&a)[N][M], const T (*f)(const T2& x), const T2 (&b)[N][M])
  {
    /*
    Get content from a function of a matrix to a matrix.

    Parameters
    ----------
    a : T (&)[N][M]
      The matrix which will receive content.
    f: const T (*)(const T2& x)
      The function whose returning content is read.
    b : const T2 (&)[N][M]
      The matrix whose content is read.

    Returns
    -------
    void
      The returning content of the function is put in the matrix.
    */

    for (unsigned long i = 0; i < N; i++)
      for (unsigned long j = 0; j < M; j++)
        a[i][j] = f(b[i][j]);
    return;
  }
}

#endif
