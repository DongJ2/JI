#pragma GCC optimize(2)
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <cassert>
#include "selection.h"

using namespace std;

int main()
{
    int n,i;
    int k;
    cin>>k;
    cin>>n;
    cin>>i;
    int a[n];
    for (int j=0;j<n;j++) cin>>a[j];
    if (k==0) cout<<"The order-"<<i<<" item is "<<Rselect(&a[0],n,i)<<endl;
    else if (k==1 )cout<<"The order-"<<i<<" item is "<<Dselect(&a[0],n,i)<<endl;
    else cout<<"Wrong input\n";
}
