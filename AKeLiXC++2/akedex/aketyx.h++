#ifndef AKEDEX_TYX
#define AKEDEX_TYX

#include <cstddef>
#include "akeerx.h++"

namespace tyx
{
  struct nulltype
  {
    erx::Error err = erx::NULL_ERR;
  };


  template <class t>
  class SecPtr
  : public erx::Secure<t>
  {
  private:

    t* dt;

  protected:

    bool   isalc; 
    size_t bc   ; // WIP

  public:
    
    SecPtr ()
    { this->set(erx::NODATA_ERR); }

    SecPtr(const erx::Error& error)
    { this->set(error); }

    SecPtr(t* value, const bool& isalc, const size_t& bytc = sizeof(t))
    { this->set(value, isalc, bytc); }

    SecPtr(t& value, const size_t& bytc = sizeof(t))
    { this->set(&value, false, bytc); }

    
    ~SecPtr()
    { if (this->isalc) delete dt; }

    
    virtual void set(const erx::Error& error) override
    { this->err = error; }

    virtual void set(t* value, const bool& isalc, const size_t& bytc = sizeof(t))
    {
      if (!(bytc > 0)) throw erx::OUTOFRANGE_ERR;

      this->dt    = value     ;
      this->isalc = isalc     ;
      this->bc    = bytc      ;
      this->err   = {false, 0};
    }


    virtual t& unpack() override
    {
      if (this->exists()) return *this->dt;
      else throw this->err;
    }


    virtual t* unveil()
    {
      if (this->exists()) return this->dt;
      else throw this->err;
    }

    
    virtual t& operator*() override
    { return this->unpack(); }


    virtual t* operator&()
    { return this->unveil(); }
  };


  template<class T>
  const SecPtr<T> NothingPtr = SecPtr<T>();


  template<class T>
  SecPtr<T> some(T* value, const bool& isalc, const size_t& bytc = sizeof(T))
  { return SecPtr<T>(value, isalc, bytc); }

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
