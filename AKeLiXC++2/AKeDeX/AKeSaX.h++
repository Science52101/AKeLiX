#ifndef AKEDEX_SAX
#define AKEDEX_SAX

// Akai Keisanki Definition eXperiments - Safe eXperiments

#include <stdexcept>
#include <cstddef>
#include <utility>

namespace sax
{
  struct Err
  {
    unsigned short code;
  };

  template <class T>
  class Ptr
  {
    /* Safe Pointer Class */

  private:
    bool   avl;
    size_t siz;

    union
    {
      Err err;
      T*  ptr;
    };

  public:
    Ptr ()
    {
      /* Empty Constructor */

      avl = false;
      siz = 0    ;
      err = {0}  ;
    }

    Ptr (const T& v, const size_t& s = 1)
    {
      /* Repeating Constructor */

      siz = s;

      if (s > 0)
      {
        avl = true    ;
        ptr = new T[s];

        for (T* p = ptr; p < ptr + s; p ++) *p = v;
      }
      else
      {
        avl = false  ;
        err = Err {0};
      }
    }

    Ptr (const Ptr& r)
    {
      /* Deep Copy Constructor */

      avl = r.avl;
      siz = r.siz;

      if (avl)
      {
        ptr = new T[siz];
        std::copy(r.ptr, r.ptr + r.siz, ptr);
      }
      else
        err = r.err;
    }

    Ptr (Ptr&& r)
    {
      /* Move Constructor */

      avl = r.avl;
      siz = r.siz;

      if (avl)
      {
        ptr = r.ptr;
        r.ptr = nullptr;
      }
      else
        err = r.err;

      r.avl = false;
      r.siz = 0    ;
      r.err = {255};
    }

    ~Ptr ()
    {
      /* Destructor */

      if (avl) delete[] ptr;
    }

    size_t getSiz ()
    {
      /* Size (`siz`) Getter */

      return siz;
    }

    Err getErr ()
    {
      /* Error (`err`) Getter */
      
      if (avl) throw std::logic_error ("Pointer is available. Ptr<T>::chk() to check if it is available instead of getting its error.");

      return err;
    }

    bool chk ()
    {
      /* Availability (`avl`) Getter */
      
      return avl;
    }
    
    void del ()
    {
      /* Explicit Destructor / Availability Setter to `false` */

      if (avl)
      {
        avl = false;

        delete[] ptr;

        siz = 0    ;
        err = {1}  ;
      }
    }

    T& get (const size_t& i = 0)
    {
      /* Data (´ptr[i]´) Getter */

      if (!avl)     throw std::logic_error ("Pointer is not available. Use Ptr<T>::getErr() to get its error.");
      if (i >= siz) throw std::out_of_range("Getter index of pointer is out of range of allocation. Use Ptr<T>::getSiz to get its size.");

      return ptr[i];
    }

    class Iterator
    {
      /* Safe Pointer Iterator Class */

    private:
      size_t pos;
      Ptr<T>* spt;

    public:
      Iterator (const size_t& pos, Ptr<T>* spt)
      {
        if (!spt->avl)     throw std::logic_error ("Pointer is not available. Use Ptr<T>::getErr() to get its error.");
        if (pos > spt->siz) throw std::out_of_range("Iterator index of pointer is out of range of allocation. Use Ptr<T>::getSiz to get its size.");

        this->pos = pos;
        this->spt = spt;
      }

      Iterator (const Iterator& r)
      {
        pos = r.pos;
        spt = r.spt;
      }

      ~Iterator () {}

      Iterator operator ++ ()
      {
        if (pos >= spt->siz) throw std::out_of_range("++() - Iterator index of pointer is out of range of allocation. Use Ptr<T>::getSiz to get its size.");
        Iterator it = *this;
        pos ++;
      }

      Iterator operator ++ (int)
      {
        if (pos >= spt->siz) throw std::out_of_range("++(int) - Iterator index of pointer is out of range of allocation. Use Ptr<T>::getSiz to get its size.");
        pos ++;
        return *this;
      }

      Iterator operator -- ()
      {
        if (pos == 0) throw std::out_of_range("--() -Iterator index of pointer is out of range of allocation. Use Ptr<T>::getSiz to get its size.");
        Iterator it = *this;
        pos ++;
      }

      Iterator operator -- (int)
      {
        if (pos == 0) throw std::out_of_range("--(int) - Iterator index of pointer is out of range of allocation. Use Ptr<T>::getSiz to get its size.");
        pos --;
        return *this;
      }

      T operator * ()
      { return spt->get(pos); }

      bool operator < (Iterator r)
      { return pos < r.pos; }

      bool operator > (Iterator r)
      { return pos > r.pos; }

      bool operator == (Iterator r)
      { return pos == r.pos; }

      bool operator != (Iterator r)
      { return pos != r.pos; }

      friend class Ptr<T>;
    };

    Iterator begin()
    {
      /* Initial Safe Pointer Iterator Getter */

      return Iterator(0, this);
    }

    Iterator end()
    {
      /* Ending Safe Pointer Iterator Getter */
      
      return Iterator(siz, this);
    }

    friend class Ptr<T>::Iterator;
  };
}

#endif