namespace vex
{
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

  template <class T, unsigned long N, unsigned long M>
  void toStream(std::ostream& os, const T (&a)[N][M], const bool& linAlgLike = true)
  {
    /*
    Put a matrix's content in a stream.

    Parameters
    ----------
    os : std::ostream&
      The output stream which will receive content.
    a : const T (*)[N][M]
      The matrix whose content is read.
    linAlgLike : const bool&, optional, default = true
      Tell when to write lines and columns like mathematical or programming notation.

    Returns
    -------
    void
      The content of the matrix is put in the stream.
    */

    for (unsigned long i = 0; i < M; i++)
    {
      for (unsigned long j = 0; j < N; j++)
        os << ((linAlgLike) ? a[j][i] : a[i][j]);
      os << '\n';
    }
    return;
  }

  template <class T, unsigned long N, unsigned long M>
  void fromStream(std::istream& is, T (&a)[N][M], const bool& linAlgLike = true)
  {
    /*
    Get content from a stream to a matrix.

    Parameters
    ----------
    os : std::istream&
      The input stream whose content is read.
    a : T (*)[N][M]
      The matrix which will receive content.
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
}
