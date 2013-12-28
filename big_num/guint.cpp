#include "guint.h"

#include <cstdio>

#include <algorithm>

Guint::Guint()
  : idx_(0)
{
}

Guint::Guint(const vector<u16> data)
{
  data_ = data;
}

Guint::Guint(u32 num)
  : idx_(0)
{
  u16 i1 = num & 0xffff;
  u16 i2 = ((num >> 16 ) & 0xffff);
  #if 0
  cout << "i1: " << i1 << endl;
  cout << "i2: " << i2 << endl;
  #endif
  data_.push_back(i1);
  data_.push_back(i2);
}

Guint::Guint(const std::string num)
  : idx_(0)
{
  convert_to_cal_data(num);
}

#if 0
Guint::Guint(const char *num)
  : idx_(0)
{
  convert_to_cal_data(num);
}
#endif

bool Guint::convert_to_cal_data(const std::string num)
{
  for (int i=0 ; i < num.size() ; ++i)
  {
    if (!isdigit(num[i]))
    {
      cout << "not number" << endl;
      return false;
    }
  }

  string nstr;

  if ((num.size() % 2) == 0)
  {
    nstr = num;
  }
  else
  {
    nstr = string("0") + num;
  }

  for (int k= nstr.size() -1 ; k >= 0; k-=2)
  {
    int i = nstr[k] - '0';
    int j = nstr[k-1] - '0';
    data_.push_back(j*10 + i);
  }
#if 0
  cout << "number" << endl;

  for (int i=0 ; i < data_.size() ; ++i)
  {
    cout << data_[i] << endl;
  }
#endif
  return true;
}

Guint Guint::add(u32 n) const
{
  Guint a(n);
  return add(a);
}

Guint Guint::add(const Guint &guint) const
{
  vector<u16> data;
  u16 carry = 0;

  int n = max(count(), guint.count());

  //cout << "n: " << n << endl;

  for (int i=0 ; i < n ; ++i)
  {
    u16 a1 = i < count() ? data_[i] : 0;
    u16 a2 = i < guint.count() ? guint.data_[i] : 0;
    u32 t = a1 + a2  + carry;
#if 0
    cout << "a1: " << a1 << endl;
    cout << "a2: " << a2 << endl;
#endif
    //stringstream ss;
    //ss << (t%100);
    //string tmp = ss.str();
    //cout << tmp << endl;
    data.push_back(t%100);
    carry = t/100;
  }
#if 0
  for (int i=0 ; i < data.size() ; ++i)
  {
    cout << data[i] << endl;
  }
#endif
  return Guint(data);
}

// prefix ++
Guint Guint::operator++()
{
  cout << "prefix++" << endl;
  *this = add(1);
  return (*this);
}

// postfix ++
Guint Guint::operator++(int)
{
  cout << "postfix++" << endl;
  Guint tmp(*this);
  *this = add(1);

  return tmp;
}

Guint operator+(const Guint &guint1, const Guint &guint2)
{
  return guint1.add(guint2);
}

Guint operator+(const Guint &guint1, u32 n)
{
  return guint1.add(n);
}



ostream& operator<<(ostream &os, const Guint &guint)
{
  for (int i=NUM-1 ; i >= 0 ; --i)
  {
    if (guint.data_[i] != 0)
      os << guint.data_[i];
  }
  return os;
}
