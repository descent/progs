#include "list.h"

#include <iostream>

#include <cstdlib>

using std::cout;
using std::endl;

void print(Node *n)
{
  Node *cur_n = n;
  while(cur_n)
  {
    cout << cur_n->value() << " ";
    cur_n = cur_n->next();
  }
  cout << endl;
}

Node *create_list(int size)
{
  srand(time(0));

  Node *head = new Node(0);
  Node *cur_n = head;
  for (int i=0 ; i < size ; ++i)
  {
    int num = rand() % 1000;
    Node *n = new Node(num);
    cur_n->set_next(n);
    cur_n = n;
  }
  cur_n->set_next(0);
  return head; 
}

int main()
{
  const int size = 10;
  Node *head = create_list(size);

  print(head);
  head->del_next_node();
  print(head);
  head->add_next_node(new Node(11));
  print(head);

  return 0;
}
