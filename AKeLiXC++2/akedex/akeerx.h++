#ifndef AKEDEX_ERX
#define AKEDEX_ERX

namespace erx
{
  /* AKeDeX - ErX -- Akai Keisanki Deffinition eXperiments - Error eXperiments */


  struct Error
  {
    /*
    Error struct for type identification.

    Attributes
    ----------
    real : bool
      True if the error is real/valid (aka. has_error).
    code : signed
      The error code for identification.

    Notes
    -----
    It's recommended not to use custom error codes if it
    isn't needed.
    */

    bool   real;
    signed code;
  };


  namespace KErr
  {
    /*
    Known Errors

    Relevant `Error` constants.

    Notes
    -----
    It is recommended to use error constants instead of `Error` literals for a better
    readability and to avoid type confusion.
    */ 

    constexpr Error
    NODATA_ERR      = (Error) {true,    0}, // Unexistance of initial data
    UNKNOWN_ERR     = (Error) {true,    1}, // Uknown
    INVALIDOP_ERR   = (Error) {true, -  1}, // Impossible operations
    UNEXISTANT_ERR  = (Error) {true,    2}, // Existance or knowledge
    OUTOFRANGE_ERR  = (Error) {true, -  2}, // Ranges and limits of continuous data
    IO_ERR          = (Error) {true,    3}, // Input and output
    FILEIO_ERR      = (Error) {true, -  3}, // File input and output
    PTR_ERR         = (Error) {true,    4}, // Pointer arithmetic
    NULLPTR_ERR     = (Error) {true, -  4}, // Null pointers
    RESOURCEOUT_ERR = (Error) {true,    5}, // Memory, processor and recursion
    TIMEOUT_ERR     = (Error) {true, -  5}, // Time
    UNSECURE_ERR    = (Error) {true,    6}, // Code security
    BLOCK_ERR       = (Error) {true, -  6}, // Access or denials
    RELATION_ERR    = (Error) {true,    7}, // Relations of data
    PARSE_ERR       = (Error) {true, -  7}, // Interpreting data
    NULL_ERR        = (Error) {true,    8}, // Null type
    TYPE_ERR        = (Error) {true, -  8}, // Data type
    RUNTIME_ERR     = (Error) {true,    9}, // General runtime
    CASE_ERR        = (Error) {true, -  9}; // Specific case
  }


  class SecType {};

  template <class t>
  class Secure : public SecType
  {
    /*
    Secure class to wrap an object with error handling and encapsulation.

    Attributes
    ----------
    dt : t, private
      The wrapped object/value/data.
    err : erx::Error, protected
      An error for when the object should not be used or isn't available.
    */

  private:

    t dt;

  protected:

    Error err;

  public:
    
    Secure()
    {
      /*
      Secure object with no data constructor.

      Parameters
      ----------

      Returns
      -------
      Secure<t>
      */

      this->set(KErr::NODATA_ERR);
    }

    Secure(const Error& error)
    {
      /*
      Secure object with error constructor.

      Parameters
      ----------
      error : const erx::Error&
        An error which makes the content unavailable.

      Returns
      -------
      Secure<t>
      */

      this->set(error);
    }

    Secure(const t& value)
    {
      /*
      Secure object with wrapped object constructor.

      Parameters
      ----------
      value : const t&
        An object/value to wrap.

      Returns
      -------
      Secure<t>
      */

      this->set(value);
    }

    
    virtual void set(const Error& error)
    {
      /*
      Error setter.

      Parameters
      ----------
      error : const erx::Error&
        An error which makes the content unavailable.

      Returns
      -------
      void
      */

      this->err = error;
    }

    virtual void set(const t& value)
    {
      /*
      Object/value wrapper/setter.

      Parameters
      ----------
      value : const t&
        An object/value to wrap.

      Returns
      -------
      void
      */

      this->dt  = value     ;
      this->err = {false, 0};
    }


    virtual t& unpack()
    {
      /*
      Object/value unwrapper/unpacker.

      Parameters
      ----------

      Returns
      -------
      this->dt : t&
        The wrapped object/value/data.

      Raises
      ------
      this->err : erx::Error
        An error for when the object should not be used or isn't available.
      */

      if (this->exists()) return this->dt;
      else throw this->err;
    }

    
    virtual bool exists()
    {
      /*
      Error verifier.

      Parameters
      ----------

      Returns
      -------
      bool
        True if the object can be used / is available / exists.
      */

      return !this->err.real;
    }


    virtual t& operator*()
    {
      /*
      Operator `*` for unwrapping/unpacking the wrapped value, similar to pointer dereferencing.

      Parameters
      ----------

      Returns
      -------
      t&
        The wrapped object/value/data.

      Raises
      ------
      this->err : erx::Error
        An error for when the object should not be used or isn't available.
      */

      return this->unpack();
    }
  };


  template<class T>
  const Secure<T> Nothing = Secure<T>();
  /*
  `Secure<t>` class constant with no `erx::KErr::NODATA_ERR` error.

  A secure object that doesn't have any wrapped data.
  */


  template<class T>
  Secure<T> pack(const T& value)
  {
    /*
    Pack/wrap an object/value in a `Secure<t>` object.

    Parameters
    ----------
    value : const T&
      An object/value to wrap.

    Returns
    -------
    Secure<T>
      A `Secure<T>` object with wrapped data.
    */

    return Secure<T>(value);
  }
}

#endif
