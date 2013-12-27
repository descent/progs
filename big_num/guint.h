#ifndef GUINT_H
#define GUINT_H

#include <iostream>
using namespace std;

#include "type.h"

const int NUM=5;


//namespace DS
//{

class Guint
{
  friend ostream & operator <<(ostream &os, const Guint &guint);
  public:
    Guint(const char *num);
    Guint(const std::string num);
    Guint add(const Guint &guint);
  private:
    int idx_;
    u16 carry_;
    u16 data_[NUM]={0,0,0,0,0};
};

//} //namespace DS

//ostream & operator <<(ostream &os, const DS::Guint &guint);
#endif
