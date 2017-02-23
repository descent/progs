#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>

typedef struct Queue_
{
#if 0
  public:
    bool push(char ch);
    bool pop(char &ch);
    int len() const {return len_;}
    int begin() const {return begin_;}
    int end() const {return end_;}
  private:
#endif
    char *q_;
    int len_;
    int begin_, end_;
}Queue;

#endif
