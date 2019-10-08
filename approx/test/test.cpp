#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <fstream>

using namespace std;

struct error
{
    int num1;
    int num2;
    int result;
};

void convolution(double *a, double *b,double *out,int n1,int n2)
{
    for (int i=0;i<n1;i++)
        for (int j=0;j<n2;j++)
            out[i+j]=a[i]*b[j]+out[i+j];
}

void eFF(double *c,double *e, double *a, double *b,struct error *E)
{
    double sum=0;
    for (int i=0;i<1536;i++)
    {
        e[E[i].result]=e[E[i].result]+a[E[i].num1]*b[E[i].num2];
        c[E[i].num1+E[i].num2]=c[E[i].num1+E[i].num2]-a[E[i].num1]*b[E[i].num2];
    }
}

void cFF(double *c, double *e)
{
    for (int i=0;i<512;i++)
        if (e[i]!=0)
    {
        c[i]=c[i]+e[i];
    }
}

void fact(int *a, int n,int j)
{
    for (int i=j-1;i>=0;i--)
    {
        if ((int)pow(2,i)<=n) {a[i]=1;n=n-(int)pow(2,i);}
            else a[i]=0;
    }
}

void add(int *a, int *b, int *c)
{
    int carry[8];
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
    c[7]=(a[7]+b[7]+carry[7])%2;c[8]=(a[7]+b[7]+carry[7])/2;
}

void add2(int *a, int *b, int *c)
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

void eFF2(double *c, double *e, double *a, double *b, struct error *E)
{
    double sum=0;
    for (int i=0;i<3072;i++)
    {
        e[E[i].result]=e[E[i].result]+a[E[i].num1]*b[E[i].num2];
        c[E[i].num1+E[i].num2]=c[E[i].num1+E[i].num2]-a[E[i].num1]*b[E[i].num2];
    }
}

int main()
{
    /*int n;
    double sum=0;
    int num1[9],num2[8],num3[10];
    int num;
    struct error E[1536];
    int t=0;
    for (int i=0;i<256;i++)
        for (int j=0;j<256;j++)
    {
        fact(&num1[0],i,8);
        fact(&num2[0],j,8);
        add(&num1[0],&num2[0],&num3[0]);
        num=0;
        for (int k=0;k<9;k++) if (num3[k]==1) num=num+(int)pow(2,k);
        if (i+j!=num)
        {
            E[t].num1=i;E[t].num2=j;E[t].result=num;
            t++;
        }
    }
    struct error E2[3072];
    t=0;
    for (int i=0;i<512;i++)
        for (int j=0;j<256;j++)
    {
        fact(&num1[0],i,9);
        fact(&num2[0],j,8);
        add2(&num1[0],&num2[0],&num3[0]);
        num=0;
        for (int k=0;k<10;k++) if(num3[k]==1) num=num+(int)pow(2,k);
        if (i+j!=num)
        {
            E2[t].num1=i;E2[t].num2=j;E2[t].result=num;
            t++;
        }
    }
    double a[256],b[256],c[256];
    double c1[512],c2[768],e1[512],e2[768],e_tem[768];
    for (int i=0;i<512;i++) {c1[i]=0;c2[i]=0;e1[i]=0;e2[i]=0;e_tem[i]=0;}
    for (int i=512;i<768;i++) {c2[i]=0;e2[i]=0;e_tem[i]=0;}
    double a_bit[8][2],b_bit[8][2],c_bit[8][2];
    for (int i=0;i<8;i++) {cin>>a_bit[i][1];a_bit[i][0]=1-a_bit[i][1];}
    for (int i=0;i<8;i++) {cin>>b_bit[i][1];b_bit[i][0]=1-b_bit[i][1];}
    for (int i=0;i<8;i++) {cin>>c_bit[i][1];c_bit[i][0]=1-c_bit[i][1];}
    int bit[8];
    for (int i=0;i<256;i++)
    {
        fact(&bit[0],i,8);
        a[i]=1;b[i]=1;c[i]=1;
        for (int j=0;j<8;j++)
        {
            a[i]=a[i]*a_bit[j][bit[j]];
            b[i]=b[i]*b_bit[j][bit[j]];
            c[i]=c[i]*c_bit[j][bit[j]];
        }
    }
    convolution(&a[0],&b[0],&c1[0],256,256);
    eFF(&c1[0],&e1[0],&a[0],&b[0],&E[0]);
    ofstream iFile;
    iFile.open("result1.txt");
    for (int i=0;i<512;i++) {iFile<<i<<" "<<c1[i]<<" "<<e1[i]<<endl;}
    iFile.close();
    convolution(&c1[0],&c[0],&c2[0],512,256);
    convolution(&e1[0],&c[0],&e_tem[0],512,256);
    eFF2(&c2[0],&e2[0],&c1[0],&c[0],&E2[0]);
    eFF2(&e_tem[0],&e2[0],&e1[0],&c[0],&E2[0]);
    for (int i=0;i<768;i++)
    {
        if (e_tem[i]!=0) e2[i]=e2[i]+e_tem[i];
    }
    ofstream iFile1;
    iFile1.open("result2.txt");
    sum=0;
    for (int i=0;i<768;i++) {iFile1<<i<<" "<<c2[i]<<" "<<e2[i]<<endl;sum=sum+c2[i]+e2[i];}
    iFile1.close();
    cout<<sum<<endl;
    sum=0;
    for (int i=0;i<768;i++)
        if (e2[i]!=0) {sum=sum+e2[i];}
    cout<<sum<<endl;*/
    double a_bit[8][2],b_bit[8][2];
    double a[256],b[256];
    for (int i=0;i<8;i++) {cin>>a_bit[i][1];a_bit[i][0]=1-a_bit[i][1];}
    for (int i=0;i<8;i++) {cin>>b_bit[i][1];b_bit[i][0]=1-b_bit[i][1];}
    int bit[8];
    for (int i=0;i<256;i++)
    {
        fact(&bit[0],i,8);
        a[i]=1;b[i]=1;
        for (int j=0;j<8;j++)
        {
            a[i]=a[i]*a_bit[j][bit[j]];
            b[i]=b[i]*b_bit[j][bit[j]];
        }
    }
    for (int i=0;i<16;i++) cout<<i<<" "<<a[i]<<" ";
    cout<<endl;
    for (int i=0;i<16;i++) cout<<i<<" "<<b[i]<<" ";
    cout<<endl;
}
