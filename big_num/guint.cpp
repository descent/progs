#include "guint.h"

#include <cstdio>
#include <string>


Guint::Guint(const std::string num)
  : idx_(0), carry_(0)
{
  string n(num);
  idx_ = 0;
  string sub_str;
  int i;
  for (i=n.size()-5 ; i >= 0 ; i-=5)
  {
    cout << "i: " << i << endl;
    string sub_str = n.substr(i, 5);
    data_[idx_] = strtol(sub_str.c_str(), NULL, 10);
    ++idx_;
    //cout << "xx : " << sub_str << endl;
  }

  cout << "i: " << i << endl;
  sub_str = n.substr(0, i+5);
  //cout << "xx : " << sub_str << endl;
  data_[idx_] = strtol(sub_str.c_str(), NULL, 10);
}

Guint::Guint(const char *num)
  : idx_(0), carry_(0)
{
  string n(num);
  idx_ = 0;
  string sub_str;
  int i;
  for (i=n.size()-5 ; i >= 0 ; i-=5)
  {
    cout << "i: " << i << endl;
    string sub_str = n.substr(i, 5);
    data_[idx_] = strtol(sub_str.c_str(), NULL, 10);
    ++idx_;
    //cout << "xx : " << sub_str << endl;
  }

  cout << "i: " << i << endl;
  sub_str = n.substr(0, i+5);
  //cout << "xx : " << sub_str << endl;
  data_[idx_] = strtol(sub_str.c_str(), NULL, 10);
}

Guint Guint::add(const Guint &guint)
{
  for (int i=0 ; i < NUM ; ++i)
  {


  }
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
