#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <cassert>
#include "sort.h"

using namespace std;

int main()
{
    srand((unsigned)time(NULL));
    string name[6];
    name[0]="bubble   ";
    name[1]="insertion";
    name[2]="selection";
    name[3]="merge    ";
    name[4]="quick_ex ";
    name[5]="quick_in ";
    int n=10;
    clock_t t[6];
    clock_t tem;
    int s,r;
    int round=0;
    while (round<9)
    {
    long int *a0,*a1,*a2,*a3,*a4,*a5;
    a0=new long int [n];
    a1=new long int [n];
    a2=new long int [n];
    a3=new long int [n];
    a4=new long int [n];
    a5=new long int [n];
    for (int i=0;i<6;i++) t[i]=0;
    s=0;
    r=0;
    while (r<50)
    {
	  for (int i=0;i<n;i++) {a0[i]=mrand48();a1[i]=a0[i];a2[i]=a0[i];a3[i]=a0[i];a4[i]=a0[i];a5[i]=a0[i];}
	  while (s<6)
	  {
	      tem=clock();
	      switch (s)
	      {
		  case 0: bubble(&a0[0],n);break;
		  case 1: insertion(&a1[0],n);break;
		  case 2: selection(&a2[0],n);break;
		  case 3: mergesort(&a3[0],0,n-1);break;
		  case 4: quick_extra(&a4[0],0,n-1);break;
		  case 5: quick_inplace(&a5[0],0,n-1);break;
	      }
	      tem=clock()-tem;
	      t[s]=(r*t[s]+tem)/(r+1);
              s++;
	  }
	  r++;
    }
    cout<<endl<<"Input size is "<<n<<endl;
    for (int i=0;i<6;i++) cout<<name[i]<<":\t"<<t[i]<<" CLOCK_PER_SEC"<<endl;
    delete [] a0;
    delete [] a1;
    delete [] a2;
    delete [] a3;
    delete [] a4;
    delete [] a5;
    if (round%2==0) n=n*5;
    else n=n*2;
    round++;
    }
}
