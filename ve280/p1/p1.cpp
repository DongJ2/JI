#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
using namespace std;
int IsFibonacci(long n);
int Issumofsquare(long n);
int Isrepeated(long n);
int Isdivisornumber(long n);
int main()
{
	int c;
	cout<<"Please enter the test choice:"<<endl;
	cin>>c;
	while ((c<1)||(c>4))
	{
		cout<<"Please enter the test choice"<<endl;
		cin>>c;
	}	
	long n;	
	cout<<"Please enter the number for test:"<<endl;
	cin>>n;
	while ((n<0)||(n>10000000)) 
	{
		cout<<"Please enter the number for test:"<<endl;
		cin>>n;
	}
	int k;
	switch (c)
	{
		case 1: k=IsFibonacci(n); if (k==0) cout<<"Fail"<<endl;else cout<<"Pass"<<endl;break;
		case 2: k=Issumofsquare(n); if (k==0) cout<<"Fail"<<endl;else cout<<"Pass"<<endl;break;
		case 3: k=Isrepeated(n); if (k==0) cout<<"Fail"<<endl;else cout<<"Pass"<<endl;break;
		case 4: k=Isdivisornumber(n); if (k==0) cout<<"Fail"<<endl;else cout<<"Pass"<<endl;break;
	}
	return 0;
}
int IsFibonacci(long n)
{
	int t,d;
	long F[40];
	F[0]=0;
	F[1]=1;
	t=1;
	d=0;
	if (n==0) d=1;
	else while (F[t]<=10000000)
		{
			if (F[t]==n) {d=1;break;}
			t++;
			F[t]=F[t-1]+F[t-2];				
		}
	if (d==0) return 0;
	else return 1;
};
int Issumofsquare(long n)
{
	int i,j,d,m;
	long s;
	d=0;
	for (i=1;i<=floor(sqrt(n));i++)
	{
		for (j=i;j<=floor(sqrt(n));j++)
		{
			s=0;
			for (m=i;m<=j;m++) s=s+m*m;
			if (s==n) {d=1;break;}
		}
		if (d==1) break;
	}
	if (d==0) return 0;
	else return 1;
};
int Isrepeated(long n)
{
	int l,p1,p2,p3,p4,p5,p6,p7;	
	if (n<10) l=1;
	if ((n>=10)&&(n<100)) l=2;
	if ((n>=100)&&(n<1000)) l=3;
	if ((n>=1000)&&(n<10000)) l=4;
	if ((n>=10000)&&(n<100000)) l=5;
	if ((n>=100000)&&(n<1000000)) l=6;
	if (n>=1000000) l=7;
	switch (l)
	{
		case 1: return 0;break;
		case 2: p1=n%10;p2=(n-p1)/10; if (p1==p2) return 1;else return 0; break;
		case 3: p1=n%10;p2=(n-p1)/10%10;p3=(n-p2*10-p1)/100; if ((p1==p2)&&(p1==p3)) return 1;else return 0; break;
		case 4: {p1=n%10;p2=(n-p1)/10%10;p3=(n-p2*10-p1)/100%10;p4=(n-p1-p2*10-p3*100)/1000;
			if ((p1==p2)&&(p2==p3)&&(p3==p4)) return 1;
			else 
			{
				p1=n%100;p2=(n-p1)/100;
				if (p1==p2) return 1;
				else return 0;
			}
			break;}
		case 5:{p1=n%10;p2=(n-p1)/10%10;
			p3=(n-p1-p2*10)/100%10;
			p4=(n-p1-p2*10-p3*100)/1000%10;
			p5=(n-p1-p2*10-p3*100-p4*1000)/10000;
			if ((p1==p2)&&(p2==p3)&&(p3==p4)&&(p4==p5)) return 1;
			else return 0;
			break;}
		case 6:{p1=n%10;p2=(n-p1)/10%10;
			p3=(n-p1-p2*10)/100%10;
			p4=(n-p1-p2*10-p3*100)/1000%10;
			p5=(n-p1-p2*10-p3*100-p4*1000)/10000%10;
			p6=(n-p1-p2*10-p3*100-p4*1000-p5*10000)/100000;
			if ((p1==p2)&&(p2==p3)&&(p3==p4)&&(p4==p5)&&(p5==p6)) return 1;
			else
			{
				p1=n%100;p2=(n-p1)/100%100;p3=(n-p1-p2*100)/10000;
				if ((p1==p2)&&(p2==p3)) return 1;
				else
				{
					p1=n%1000;p2=(n-p1)/1000;
					if (p1==p2) return 1;
					else return 0;
				}
			}
			break;}
		case 7:{p1=n%10;p2=(n-p1)/10%10;
			p3=(n-p1-p2*10)/100%10;
			p4=(n-p1-p2*10-p3*100)/1000%10;
			p5=(n-p1-p2*10-p3*100-p4*1000)/10000%10;
			p6=(n-p1-p2*10-p3*100-p4*1000-p5*10000)/100000%10;
			p7=(n-p1-p2*10-p3*100-p4*1000-p5*10000-p6*100000)/1000000%10;
			if ((p1==p2)&&(p2==p3)&&(p3==p4)&&(p4==p5)&&(p5==p6)&&(p6==p7)) return 1;
			else return 0;
			break;}
	}	
};
int Isdivisornumber(long n)
{
	long s,i;
	s=0;
	for (i=1;i<=n/2;i++)
	{
		if (n%i==0) s=s+i;
	}	
	if (n==s) return 1;
	else return 0;
};
