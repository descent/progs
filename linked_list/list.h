#ifndef LIST_H
#define LIST_H

//
typedef int NodeElm;

typedef struct Node_
{
  NodeElm elm;
  struct Node_ *next;
}Node;

Node *make_node(NodeElm elm);

void insert(Node *node);

void del(Node *node);

void search(NodeElm elm);

#endif
