#include "list.h"

#include <iostream>

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

int main()
{
  int data[] = {1,2,3,4,5};
  Node *head = new Node(0);
  Node *cur_n = head;

  for (int i=0 ; i < sizeof(data)/sizeof(int) ; ++i)
  {
    Node *n = new Node(data[i]);
    cur_n->set_next(n);
    cur_n = n;
  }
  cur_n->set_next(0);
  print(head);

  return 0;
}
