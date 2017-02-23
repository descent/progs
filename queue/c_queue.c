#include "c_queue.h"
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

// init: 
// begin_ = end_ = 0;
// q leave one empty space when full
int q_ctor(Queue *queue, int len)
{
  queue->len_ = len;
  if (queue->len_ > 1)
  {
    queue->len_ = len;
    queue->q_ = malloc(sizeof(char) * len);
    queue->begin_ = queue->end_ = 0;
  }
}

int q_dtor(Queue *queue)
{
  free(queue->q_);
}

int ready(Queue *queue) 
{
      //cout << "len_:" << len_ << endl;
  if (queue->len_ > 1)
    return TRUE;
  else
    return FALSE;
}

int can_push(Queue *queue)
{
  int next_begin = (queue->begin_ + 1) % queue->len_;
  if (next_begin == queue->end_)
    return FALSE;
  else
    return TRUE;
}

int can_pop(Queue *queue)
{
  if (queue->begin_ == queue->end_)
    return FALSE;
  else
    return TRUE;
}

int queue_push(Queue *queue, char ch)
{
  if (FALSE == ready(queue))
    return FALSE;
// copy ch to begin point
// ++begin

  int ret = TRUE;
  if (can_push(queue))
  {
    *(queue->q_ + queue->begin_) = ch;
    queue->begin_ = ((queue->begin_ + 1) % queue->len_);
  }
  else
    ret = FALSE;
  return ret;
}

int queue_pop(Queue *queue, char *ch)
{
  if (ready(queue) == FALSE) 
    return FALSE;
// return end point value, ++end
  int ret = TRUE;
  if (can_pop(queue))
  {
    *ch = *(queue->q_ + queue->end_);
    queue->end_ = ((queue->end_ + 1) % queue->len_);
  }
  else
  {
    ret = FALSE;
  }
  return ret;
}

int print_queue(Queue *queue)
{
  if (ready(queue) == FALSE) return FALSE;
  int e = queue->end_;
  for (int i=e ; i != queue->begin_ ; )
  {
    printf("%c ", *(queue->q_ + i));
    i = (i + 1) % queue->len_;
  }
  printf("\n");
  return TRUE;
}

#ifdef UNIT_TEST

#include <stdio.h>

int main(int argc, char *argv[])
{
  Queue q;
  q_ctor(&q, 5);

  printf("q len: %d\n", q.len_);
  printf("begin: %d\n", q.begin_);
  printf("push 'a'\n");
  queue_push(&q, 'a');
  printf("begin: %d\n", q.begin_);

  printf("push 'b'\n");
  queue_push(&q, 'b');
  printf("begin: %d\n", q.begin_);
  for (char i='1' ; i < '8' ; ++i)
  {
    printf("push %c ", i);
    if (TRUE == queue_push(&q, i))
    {
      printf("ok\n");
    }
    else
    {
      printf("push false\n");
    }
  }

  // pop 1 element
  for (int i=0 ; i < 1 ; ++i)
  {
    char pop_ch;
    if (TRUE == queue_pop(&q, &pop_ch))
    {
      printf("pop value: %c\n", pop_ch);
    }
    else
    {
      printf("pop fail\n");
    }

  }

  for (char i='1' ; i < '8' ; ++i)
  {
    printf("push %c ", i);
    if (TRUE == queue_push(&q, i))
    {
      printf("ok\n");
    }
    else
    {
      printf("push false\n");
    }
  }


  print_queue(&q);
  
  q_dtor(&q);
  return 0;
}

#endif
