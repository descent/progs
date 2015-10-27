#ifndef SPINLOCK_H
#define SPINLOCK_H

typedef struct 
{
  int val_;
}Atomic;


typedef Atomic Spinlock;

#endif
