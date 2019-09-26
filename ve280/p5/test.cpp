#include <iostream>
#include "dlist.h"

using namespace std;

struct com
{
	int r;
	int c;
};

int main()
{
	Dlist<com> c1,c2;
	com a,b;
	com *a1,*b1;
	a1=&a;b1=&b;
	cin>>a.r>>a.c;
	com *num=new com;
	num->r=a.r;num->c=a.c;
	c1.insertFront(num);
	c2=c1;
	b1=c2.removeFront();
	cout<<b1->r<<" "<<b1->c<<endl;
}
