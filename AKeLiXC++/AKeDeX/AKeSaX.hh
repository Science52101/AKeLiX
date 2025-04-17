#ifndef AKEDEX_WRAX
#define AKEDEX_WRAX

// Akai Keisanki Definition eXperiments - Safe eXperiments

#include <cstdint>

#include <utility>
#include <type_traits>

namespace akelix
{

namespace sax
{
  // Declarations


  class IWrapper;

  template <class T>
  class Wrapper;

  template <class T>
  class Borrow;

  template <class T>
  void drop (T&);

  template <class T>
  T clone (T&);

  template <class T>
  struct IsWrapper;


  // Definitions


  template <class T>
  struct IsWrapper : std::false_type {};


  class IWrapper
  {
  public:

    virtual void drop (void) = 0;
    virtual bool ok (void) = 0;
    virtual bool empty (void) = 0;

    virtual ~IWrapper (void) = default;

  };


  template <>
  struct IsWrapper<IWrapper> : std::true_type {};

  /* Wrapper class template
   *
   * Wraps any class instance into a secure object.
   * 
   */
  template <class T>
  class Wrapper : IWrapper
  {
  protected:

    T* obj;

    /* States:
     *
     * 0xXY - X: general state, Y: specifier
     *
     * X = 0: OK
     * - Y = 0: OK
     * - Y = 1: Empty
     *
     * X = 1: Moved
     * - Y = 0: Moved
     * - Y = 1: Borrowed
     * - Y = 1: Unborrowed (Borrow)
     *
     * X = 2: Dropped
     * - Y = 0: Dropped
     * - Y = 2: Dropped (Borrow)
     *
     * Formulas:
     *
     * General state: state / 0x10 (or state >> 4)
     * Specifier:     state % 0x10 (or state << 4 >> 4)
     *
     */
    uint8_t state; 

   
  public:

    Wrapper (T&& obj)
    : obj(new T), state(0x00)
    {
      *this->obj = std::move(obj);
    }

    Wrapper (const T& obj)
    : obj(new T), state(0x00)
    {
      *obj = std::move(obj);
    }

    Wrapper (Wrapper&& w)
    : obj(new T), state(0x01)
    {
      assign(w);
    }

    Wrapper (Wrapper& w)
    : obj(new T), state(0x01)
    {
      assign(w);
    }

    Wrapper (void)
    : obj(new T ()), state(0x01)
    {}

    ~Wrapper (void)
    {
      auto_drop();
    }


    virtual Wrapper& operator = (Wrapper& w)
    {
      return assign(w);
    }

    virtual Wrapper& operator = (Wrapper&& w)
    {
      return assign(w);
    }

    virtual operator T& ()
    {
      if (!ok()) throw state;

      return *obj;
    }

    
    virtual Wrapper& assign (Wrapper& w)
    {
      if (!ok()) throw state;
      if (!w.ok()) throw w.state;

      obj = w.obj;
      state = w.state;
      w.state = 0x10;
      w.obj = nullptr;

      return *this;
    }

    virtual Wrapper& assign (Wrapper&& w)
    {
      if (!ok()) throw state;
      if (!w.ok()) throw w.state;

      obj = w.obj;
      state = w.state;
      w.state = 0x10;
      w.obj = nullptr;

      return *this;
    }


    virtual Wrapper clone (void)
    {
      if (!ok()) throw state;

      Wrapper w;

      *w.obj = sax::clone(*obj);

      w.state = state;

      return w;
    }


    virtual void drop (void) override
    {
      if (!ok()) throw state;

      if (ok()) delete obj;
      state = 0x20;
      obj = nullptr;
    }

    virtual void auto_drop (void)
    {
      if (state >> 4 == 2 || state == 0x10) return;

      drop();
    }

    
    virtual bool ok (void) override
    {
      return state >> 4 == 0;
    }

    virtual bool empty (void) override
    {
      return state == 0x01;
    }


    friend class Borrow<T>;

    virtual Borrow<T> borrow (void)
    {
      return *this;
    }

  };


  template <class T>
  struct IsWrapper<Wrapper<T>> : std::true_type {};


