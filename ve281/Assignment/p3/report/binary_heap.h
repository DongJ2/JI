#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <algorithm>
#include "priority_queue.h"

// OVERVIEW: A specialized version of the 'heap' ADT implemented as a binary
//           heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class binary_heap: public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  binary_heap(COMP comp = COMP());

  // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(log(n))
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: O(log(n))
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

    void percolateup(int id);

    void percolatedown(int id);

private:
  // Note: This vector *must* be used in your heap implementation.
  std::vector<TYPE> data;
  // Note: compare is a functor object
  COMP compare;

private:
  // Add any additional member functions or data you require here.
};

template<typename TYPE, typename COMP>
binary_heap<TYPE, COMP> :: binary_heap(COMP comp) {
    compare = comp;
    // Fill in the remaining lines if you need.
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP> :: enqueue(const TYPE &val) {
    // Fill in the body.
    if (data.size()==0) data.push_back(val);
    data.push_back(val);
    percolateup(data.size()-1);
}

template<typename TYPE, typename COMP>
TYPE binary_heap<TYPE, COMP> :: dequeue_min() {
    // Fill in the body.
    int id=data.size();
    if (id>1)
    {
        TYPE tem=data[1];
        data[1]=data[id-1];
        data[id-1]=tem;
        data.pop_back();
        percolatedown(1);
        return tem;
    }
}

template<typename TYPE, typename COMP>
const TYPE &binary_heap<TYPE, COMP> :: get_min() const {
    // Fill in the body.
    if (data.size()>1) return data[1];
}

template<typename TYPE, typename COMP>
bool binary_heap<TYPE, COMP> :: empty() const {
    // Fill in the body.
    if (data.size()<2) return true;
    else return false;
}

template<typename TYPE, typename COMP>
unsigned binary_heap<TYPE, COMP> :: size() const {
    // Fill in the body.
    if (data.size()==0) return 0;
    else return data.size()-1;
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>:: percolateup(int id)
{
    TYPE tem;
    while (id>1 && compare(data[id],data[id/2]))
    {
        tem=data[id];
        data[id]=data[id/2];
        data[id/2]=tem;
        id=id/2;
    }

}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::percolatedown(int id)
{
    TYPE tem;
    int size=data.size()-1;
    for (int j=2*id;j<=size;j=2*id)
    {
        if (j<size && compare(data[j+1],data[j])) j++;
        if (compare(data[id],data[j])) break;
        tem=data[id];
        data[id]=data[j];
        data[j]=tem;
        id=j;
    }
}

#endif //BINARY_HEAP_H
