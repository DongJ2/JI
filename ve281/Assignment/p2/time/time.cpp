#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <cassert>
#include "selection.h"
#include "sort.h"

using namespace std;

int main()
{
    srand((unsigned)time(NULL));
    int n,i,r,k,km;
    n=10;
    clock_t t[3];
    clock_t tem;
    r=0;
    while (n<=1000000)
    {
	long int *a0,*a1,*a2;
	a0=new long int [n];
	a1=new long int [n];
	a2=new long int [n];
	for (int j=0;j<n;j++) {a0[j]=mrand48();a1[j]=a0[j];a2[j]=a0[j];}
	k=0;
	switch (n)
	{
	    case 10: km=5;break;
	    case 50: km=10;break;
	    case 100: km=20;break;
	    case 500: km=50;break;
	    case 1000: km=50;break;
	    case 5000: km=100;break;
	    case 10000: km=500;break;
	    case 50000: km=1000;break;
	    case 100000: km=1000;break;
	    case 500000: km=1000;break;
	    case 1000000: km=1000;break;
	}
	while (k<km)
	{
	    i=rand()%n;
	    tem=clock();
	    Rselect(a0,n,i);
	    tem=clock()-tem;
	    t[0]=(k*t[0]+tem)/(k+1);
	    tem=clock();
	    Dselect(a1,n,i);
	    tem=clock()-tem;
	    t[1]=(k*t[1]+tem)/(k+1);
	    tem=clock();
	    quick_inplace(a2,0,n-1);
	    tem=clock()-tem;
	    t[2]=(k*t[2]+tem)/(k+1);
	    k++;
	}
	cout<<endl<<"Input size is "<<n<<endl;
	cout<<"Rselect:\t"<<t[0]<<endl;
	cout<<"Dselect:\t"<<t[1]<<endl;
	cout<<"Quicksort\t"<<t[2]<<endl;
	if (r%2==0) n=n*5;
	else n=n*2;
	r++;
	delete [] a0;
	delete [] a1;
	delete [] a2;
    }
}
