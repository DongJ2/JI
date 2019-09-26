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
   int n,m;
   cin>>m;
   cin>>n;
   int a[n];
   for (int i=0;i<n;i++) cin>>a[i];
   switch (m)
   {
       case 0: bubble(&a[0],n);break;
       case 1: insertion(&a[0],n);break;
       case 2: selection(&a[0],n);break;
       case 3: mergesort(&a[0],0,n-1);break;
       case 4: quick_extra(&a[0],0,n-1);break;
       case 5: quick_inplace(&a[0],0,n-1);break;
       default: cout<<"Wrong Input\n";
   }
   for (int i=0;i<n;i++) cout<<a[i]<<endl;
}
