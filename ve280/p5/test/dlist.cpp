#include <cstdlib>
#include <iostream>
using namespace std;
template<class T>
Dlist<T>::Dlist()
{
    first=NULL;
    last=NULL;
}

template<class T>
Dlist<T>::Dlist(const Dlist &l)
{
    copyAll(l);
}

template<class T>
Dlist<T>::~Dlist()
{
    removeAll();
}

template<class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l)
{
    if (l.isEmpty()) removeAll();
    else copyAll(l);
}

template<class T>
bool Dlist<T>::isEmpty() const
{
    if (first==NULL) return true;
    else return false;
}

template<class T>
void Dlist<T>::insertFront(T *op)
{
    node *np=new node;
    np->next=first;
    np->prev=NULL;
    np->op=op;
    if (isEmpty())
    {
 	last=np;
	first=np;
    }
    else
    {
	first->prev=np;
	first=np;
    }
}

template<class T>
void Dlist<T>::insertBack(T *op)
{
    node *np=new node;
    np->next=NULL;
    np->prev=last;
    np->op=op;
    if (isEmpty())
    {
        first=np;
        last=np;
    }
    else
    {
        last->next=np;
	last=np;
    }
}

template<class T>
T* Dlist<T>::removeFront()
{
    node *np=first;
    T *t;
    if (first==NULL)
    {
        emptyList e;
        throw e;
    }
    else if (first->op==last->op)
         {
             t=first->op;
             first=NULL;
             last=NULL;
             delete np;
             return t;
         }
         else
         {
             t=first->op;
             first=first->next;
             first->prev=NULL;
             delete np;
             return t;
         }
}

template<class T>
T* Dlist<T>::removeBack()
{
    node *np=last;
    if (first==NULL)
    {
        emptyList e;
        throw e;
    }
    else if (first->op==last->op)
         {
            T* t;
            t=last->op;
            last=NULL;
            first=NULL;
            delete np;
            return t;
         }
         else
         {
             T* t;
             t=last->op;
             last=last->prev;
             last->next=NULL;
             delete np;
             return t;
         }
}

template<class T>
void Dlist<T>::copyAll(const Dlist &l)
{
    removeAll();
    node np;
    T *op;
    np=*l.first;
    while (np.next!=NULL)
    {
        op=np.op;
        insertBack(op);
        np=*np.next;
    }
}

template<class T>
void Dlist<T>::removeAll()
{
    while (!isEmpty())
    {
        T *op=removeFront();
        delete op;
    }
}









