#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <fstream>

using namespace std;

void adder(int *a, int *b, int *c)
{
    int carry[17];
    carry[0]=0;
    for (int i=0;i<8;i++)
    {
        c[i]=(a[i]+b[i]+carry[i])%2;
        carry[i+1]=(a[i]+b[i]+carry[i])/2;
    }
    carry[4]=0;
    for (int i=4;i<8;i++) carry[i+1]=(a[i]+b[i]+carry[i])/2;
    for (int i=8;i<12;i++)
    {
        c[i]=(a[i]+b[i]+carry[i])%2;
        carry[i+1]=(a[i]+b[i]+carry[i])/2;
    }
    carry[8]=0;
    for (int i=8;i<12;i++) carry[i+1]=(a[i]+b[i]+carry[i])/2;
    for (int i=12;i<16;i++)
    {
        c[i]=(a[i]+b[i]+carry[i])%2;
        carry[i+1]=(a[i]+b[i]+carry[i])/2;
    }
    c[16]=carry[16];
}

void fact(int *a, int n, int len)
{
    for (int i=len-1;i>=0;i--)
    {
        if ((int)pow(2,i)<=n) {a[i]=1;n=n-(int)pow(2,i);}
            else a[i]=0;
    }
}

int main()
{
    int num1[16],num2[16],num3[17];
    int num;
    int t=0;
    ofstream iFile;
    iFile.open("errordistribution.txt");
    for (int i=0;i<2000;i++)
    {
        fact(&num1[0],i,16);
        for (int j=0;j<2000;j++)
        {
            fact(&num2[0],j,16);
            adder(&num1[0],&num2[0],&num3[0]);
            num=0;
            for (int k=0;k<17;k++)
                if (num3[k]==1) num=num+(int)pow(2,k);
            if (i+j!=num)
            {
                t++;
                iFile<<i<<" "<<j<<" "<<num<<endl;
            }
        }
    }
    iFile.close();
    cout<<t<<endl;
}
