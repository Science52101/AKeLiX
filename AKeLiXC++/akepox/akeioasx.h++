#ifndef AKEIOASX_H
#define AKEIOASX_H

// AKeIOASX - Akai Keisanki Input and Output Array Stream eXperiments

namespace akepox
{

template<typename type>
class ioas
{
protected:

  type* array;
  int index;

public:

  static type END;

  ioas() {
    this->index = 0;
    this->array = new type[index+1];
    this->array[index] = END;
  }
  
  ioas(const type* array, const int& size)
  {
    *this = ioas<type>::get();
    this->set(array, size);
  }

  ioas(const type* begin, const type* end)
  {
    *this = ioas<type>::get();
    this->set(begin, end);
  }

  ioas(const int& size, const type& x = END)
  {
    *this = ioas<type>::get();
    this->set(size, x);
  }

  ~ioas()
  { delete[] array; }

  inline int get_index() const
  { return index; }

  void set_index(const int& nindex, type x = END)
  {
    type* narray = new type[nindex+1];
    
    for (int i = 0; i < nindex; i++)
    {
      if (i < this->index) narray[i] = this->array[i];
      else narray[i] = x;
    }
    narray[nindex] = END;
    
    this->index = nindex;
    type* tmp = array;
    this->array = narray;
    delete[] tmp;
  }

  inline type* begin() const
  { return array; }

  inline type* end() const
  { return array+index; }

  inline int size() const
  { return this->get_index(); }

  void set(const type* array, const int& size)
  {
    type* tmp = this->array;
    this->index = size;
    this->array = new type[this->index+1];

    for (int i = 0; i < this->index; i++) this->array[i] = array[i];
    this->array[this->index] = END;
    delete[] tmp;
  }

  void set(const type* begin, const type* end)
  {
    type* tmp = this->array;
    this->index = 0;
    for (const type* i = begin; i < end; i++)
      index++;
    this->array = new type[this->index+1];

    for (int i = 0; i < index; i++)
      this->array[i] = begin[i];
    this->array[this->index] = END;
    delete[] tmp;
  }

  void set(const int& size, const type& x = END)
  {
    type* tmp = this->array;
    this->index = size;
    this->array = new type[this->index+1];

    for (int i = 0; i < this->index; i++) this->array[i] = x;
    this->array[this->index] = END;
    delete[] tmp;
  }

  type erase(const int& idx)
  {
    type el;

    if (index != 0)
    {
      el = this->array[idx];

      type* narray = new type[--index+1];
      
      for (int i = 0; i < index; i++)
      {
        if (i < idx) narray[i] = array[i];
	else narray[i] = array[i+1];
      }
      narray[index] = END;
      
      type* tmp = array;
      this->array = narray;
      delete[] tmp;

    }
    else
      el = this->array[index];

    return el;
  }

  inline type pop_front()
  { return this->erase(0); }

  inline type pop_back()
  { return this->erase(index-1); }

  inline type pop(const int& idx = 0)
  { return this->erase(idx); }

  void add(const int& idx, const type& el)
  {
    type* narray = new type[++index+1];
    
    for (int i = 0; i < index-1; i++)
    {
      if (i < idx) narray[i] = this->array[i];
      else narray[i+1] = this->array[i];
    }
    narray[idx] = el;
    narray[index] = END;
    
    type* tmp = array;
    this->array = narray;
    delete[] tmp;
  }

  inline type push_front(const type& el = END)
  { return this->add(0, el); }

  inline type push_back(const type& el = END)
  { return this->add(index-1, el); }

  inline type push(const int& idx = 0, const type& el = END)
  { return this->add(idx, el); }

  ioas& operator<<(const type& el)
  {
    this->array[index++] = el;
    type* narray = new type[index+1];
    
    for (int i = 0; i < index; i++) narray[i] = this->array[i];
    narray[index] = END;
    
    type* tmp = array;
    this->array = narray;
    delete[] tmp;

    return *this;
  }

  ioas& operator>>(type& el)
  {
    if (index != 0)
    {
      el = this->array[--index];

      type* narray = new type[index+1];
      
      for (int i = 0; i < index; i++) narray[i] = array[i];
      narray[index] = END;
      
      type* tmp = array;
      this->array = narray;
      delete[] tmp;
    }
    else
      el = this->array[index];

    return *this;
  }

  friend ioas<type>& operator>>(const type& el, ioas<type>& a)
  {
    type* narray = new type[++a.index+1];
    narray[0] = el;
    
    for (int i = 1; i <= a.index; i++) narray[i] = a.array[i-1];
    narray[a.index] = a.END;
    
    type* tmp = a.array;
    a.array = narray;
    delete[] tmp;

    return a;
  }

  friend ioas<type>& operator<<(type& el, ioas<type>& a)
  {
    el = type(a.array[0]);

    if (a.index != 0)
    {
      type* narray = new type[a.index--];
      
      for (int i = 1; i <= a.index; i++) narray[i-1] = a.array[i];
      narray[a.index] = a.END;
      
      type* tmp = a.array;
      a.array = narray;
      delete[] tmp;
    }

    return a;
  }

  inline virtual type& operator[](const int& i)
  { return array[i]; }

  inline virtual type* operator*(const int& i)
  { return array+i; }

  friend ioas<type> operator+(const ioas<type>& a, const ioas<type>& b)
  {
    ioas<type> r = ioas<type>::get();
    r.set(a.array, a.index);
    for (type* el = b.array; el < b.array+b.index; el++)
    { r << *el; }
    return r;
  }

  friend ioas<type> operator-(const ioas<type>& a, const ioas<type>& b)
  {
    ioas<type> r = ioas<type>::get();
    r.set(a.array, a.index);
    r.set_index(b.index);
    return r;
  }

  inline static ioas<type> get()
  { return ioas<type>(); }

};

template<class type>
type ioas<type>::END = type();

#define loopioas(el, ioas_x) for(auto* el = ioas_x.begin(); el < ioas_x.end(); el++)

template<class type>
std::ostream& operator<<(std::ostream& os, const ioas<type>& a)
{
  os << "[L]";
  loopioas(el, a) os << " << " << *el;
  os << " << [R]";
  return os;
}


template<class type>
ioas<type> fioas (type (*f)(type), const ioas<type>& X)
{
  ioas<type> Y;
  loopioas(el, X) Y << f(*el);
  return Y;
}

}

#endif
