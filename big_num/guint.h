#ifndef GUINT_H
#define GUINT_H

#include "type.h"

const int NUM=5;

namespace DS
{

class Guint
{
  public:
    Guint(const char *num);
  private:
    u16 data_[NUM];
    int idx_;
};

} //namespace DS
#endif
