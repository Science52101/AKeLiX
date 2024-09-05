#ifndef AKENUSYX_H
#define AKENUSYX_H

#include <iostream>

// Akai Keisanki Number System eXperiments

struct nsys
{
private:
  std::string nums = "";
  int base = 0;

public:

  nsys() : nums("A234567890JQK"), base(13) {  }

  nsys(std::string nums) : nums(nums), base(nums.length()) {  }

  nsys(std::string nums, int base) : nums(nums), base(base) {  }

  int tfrom(std::string cvsip)
  {
    int output = 0;
    for (int i = 0; i < sizeof(cvsip); i++)
    { output += nums.find( cvsip[ (int) ( sizeof(cvsip) - i - 1 ) ] ) * ( base * i ); }
    return output;
  }

  std::string tto(int cvsip)
  {
    std::string output = "";
    while (cvsip != 0)
    {
      output = nums[ ( cvsip % base ) ] + output;
      cvsip /= base;
    }
    return output;
  }
};

struct nsn
{
private:
  int value;
  nsys sys;

public:
  nsn() : value(0), sys(nsys()) {}

  nsn(int value, nsys sys) : value(value), sys(sys) {  }

  nsn(std::string value, nsys sys) : value(sys.tfrom(value)), sys(sys) {  }

  std::string get()
  { return sys.tto(value); }

  int getInt()
  { return value; }

  nsn operator+(nsn nsn2)
  { return nsn(value + nsn2.getInt(), sys); }

  nsn operator*(nsn nsn2)
  { return nsn(value * nsn2.getInt(), sys); }

  nsn operator/(nsn nsn2)
  { return nsn(value / nsn2.getInt(), sys); }

  nsn operator-(nsn nsn2)
  { return nsn(value - nsn2.getInt(), sys); }

  nsn operator+(int nsn2)
  { return nsn(value - nsn2, sys); }

  nsn operator*(int nsn2)
  { return nsn(value * nsn2, sys); }

  nsn operator/(int nsn2)
  { return nsn(value / nsn2, sys); }

  nsn operator-(int nsn2)
  { return nsn(value - nsn2, sys); }
};

#endif
