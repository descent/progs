#ifndef GUINT_H
#define GUINT_H

#include <cctype>

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

#include "type.h"

const int NUM=5;


//namespace DS
//{

class Guint
{
  friend ostream & operator <<(ostream &os, const Guint &guint);
  friend Guint operator+(const Guint &guint1, const Guint &guint2);
  friend Guint operator+(const Guint &guint1, u32 n);
  friend bool operator<(const Guint &guint1, Guint &guint2);
  friend bool operator<(const Guint &guint1, u32 i);
  friend bool operator<=(const Guint &guint1, u32 i);
  public:
    Guint();
    Guint(u32 num);
    //Guint(const char *num);
    Guint(const std::string num);
    Guint(const vector<u16> data);

    Guint add(const Guint &guint) const;
    Guint add(u32 n) const;
    Guint operator++();
    Guint operator++(int);
    Guint operator+=(const Guint &guint);
    int count() const {return data_.size();}
  private:
    bool convert_to_cal_data(const std::string num);
    int idx_;
    //u16 carry_;
    vector<u16> data_;
};

//} //namespace DS

//ostream & operator <<(ostream &os, const DS::Guint &guint);
#endif
