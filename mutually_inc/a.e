# 1 "a.cpp"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "a.cpp"
# 1 "a.h" 1



# 1 "b.h" 1



# 1 "a.h" 1
# 5 "b.h" 2

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
# 5 "a.h" 2


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
# 1 "a.cpp" 2
