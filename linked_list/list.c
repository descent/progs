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
}

void search(NodeElm elm)
{
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
  print_list();
  return 0;
}
