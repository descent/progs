#ifndef LIST_H
#define LIST_H

class Node
{
  public:
    Node(int v);
    void set_next(Node *n){next_ = n;}
    Node *next() const {return next_;}
    void add_next_node(Node *n){set_next(n);};
    void del_next_node();
    int value() const{return value_;}
  private:
    int value_;
    Node *next_;
};

#endif
