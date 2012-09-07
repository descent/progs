#include "list.h"

Node::Node(int v)
{
  value_ = v;
}

void Node::del_next_node()
{
  if (next() == 0) return;
  Node *next_n = next();
  set_next(next_n->next());
  delete next_n;
}
