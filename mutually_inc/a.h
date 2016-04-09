#ifndef A_H
#define A_H

#include "b.h"


template <typename Type> class vec;


template <typename Type>
class list
{
  public:
    list()
    {
      vec<int> v;
    }
    ~list(){}
};
#endif
