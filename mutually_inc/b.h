#ifndef B_H
#define B_H

#include "a.h"

template <typename Type> class list;


template <typename Type>
class vec
{
  public:
    vec()
    {
      list<int> l;
    }
    ~vec(){}
};
#endif
