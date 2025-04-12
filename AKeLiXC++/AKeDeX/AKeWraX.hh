#ifndef AKEDEX_WRAX
#define AKEDEX_WRAX

// Akai Keisanki Definition eXperiments - Wrapper eXperiments

#include <cstdint>

#include <utility>

namespace akelix
{

namespace wrax
{

class IWrapper
{
public:
  virtual void drop (void) = 0;
  virtual bool ok (void) = 0;
  virtual bool empty (void) = 0;
};
  
template <class T>
class Wrapper : IWrapper
{
  /* Wrapper class template
   *
   * Wraps any class instance into a secure object.
   * 
   */

protected:

  T* obj;
  uint8_t state; 

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

public:

  Wrapper (T&& obj)
  : obj(new T), state(0x00)
  {
    *obj = std::move(obj);
  }

  Wrapper (const T& obj)
  : obj(new T), state(0x00)
  {
    *obj = std::move(obj);
  }

  Wrapper (void)
  : obj(new T ()), state(0x01)
  {}

  ~Wrapper (void)
  {
    drop();
  }


  Wrapper& operator = (Wrapper& w)
  {
    obj = w.obj;
    state = w.state;
    w.state = 0x10;
    w.obj = nullptr;

    return *this;
  }

  Wrapper& operator = (Wrapper&& w)
  {
    obj = w.obj;
    state = w.state;
    w.state = 0x10;
    w.obj = nullptr;

    return *this;
  }

  operator T& ()
  {
    if (!ok())
      return (T) {};

    return *obj;
  }


  void drop (void)
  {
    if (ok()) delete obj;
    state = 0x20;
    obj = nullptr;
  }

  
  bool ok (void)
  {
    return state >> 4 == 0;
  }

  bool empty (void)
  {
    return state == 0x01;
  }

};

template <class T>
class Borrow
: IWrapper, Wrapper<T>
{
protected:

  Wrapper<T>* w;

public:

  Borrow (Wrapper<T>& w)
  : w(&w), Wrapper<T>::obj(w->obj), Wrapper<T>::state(w->state)
  {
    w.state = 0x11;
    w.obj = nullptr;
  }

  ~Borrow (void)
  {
    drop();
  }

  void drop (void) override
  {
    w->obj = Wrapper<T>::obj;
    w->state = Wrapper<T>::state;
    Wrapper<T>::state = 0x21;
    Wrapper<T>::obj = nullptr;
    w = nullptr;
  }

};

void drop (IWrapper& w)
{
  w.drop();
}

}

}

#endif
