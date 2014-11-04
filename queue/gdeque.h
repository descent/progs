/*
 * g: generic
 * gdeque: generic deque
 */

#ifndef GDEQUE_H
#define GDEQUE_H

#include <iostream>
using namespace std;
//namespace DS
//{

const int DEQUE_LEN = 30;

template <typename ElmType>
class Deque
{
  public:
    //explicit MyDeque();
    bool init()
    {
      len_ = DEQUE_LEN;
      begin_ = end_ = 0;
    }


    bool push_back(ElmType &ch)
    {
      if (ready() == false) 
        return false;
    // copy ch to begin point
    // ++begin

      bool ret = true;
      if (can_push())
      {
        *(q_ + begin_) = ch;
        begin_ = ((begin_ + 1) % len_);
      }
      else
        ret = false;
      return ret;
    }

    bool back(int i, ElmType &elm)
    {
      if (ready() == false) 
        return false;

      bool ret = true;

      int b = ((begin_ - i + len_) % len_);

      if (b == end())
      {
        ret = false;
      }
      else
      {
        elm = *(q_ + b - 1);
      }
      return ret;
    }
    bool pop_front()
    {
      ElmType ch;
      return pop_front(ch);
    }
    bool pop_front(ElmType &ch)
    {
      if (ready() == false) 
        return false;
    // return end point value, ++end
      bool ret = true;
      if (can_pop())
      {
        ch = *(q_ + end_);
        end_ = ((end_ + 1) % len_);
      }
      else
      {
        ret = false;
      }
      return ret;
    }

    bool push_front(int ch)
    {
      if (ready() == false) 
        return false;
      bool ret = true;

      // has space to push
      if (can_push())
      {
        end_ = ((end_ + len_ - 1) % len_);
        *(q_ + end_) = ch;
      }
      else
        ret = false;
      return ret;
    }

    bool pop_back(int &ch)
    {
      if (ready() == false) 
        return false;

      bool ret = true;
      if (can_pop())
      {
        begin_ = ((begin_ - 1) % len_);
        ch = *(q_ + begin_);
      }
      else
      {
        ret = false;
      }
      return ret;
    }

    int len() const {return len_;}
    int begin() const {return begin_;}
    int end() const {return end_;}
    bool print()
    {
#if 1
      cout << "begin: " << begin_ << endl;
      cout << "end: " << end_ << endl;
      if (ready() == false) return false;
      cout << "-- ";
      int e = end();
      for (int i=e ; i != begin() ; )
      {
        cout << *(q_ + i) << " ";
        i = (i + 1) % len_;
      }
      cout << " --" << endl;
      return true;
#endif
    }
    bool ready() const
    {
      //cout << "len_:" << len_ << endl;
      if (len_ > 1)
        return true;
      else
        return false;
    }
    bool full()
    {
      return (!can_push());
    }
    bool empty()
    {
      return (!can_pop());
    }
    bool can_push()
    {
      int next_begin = ((begin() + 1) % len_);
      if (next_begin == end())
        return false;
      else
        return true;
    }
    bool can_pop()
    {
      if (begin() == end())
        return false;
      else
        return true;
    }
  private:
    ElmType q_[DEQUE_LEN];
    int len_;
    int begin_, end_;
    int begin_front_, end_front_;
};

//}
#endif
