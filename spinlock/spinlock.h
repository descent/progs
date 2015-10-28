#ifndef SPINLOCK_H
#define SPINLOCK_H

typedef struct 
{
  int val_;
}Atomic;


typedef Atomic Spinlock;

typedef unsigned int u32;
typedef unsigned int u16;

#define TICKET_SHIFT    16


#define barrier() __asm__ __volatile__("": : :"memory")



typedef struct {
        union {
                u32 lock;
                struct __raw_tickets {
#ifdef __ARMEB__
                        u16 next;
                        u16 owner;
#else
                        u16 owner;
                        u16 next;
#endif
                } tickets;
        };
} arch_spinlock_t;


// #define PTHREAD_FUNC

#endif
