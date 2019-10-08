#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

void add(int *a, int *b, int *c)
{
    int carry[9];
    carry[0]=0;
    for (int i=0;i<6;i++)
    {
        c[i]=(a[i]+b[i]+carry[i])%2;
        carry[i+1]=(a[i]+b[i]+carry[i])/2;
    }
    carry[2]=0;
    for (int i=2;i<6;i++)
    {
        carry[i+1]=(a[i]+b[i]+carry[i])/2;
    }
    c[6]=(a[6]+b[6]+carry[6])%2;carry[7]=(a[6]+b[6]+carry[6])/2;
    c[7]=(a[7]+b[7]+carry[7])%2;carry[8]=(a[7]+b[7]+carry[7])/2;
    c[8]=(a[8]+carry[8])%2;c[9]=(a[8]+carry[8])/2;
}

void fact(int *a, int n,int j)
{
    for (int i=j-1;i>=0;i--)
    {
        if ((int)pow(2,i)<=n) {a[i]=1;n=n-(int)pow(2,i);}
            else a[i]=0;
    }
}

int main()
{
    int n=8;
    int a[9],b[8],c[10];
    int num;
    int s=0;
    for (int i=0;i<512;i++)
        for (int j=0;j<256;j++)
    {
        fact(&a[0],i,9);
        fact(&b[0],j,8);
        add(&a[0],&b[0],&c[0]);
        num=0;
        for (int k=0;k<10;k++) if (c[k]==1) num=num+(int)pow(2,k);
        if (i+j!=num)
        {
            s++;
            cout<<i<<" "<<j<<" "<<i+j<<" "<<num<<endl;
        }
    }
    cout<<s<<endl;
}
