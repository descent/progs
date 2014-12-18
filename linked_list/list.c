#include "list.h"

#include <stdlib.h>
#include <stdio.h>

Node *head = 0;
Node *tail = 0;

Node *make_node(NodeElm elm)
{
  Node *n = malloc(sizeof(Node));

  if (n)
  {
    n->elm = elm;
    n->next = 0;
  }
  return n;
}

void push_back(Node *node)
{
  if (node == 0) return;

  if (head == 0)
  {
    head = node;
  }
  else
  {
    tail->next = node;
  }

  tail = node;
}

void del(Node *node)
{
  if (node == head)
  {
    printf("del head\n");
    head = node->next;
    free(node);
  }
  else
  {
    Node *cur = head;
    Node *previous_node = 0;
    printf("del no head\n");
    while (cur != 0)
    {
      if (cur == node)
      {
        break;
      }
      previous_node = cur;
      cur = cur->next;
    }
    previous_node->next = node->next;
    free(node);
  }
}

Node* search(const NodeElm *elm)
{
  Node *cur = head; 

  for (; cur != 0 ; cur = cur->next)
  {
    if (*elm == cur->elm)
      return cur;
  }
  return 0;
}

void print_list()
{
  Node *n;

  for (n = head ; n ; n=n->next)
  {
    printf("%d\n", n->elm);
  }
}

int main(int argc, char *argv[])
{
  push_back(make_node(1));
  push_back(make_node(2));
  push_back(make_node(3));
  push_back(make_node(4));
  push_back(make_node(5));
  print_list();

  //NodeElm elm=1; // head
  //NodeElm elm=2; // middle
  NodeElm elm=5;   // tail
  Node *n = search(&elm);

  if (n)
  {
    printf("find n->elm: %d\n", n->elm);
    del(n);
  }
  else
  {
    printf("not found\n");
  }
  print_list();

  return 0;
}
