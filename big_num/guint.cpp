#include "guint.h"

#include <cstdio>

#include <algorithm>

Guint::Guint()
  : idx_(0)
{
  data_.push_back(0);
  data_.push_back(0);
}

Guint::Guint(const vector<u16> data)
{
  data_ = data;
  if (data.size() < 2)
    data_.push_back(0);
}

Guint::Guint(u32 num)
  : idx_(0)
{
  stringstream ss;
  ss << num;
  convert_to_cal_data(ss.str());
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

  if (data_.size() < 2)
    data_.push_back(0); // if 89, append 0 to 0 89, use 2 u16.

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

Guint Guint::operator+=(const Guint &guint)
{
  *this = add(guint);
  return *this;
}

Guint operator+(const Guint &guint1, const Guint &guint2)
{
  return guint1.add(guint2);
}

Guint operator+(const Guint &guint1, u32 n)
{
  return guint1.add(n);
}

bool operator<(const Guint &guint1, Guint &guint2)
{
}

bool operator<(const Guint &guint1, u32 i)
{
}

bool operator<=(const Guint &guint1, u32 i)
{
  Guint g2(i);

  //cout << guint1.count() << ", " << g2.count() << endl;
  if (guint1.count() <= g2.count())
  {
    u32 cmp1 = guint1.data_[1] << 16 + guint1.data_[0];
    u32 cmp2 = g2.data_[1] << 16 + g2.data_[0];
    return (cmp1 <= cmp2);
  }
  else
  {
    return false;
  }
}

ostream& operator<<(ostream &os, const Guint &guint)
{
  //cout << "oo: " << guint.count() << endl;
  int i=guint.data_.size() - 1;

  for ( ; i >= 0 ; --i)
  {
    if (guint.data_[i] != 0)
      break;
  }

  if (i==-1)
  {
    os << "0";
    return os;
  }

  for ( ; i >= 0 ; --i)
  {
    if (guint.data_[i] == 0)
      os << "00";
    else
      os << guint.data_[i];
  }

  return os;
}

void mul(const Guint &guint1, const Guint &guint2)
{
  vector<u16> data;
  data.reserve(100);
  int i=0, j=0;
  u32 t = 0;
  cout << data.size() << endl;
  cout << data.capacity() << endl;

  for (i ; i < guint1.count() ; ++i)
  {
    u16 carry = 0;
    for (j ; j < guint2.count() ; ++j)
    {
      t = data[i+j] + guint1.data_[i] * guint2.data_[j] + carry;
      data[i+j] = t % 100;
      carry = t / 100;
      cout << "(" << i << "," << j << ")" << endl;


     
    }
    data[i+j] = carry;
  }
  #if 0
  for (int i=0 ; i < 10 ; ++i)
    cout << data[i] << endl;
  #endif

}
