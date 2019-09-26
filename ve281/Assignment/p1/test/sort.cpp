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

void bubble(int *a, int len)
{
    int tem;
    for (int i=len-2;i>=0;i--)
    {
        for (int j=0;j<=i;j++)
        {
            if (a[j]>a[j+1])
            {
                tem=a[j];
                a[j]=a[j+1];
                a[j+1]=tem;
            }
        }
    }
}

void insertion(int *a, int len)
{
    int tem,j;
    for (int i=1;i<len;i++)
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
}

void selection(int *a, int len)
{
    int tem,k;
    for (int i=0;i<len-1;i++)
    {
        k=i;
        for (int j=i+1;j<len;j++)
        {
            if (a[k]>a[j]) k=j;
        }
        tem=a[i];
        a[i]=a[k];
        a[k]=tem;
    }
}

void mergesort(int *a, int left, int right)
{
    if (left>=right) return;
    int mid=(left+right)/2;
    mergesort(a,left,mid);
    mergesort(a,mid+1,right);
    merge(a,left,mid,right);

}

void merge(int *a, int left, int mid, int right)
{
    int i,j,k;
    i=0;
    j=0;
    k=0;
    int sizeA, sizeB;
    sizeA=mid-left+1;
    sizeB=right-mid;
    int tem[sizeA+sizeB];
    while ((i<sizeA)&&(j<sizeB))
    {
        if (a[left+i]<=a[mid+1+j]) {tem[k]=a[left+i];i++;}
        else {tem[k]=a[mid+1+j];j++;}
        k++;
    }
    if (i==sizeA)
    {
        while (j<sizeB)
        {
            tem[k]=a[mid+1+j];
            j++;
            k++;
        }
    }
    else
    {
        while (i<sizeA)
        {
            tem[k]=a[left+i];
            i++;
            k++;
        }
    }
    for (i=0;i<sizeA+sizeB;i++)
        a[left+i]=tem[i];
}

void quick_extra(int *a, int left, int right)
{
    int pivotat;
    if (left>=right) return;
    pivotat=partition_ex(a,left,right);
    quick_extra(a,left,pivotat-1);
    quick_extra(a,pivotat+1,right);
}

void quick_inplace(int *a, int left, int right)
{
    int pivotat;
    if (left>=right) return;
    pivotat=partition_in(a,left,right);
    quick_inplace(a,left,pivotat-1);
    quick_inplace(a,pivotat+1,right);
}

int partition_ex(int *a, int left, int right)
{
    srand((unsigned)time(NULL));
    int p=rand()%(right-left+1)+left;
    int b[right-left+1];
    int l,r,tem;
    tem=a[left];
    a[left]=a[p];
    a[p]=tem;
    l=0;r=right-left;
    int i=left+1;
    while (l<r)
    {
        if (a[i]<a[left]) {b[l]=a[i];l++;}
        else {b[r]=a[i];r--;}
        i++;
    }
    b[l]=a[left];
    for (i=left;i<=right;i++)
        a[i]=b[i-left];
    return l+left;
}

int partition_in(int *a, int left, int right)
{
    srand((unsigned)time(NULL));
    int i=left+1, j=right;
    int p=rand()%(right-left+1)+left;
    int tem;
    cout<<left<<" "<<right<<" "<<p<<endl;
    for (int i=left;i<=right;i++) cout<<a[i]<<" ";
    cout<<endl;
    tem=a[p];
    a[p]=a[left];
    a[left]=tem;
    if (i==j)
    {
        if (a[left]>a[right]) {tem=a[right];a[right]=a[left];a[left]=tem;}
        else j--;
    }
    else while (i<j)
        {
            while ((i<right)&&(a[i]<a[left])) i++;
            while ((j>left)&&(a[j]>=a[left])) j--;
            if (i<j) {tem=a[i];a[i]=a[j];a[j]=tem;}
            else {tem=a[j];a[j]=a[left];a[left]=tem;}
        }
    cout<<j<<endl;
    for (int i=left;i<=right;i++) cout<<a[i]<<" ";
    cout<<endl;
    return j;
}
