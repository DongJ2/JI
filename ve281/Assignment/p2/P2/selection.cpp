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

int Rselect(int *a, int n, int i)
{
    srand((unsigned)time(NULL));
    int p=rand()%(n);
    int j=partition(a,n,p);
    if (j==i) return a[j];
    if (j>i) return Rselect(a, j, i);
    else return Rselect(a+j+1,n-j-1,i-j-1);

}

int partition(int *a, int n, int p)
{
    int i=1;
    int j=n-1;
    int tem;
    tem=a[p];
    a[p]=a[0];
    a[0]=tem;
    if (i==j)
    {
        if (a[0]>a[1]) {tem=a[1];a[1]=a[0];a[0]=tem;}
        else j--;
    }
    else while (i<j)
        {
            while ((i<n-1)&&(a[i]<a[0])) i++;
            while ((j>0)&&(a[j]>=a[0])) j--;
            if (i<j) {tem=a[i];a[i]=a[j];a[j]=tem;}
            else {tem=a[j];a[j]=a[0];a[0]=tem;}
        }
    return j;
}

int Dselect(int *a, int n, int i)
{
    if (n==1) return a[0];
    else
    {
        int C[(n-1)/5+1];
        int k=0, j=0;
        for (k;k<(n-1)/5;k++)
            C[k]=median(&a[k*5],5);
        C[k]=median(&a[k*5],n-5*k);
        int p=Dselect(&C[0],(n-1)/5+1,n/10);
        int p1;
        for (int m=0;m<n;m++)
        if (p==a[m]) {p1=m;break;}
        j=partition(a,n,p1);
        if (j==i) return a[j];
        if (j>i) return Dselect(a, j, i);
        else return Dselect(a+j+1,n-j-1,i-j-1);
    }
}

int median(int *a, int n)
{
    int tem,j;
    for (int i=1;i<n;i++)
    {
        tem=a[i];
        j=i-1;
        while ((j>-1)&&(tem<a[j]))
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=tem;
    }
    return a[(n-1)/2];
}
