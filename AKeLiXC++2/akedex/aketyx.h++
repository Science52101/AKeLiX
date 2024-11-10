#ifndef AKEDEX_TYX
#define AKEDEX_TYX

#include <cstddef>
#include "akeerx.h++"

namespace tyx
{
  struct nulltype
  {
    /*
    Null type that contains explanative error.

    Attributes
    ----------
    err : erx::Error, default = erx::KErr::NULL_ERR;
    */

    erx::Error err = erx::KErr::NULL_ERR;
  };


  template <class t>
  class SecPtr
  : public erx::Secure<t>
  {
    /*
    Secure pointer class to wrap a pointer with error handling and encapsulation.

    Attributes
    ----------
    dt : t*, private
      The wrapped pointer.
    err : erx::Error, protected
      An error for when the object should not be used or isn't available.
    autalc : bool, protected
      True if value should be automatically deleted.
    bc : size_t, protected
      Byte ammount that is safe to access from the pointed position. (WIP)
    */

  private:

    t* dt;

  protected:

    bool   autalc;
    size_t bc    ; // WIP

  public:
    
    SecPtr ()
    {
      /*
      Secure pointer with no data constructor.

      Parameters
      ----------

      Returns
      -------
      SecPtr<t>
      */

      this->set(erx::KErr::NODATA_ERR);
    }

    SecPtr(const erx::Error& error)
    {
      /*
      Secure pointer with error constructor.

      Parameters
      ----------
      error : const erx::Error&
        An error which makes the content unavailable.

      Returns
      -------
      SecPtr<t>
      */

      this->set(error);
    }

    SecPtr(t* value, const bool& autalc = false, const size_t& bytc = sizeof(t))
    {
      /*
      Secure object with wrapped pointer constructor.

      Parameters
      ----------
      value : t*
        A pointer to wrap.
      autalc : const bool&, optional, default = false
        True if value should be automatically deleted.
      bytc : const size_t&, optional, default = sizeof(t)
        Byte ammount that is safe to access from the pointed position. (WIP)

      Returns
      -------
      SecPtr<t>
      */
      this->set(value, autalc, bytc);
    }

    SecPtr(t& value, const size_t& bytc = sizeof(t))
    {
      /*
      Secure pointer with wrapped pointer to object constructor.

      Parameters
      ----------
      value : t&
        An object/value to point and wrap.
      bytc : const size_t&, optional, default = sizeof(t)
        Byte ammount that is safe to access from the pointed position. (WIP)

      Returns
      -------
      SecPtr<t>
      */

      this->set(&value, false, bytc);
    }

    
    ~SecPtr()
    {
      /*
      Secure pointer destructor for deleting `dt` if `autalc`.
      */

      if (this->autalc) delete dt;
    }

    
    virtual void set(const erx::Error& error) override
    {
      /*
      Error setter.

      Parameters
      ----------
      error : const erx::Error&
        An error which makes the pointer unavailable.

      Returns
      -------
      void
      */

      this->err = error;
    }

    virtual void set(t* value, const bool& autalc = false, const size_t& bytc = sizeof(t))
    {
      /*
      Pointer wrapper/setter.

      Parameters
      ----------
      value : t*
        A pointer to wrap.
      autalc : const bool&, optional, default = false
        True if value should be automatically deleted.
      bytc : const size_t&, optional, default = sizeof(t)
        Byte ammount that is safe to access from the pointed position. (WIP)

      Returns
      -------
      void
      */
      

      if (!(bytc > 0)) throw erx::KErr::OUTOFRANGE_ERR;

      this->dt     = value     ;
      this->autalc = autalc    ;
      this->bc     = bytc      ;
      this->err    = {false, 0};
    }


    virtual t& unpack() override
    {
      /*
      Pointer dereferencer / pointed object/value unwrapper/unpacker.

      Parameters
      ----------

      Returns
      -------
      this->dt : t&
        The object/value/data pointed by the wrapped pointer.

      Raises
      ------
      this->err : erx::Error
        An error for when the pointer should not be used or isn't available.
      */

      if (this->exists()) return *this->dt;
      else throw this->err;
    }


    virtual t* unveil()
    {
      /*
      Pointer unwrapper/unpacker.

      Parameters
      ----------

      Returns
      -------
      this->dt : t*
        The wrapped pointer.

      Raises
      ------
      this->err : erx::Error
        An error for when the pointer should not be used or isn't available.
      */

      if (this->exists()) return this->dt;
      else throw this->err;
    }

    
    virtual t& operator*() override
    {
      /*
      Operator `*` for dereferencing the value pointed by the wrapped pointer, similar to typical pointer dereferencing.

      Parameters
      ----------

      Returns
      -------
      dt : t&
        The object/value/data pointed by the wrapped pointer.

      Raises
      ------
      this->err : erx::Error
        An error for when the object should not be used or isn't available.
      */

      return this->unpack();
    }


    virtual t* operator&()
    {
      /*
      Operator `&` for unwrapping/unpacking the wrapped pointer, similar to referencig.

      Parameters
      ----------

      Returns
      -------
      t*
        The wrapped pointer.

      Raises
      ------
      this->err : erx::Error
        An error for when the object should not be used or isn't available.
      */

      return this->unveil();
    }
  };


  template<class T>
  const SecPtr<T> NothingPtr = SecPtr<T>();


  template<class T>
  SecPtr<T> some(T* value, const bool& autalc, const size_t& bytc = sizeof(T))
  { return SecPtr<T>(value, autalc, bytc); }

  template<class T>
  SecPtr<T> some(T& value, const size_t& bytc = sizeof(T))
  { return SecPtr<T>(value, bytc); }

  template<class T>
  SecPtr<T> some(const T& value, const size_t& bytc = sizeof(T))
  { return SecPtr<T>(new T(value), true, bytc); }

  template<class T>
  SecPtr<T> some(erx::Secure<T>& scval)
  { return SecPtr<T>(scval.unpack()); }
}

#endif