  /* Borrow class template
   *
   * Borrows a Wrapper.
   *
   */
  template <class T>
  class Borrow
  : virtual public Wrapper<T>
  {
  protected:

    Wrapper<T>* w;

  public:

    Borrow (Wrapper<T>& w)
    : w(&w), Wrapper<T>(w)
    {
      w.state = 0x11;
    }

    Borrow (Borrow<T>& b)
    : w(new Wrapper<T> ()), Wrapper<T>()
    {
      assign(b);
    }

    ~Borrow (void)
    {
      auto_drop();
    }


    virtual Borrow& operator = (Wrapper<T>& w) override
    {
      return assign(w);
    }

    virtual Borrow& operator = (Wrapper<T>&& w) override
    {
      return assign(w);
    }
    
    Borrow& operator = (Borrow<T>& w)
    {
      return assign(w);
    }

    Borrow& operator = (Borrow<T>&& w)
    {
      return assign(w);
    }

    virtual operator T& () override
    {
      if (!Wrapper<T>::ok()) throw Wrapper<T>::state;

      return *Wrapper<T>::obj;
    }

    
    virtual Borrow& assign (Wrapper<T>& w) override
    {
      if (!Wrapper<T>::ok()) throw Wrapper<T>::state;
      if (!w.ok()) throw w.state;

      drop();

      this->w = &w;
      Wrapper<T>::obj = w.obj;
      Wrapper<T>::state = w.state;

      w.state = 0x11;
      w.obj = nullptr;

      return *this;
    }

    virtual Borrow& assign (Wrapper<T>&& w) override
    {
      if (!Wrapper<T>::ok()) throw Wrapper<T>::state;
      if (!w.ok()) throw w.state;

      drop();

      this->w = &w;
      Wrapper<T>::obj = w.obj;
      Wrapper<T>::state = w.state;

      w.state = 0x11;
      w.obj = nullptr;

      return *this;
    }

    virtual Borrow& assign (Borrow<T>& b)
    {
      if (!Wrapper<T>::ok()) throw Wrapper<T>::state;
      if (!b.ok()) throw b.state;

      drop();

      this->w = &b;
      Wrapper<T>::obj = b.obj;
      Wrapper<T>::state = b.state;

      b.state = 0x10;
      b.obj = nullptr;

      return *this;
    }

    virtual Borrow& assign (Borrow<T>&& b)
    {
      if (!Wrapper<T>::ok()) throw Wrapper<T>::state;
      if (!b.ok()) throw b.state;

      drop();

      this->w = &b;
      Wrapper<T>::obj = b.obj;
      Wrapper<T>::state = b.state;

      b.state = 0x10;
      b.obj = nullptr;

      return *this;
    }


    virtual Wrapper<T> clone (void) override
    {
      if (!Wrapper<T>::ok()) throw Wrapper<T>::state;

      Wrapper<T> w;

      if constexpr (IsWrapper<decltype(*Wrapper<T>::obj)>::value)
        *w.obj = Wrapper<T>::obj->clone();
      else
        *w.obj = *Wrapper<T>::obj;

      w.state = Wrapper<T>::state;

      return w;
    }


    void drop (void) override
    {
      if (!Wrapper<T>::ok()) throw Wrapper<T>::state;

      w->obj = Wrapper<T>::obj;
      w->state = Wrapper<T>::state;
      Wrapper<T>::state = 0x21;
      Wrapper<T>::obj = nullptr;
      w = nullptr;
    }

    void auto_drop (void) override
    {
      if (Wrapper<T>::state >> 4 == 2 || Wrapper<T>::state == 0x10) return;

      drop();
    }


    virtual Wrapper<T>& unborrow (void)
    {
      if (!Wrapper<T>::ok()) throw Wrapper<T>::state;

      w->obj = Wrapper<T>::obj;
      w->state = Wrapper<T>::state;
      Wrapper<T>::state = 0x13;
      Wrapper<T>::obj = nullptr;

      return *w;
    }

    virtual void reborrow (void)
    {
      if (!w->ok()) throw w->state;

      Wrapper<T>::obj = w->obj;
      Wrapper<T>::state = w->state;
      w->state = 0x11;
      w->obj = nullptr;
    }

  };


  template <class T>
  struct IsWrapper<Borrow<T>> : std::true_type {};


  template <class T>
  void drop (T& v)
  {
      if constexpr (IsWrapper<T>::value)
        v.drop();
  }

  template <class T>
  T clone (T& v)
  {
    if constexpr (IsWrapper<T>::value)
      return v.clone();

    return v;
  }

  // User Aliases
  
  template <class T>
  using wra = Wrapper<T>;

  template <class T>
  using bor = Borrow<T>;

}

}

#endif
