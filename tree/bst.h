#ifndef BST_H
#define BST_H

#ifdef USE_OS
#include <cstdio>
#include <cstdlib>

#include <string>
#include <iostream>
#include <map>

using namespace std;
#else

#include "myiostream.h"
#include "k_stdio.h"
using namespace DS;

#endif

#include "coroutine.h"

// GNode: G - generic
template <typename Key, typename Value>
struct GNode
{
  int e_;
  GNode *l_, *r_;
  Key k_;
  Value v_;
  GNode()
  {
    r_ = l_ = 0;
  }
  #if 1
  GNode(const Key &k, const Value &v):k_(k), v_(v)
  {
    r_ = l_ = 0;
  }
  #endif
  ~GNode()
  {
    // cout << "~GNode" << endl;
  }
};

template <typename NodeType, typename Key, typename Value>
NodeType *make_node(const Key &k, Value v)
{
  //cout << sizeof(NodeType) << endl;
  //NodeType *n = (NodeType*)malloc(sizeof(NodeType));
  //(n->k_).string("abc");
  NodeType *n = new NodeType;
  //cout << "sizeof(NodeType): " << sizeof(NodeType) << endl;
  if (n)
  {
    n->k_ = k;
    n->v_ = v;
    n->r_ = n->l_ = 0;
  }
  #if 0
#ifndef USE_OS
  else
  {
    THROW(NOFREE_MEM);
  }
#endif
  #endif
  return n;
}

template <typename NodeType>
void free_node(NodeType *n)
{
  delete n;
}

template <typename NodeType, typename Key, typename Value>
NodeType *insert(NodeType *t, const Key &k, Value v)
{
  if (t==0)
    return make_node<NodeType>(k, v);
  else if (t->k_ > k)
         t->l_ = insert(t->l_, k, v);
       else
         t->r_ = insert(t->r_, k, v);
  return t;
}

template <typename NodeType, typename Key>
NodeType* del(NodeType *n, const Key &k)
{
  NodeType *p;

  if (n==0)
    return 0;
  if (n->k_ > k)
    n->l_ = del(n->l_, k);
  else if (n->k_ < k)
         n->r_ = del(n->r_, k);
       else
       {
         if (n->l_ == 0 && n->r_ == 0)
         {
           free_node(n);
           n = 0;
         }
         else if (n->l_) // it has left subtree
              {
	        for (p = n->l_; p->r_; p = p->r_);

	        n->k_ = p->k_;
	        n->v_ = p->v_;
	        n->l_ = del(n->l_, n->k_);
              }
              else // it has right subtree
              {
	        for (p = n->r_; p->l_; p = p->l_);

	        n->k_ = p->k_;
	        n->v_ = p->v_;
	        n->r_ = del(n->r_, n->k_);
              }
       }
  return n;
}

template <typename NodeType, typename Key>
NodeType *search (NodeType *n, const Key &k)
{
  if (n==0)
    return 0;
  if (n->k_ > k)
    return search(n->l_, k);
  if (n->k_ < k)
    return search(n->r_, k);

  return n; // n->k_ == k
}

#if 1
// ref: http://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html
// ref: http://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/
/* Function to traverse binary tree without recursion and 
   without stack */
template <typename NodeType>
NodeType* morris_traversal(NodeType *root)
{
  static NodeType *current,*pre;
  scrBegin;
 
  if(root == 0)
     return 0; 
 
  current = root;
  while(current != 0)
  {                 
    if(current->l_ == 0)
    {
      //printf(" %f ", current->k_);
      //return current;
      scrReturn(current);
      current = current->r_;
    }    
    else
    {
      /* Find the inorder predecessor of current */
      pre = current->l_;
      while(pre->r_ != 0 && pre->r_ != current)
        pre = pre->r_;
 
      /* Make current as right child of its inorder predecessor */
      if(pre->r_ == 0)
      {
        pre->r_ = current;
        current = current->l_;
      }
             
      /* Revert the changes made in if part to restore the original 
        tree i.e., fix the right child of predecssor */   
      else 
      {
        pre->r_ = 0;
        //printf(" %f ", current->k_);
        //return current;
        scrReturn(current);
        current = current->r_;      
      } /* End of if condition pre->right == NULL */
    } /* End of if condition current->left == NULL*/
  } /* End of while */
  scrFinish(0);
  return 0;
}
#endif

template <typename NodeType>
void print_tree(NodeType *t)
{
  if (t)
  {
    cout << "(" << t->k_;
    //printf("(%f", t->k_);
    print_tree(t->l_);
    print_tree(t->r_);
    cout << ")";
  }
  else
  {
    printf("()");
  }
}

#endif
