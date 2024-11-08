#ifndef AKEDEX_ERX
#define AKEDEX_ERX

namespace erx
{

  struct Error
  {
    bool   real;
    signed code;
  };


  const Error      NODATA_ERR = {true,    0}, // Unexistance of initial data
                  UNKNOWN_ERR = {true,    1}, // Uknown
                INVALIDOP_ERR = {true, -  1}, // Impossible operations
               UNEXISTANT_ERR = {true,    2}, // Existance or knowledge
               OUTOFRANGE_ERR = {true, -  2}, // Ranges and limits of continuous data
                       IO_ERR = {true,    3}, // Input and output
                   FILEIO_ERR = {true, -  3}, // File input and output
                      PTR_ERR = {true,    4}, // Pointer arithmetic
                  NULLPTR_ERR = {true, -  4}, // Null pointers
              RESOURCEOUT_ERR = {true,    5}, // Memory, processor and recursion
                  TIMEOUT_ERR = {true, -  5}, // Time
                 UNSECURE_ERR = {true,    6}, // Code security
                    BLOCK_ERR = {true, -  6}, // Access or denials
                 RELATION_ERR = {true,    7}, // Relations of data
                    PARSE_ERR = {true, -  7}, // Interpreting data
                     NULL_ERR = {true,    8}, // Null type
                     TYPE_ERR = {true, -  8}, // Data type
                  RUNTIME_ERR = {true,    9}, // General runtime
                     CASE_ERR = {true, -  9}; // Specific case

  class SecType {};

  template <class t>
  class Secure : public SecType
  {
  private:

    t dt;

  protected:

    Error err;

  public:
    
    Secure()
    { this->set(NODATA_ERR); }

    Secure(const Error& error)
    { this->set(error); }

    Secure(const t& value)
    { this->set(value); }

    
    virtual void set(const Error& error)
    { this->err = error; }

    virtual void set(const t& value)
    {
      this->dt  = value     ;
      this->err = {false, 0};
    }


    virtual t& unpack()
    {
      if (this->exists()) return this->dt;
      else throw this->err;
    }

    
    virtual bool exists()
    { return !this->err.real; }


    virtual t& operator*()
    {
      return this->unpack();
    }
  };


  template<class T>
  const Secure<T> Nothing = Secure<T>();


  template<class T>
  Secure<T> pack(const T& value)
  { return Secure<T>(value); }
}

#endif
