#ifndef T_H
#define T_H

class Hello
{
  public:
    Hello();
    ~Hello();
    inline int get_val() const
    {
      return val_;
    }
  private:
    int val_;
};

#endif
