#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <algorithm>
#include <cmath>
#include "priority_queue.h"
#include <iostream>

using namespace std;


// OVERVIEW: A specialized version of the 'heap' ADT implemented as a
//           Fibonacci heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class fib_heap: public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  fib_heap(COMP comp = COMP());

// EFFECTS: Deconstruct the heap with no memory leak.
  // MODIFIES: this
  // RUNTIME: O(n)
  ~fib_heap();

  // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(1)
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: Amortized O(log(n))
  virtual TYPE dequeue_min();

  // EFFECTS: Return the smallest element of the heap.
  // REQUIRES: The heap is not empty.
  // RUNTIME: O(1)
  virtual const TYPE &get_min() const;

  // EFFECTS: Get the number of elements in the heap.
  // RUNTIME: O(1)
  virtual size_type size() const;

  // EFFECTS: Return true if the heap is empty.
  // RUNTIME: O(1)
  virtual bool empty() const;

private:
  // Note: compare is a functor object
  COMP compare;

private:
  // Add any additional member functions or data you require here.
  // You may want to define a strcut/class to represent nodes in the heap and a
  // pointer to the min node in the heap.
    struct node
    {
        TYPE key;
        node *parent;
        node *child;
        node *left;
        node *right;
        int degree;
        bool mark;
    };

    int n;
    node *min;

    void Consolidate();
};

// Add the definitions of the member functions here. Please refer to
template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP> :: fib_heap(COMP comp) {
    compare = comp;
    min=NULL;
    n=0;
    // Fill in the remaining lines if you need.
}

template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP>::~fib_heap()
{
    while (n>0)
    {
        n--;
        dequeue_min();
    }
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP>::enqueue(const TYPE &val)
{
    node *np=new node;
    np->key=val;
    np->degree=0;
    np->mark=false;
    np->parent=NULL;
    np->child=NULL;
    np->left=NULL;
    np->right=NULL;
    if (min==NULL)
    {
        min=np;
        min->right=min;
        min->left=min;
        n=1;
    }
    else
    {
        min->right->left=np;
        np->right=min->right;
        np->left=min;
        min->right=np;
        n++;
        if (compare(np->key,min->key)) min=np;
    }
}

template<typename TYPE, typename COMP>
TYPE fib_heap<TYPE, COMP>::dequeue_min()
{
    node *np=min;
    TYPE tem;
    if (min!=NULL)
    {
        node *np1=np->child;
        node *np2,*np3;
        if (np1!=NULL)
        {
            np2=np1->right;
            np1->parent=NULL;
            min->right->left=np1;
            np1->right=min->right;
            np1->left=min;
            min->right=np1;
            while (np2!=np1)
            {
                np3=np2->right;
                np2->parent=NULL;
                min->right->left=np2;
                np2->right=min->right;
                np2->left=min;
                min->right=np2;
                np2=np3;
            }
        }
        np->right->left=np->left;
        np->left->right=np->right;
        if (np==np->right)
            min=NULL;
        else
        {
            min=np->right;
            Consolidate();
        }
        n--;
        tem=np->key;
        delete np;
        return tem;
    }
}

template<typename TYPE, typename COMP>
const TYPE &fib_heap<TYPE, COMP>::get_min() const {
    if (n>0) return min->key;
}

template<typename TYPE, typename COMP>
bool fib_heap<TYPE, COMP> :: empty() const {
    // Fill in the body.
    if (n==0) return true;
    else return false;
}

template<typename TYPE, typename COMP>
unsigned fib_heap<TYPE, COMP> :: size() const {
    // Fill in the body.
    return n;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP>::Consolidate()
{
    int D=log(n)/log((1+sqrt(5))/2)+1;
    node *A[D];
    for (int i=0;i<D;i++) A[i]=NULL;
    A[min->degree]=min;
    int t=1;
    node *np=min->right;
    while (np!=min)
    {
        t++;
        np=np->right;
    }
    node *root[t];
    np=min;
    int k=0;
    while (k<t)
    {
        root[k]=np;
        np=np->right;
        k++;
    }
    k=1;
    node *x,*y,*tem;
    int d;
    while (k<t)
    {
        x=root[k];
        d=x->degree;
        k++;
        while (A[d]!=NULL)
        {
            y=A[d];
            if (compare(y->key,x->key))
            {
                tem=y;
                y=x;
                x=tem;
            }
            y->left->right=y->right;
            y->right->left=y->left;
            y->parent=x;
            x->degree++;
            y->mark=false;
            if (x->child==NULL)
            {
                x->child=y;
                y->left=y;
                y->right=y;
            }
            else
            {
                x->child->right->left=y;
                y->right=x->child->right;
                y->left=x->child;
                x->child->right=y;
            }
            A[d]=NULL;
            d++;
        }
        A[d]=x;
    }
    min=NULL;
    for (int i=0;i<D;i++)
    {
        if (A[i]!=NULL)
        {

            if (min==NULL)
            {
                min=A[i];
                min->left=min;
                min->right=min;
            }
            else
            {
                min->right->left=A[i];
                A[i]->right=min->right;
                A[i]->left=min;
                min->right=A[i];
                if (compare(A[i]->key,min->key))
                    min=A[i];
            }
        }
    }
}
#endif //FIB_HEAP_H
