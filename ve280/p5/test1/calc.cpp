#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "dlist.h"

using namespace std;

struct complexinteger
{
    int real;
    int imag;
};

int main()
{
    Dlist<complexinteger> c,c1;
    string s,real,imag;
    complexinteger *com;
    complexinteger a,b;
    istringstream iStream;
    bool input;
    int i=0;
    int l,j,sum,t,ar;
    sum=0;
    t=0;
    cin>>s;
    input=true;
    while (s!="q")
    {
        a.real=0;a.imag=0;
	b.real=0;b.imag=0;
        real="";
        imag="";
        l=s.size();
        if (l==1)
        {
            if (s=="+")
            {
                if (sum<2) cout<<"Not enough operands\n";
                else
                {
                    com=c.removeFront();
		    a.real=com->real;a.imag=com->imag;
		    delete com;
		    com=NULL;
                    com=c.removeFront();
		    b.real=com->real;
		    b.imag=com->imag;
		    delete com;
		    com=NULL;
		    a.real=a.real+b.real;
		    a.imag=a.imag+b.imag;
		    complexinteger *num=new complexinteger;
		    num->real=a.real;num->imag=a.imag;
		    c.insertFront(num);sum--;
                }
            }
            else if (s=="-")
            {
                if (sum<2) cout<<"Not enough operands\n";
                else
                {
                    com=c.removeFront();
		    a.real=com->real;a.imag=com->imag;
		    delete com;
		    com=NULL;
                    com=c.removeFront();
		    b.real=com->real;
		    b.imag=com->imag;
		    delete com;
		    com=NULL;
		    a.real=b.real-a.real;
		    a.imag=b.imag-a.imag;
		    complexinteger *num=new complexinteger;
		    num->real=a.real;num->imag=a.imag;
		    c.insertFront(num);sum--;
                }
            }
            else if (s=="*")
            {
                if (sum<2) cout<<"Not enough operands\n";
                else
                {
                    com=c.removeFront();
		    a.real=com->real;a.imag=com->imag;
		    delete com;
		    com=NULL;
                    com=c.removeFront();
		    b.real=com->real;
		    b.imag=com->imag;
		    delete com;
		    com=NULL;
		    ar=a.real;
		    a.real=a.real*b.real-a.imag*b.imag;
		    a.imag=ar*b.imag+a.imag*b.real;
		    complexinteger *num=new complexinteger;
		    num->real=a.real;num->imag=a.imag;
		    c.insertFront(num);sum--;
                }
            }
            else if (s=="n")
            {
                if (c.isEmpty()) cout<<"Not enough operands\n";
                else
                {
                    com=c.removeFront();
		    complexinteger *num=new complexinteger;
		    num->real=-com->real;
		    num->imag=-com->imag;
		    c.insertFront(num);
		    delete com;
		    com=NULL;
                }
            }
            else if (s=="d")
            {
                if (c.isEmpty()) cout<<"Not enough operands\n";
                else
                {
                    com=c.removeFront();
		    complexinteger *num=new complexinteger;
		    num->real=com->real;num->imag=com->imag;
                    c.insertFront(num);
		    complexinteger *num1=new complexinteger;
		    num1->real=com->real;num1->imag=com->imag;
		    delete com;
		    com=NULL;
                    c.insertFront(num1);
		    sum++;
                }
            }
            else if (s=="r")
            {
                if (sum<2) cout<<"Not enough operands\n";
                else
                {
                    com=c.removeFront();
                    a.real=com->real;a.imag=com->imag;
		    delete com;
		    com=NULL;
		    com=c.removeFront();
		    b.real=com->real;b.imag=com->imag;
		    delete com;
		    com=NULL;
		    complexinteger *num=new complexinteger;
		    num->real=a.real;num->imag=a.imag;
		    c.insertFront(num);
		    complexinteger *num1=new complexinteger;
		    num1->real=b.real;num1->imag=b.imag;
		    c.insertFront(num1);
                }
            }
            else if (s=="p")
            {
                if (c.isEmpty()) cout<<"Not enough operands\n";
                else
                {
                    com=c.removeFront();
                    cout<<com->real;
                    if (com->imag<0) cout<<com->imag<<"i"<<endl;
                    else cout<<"+"<<com->imag<<"i"<<endl;
		    complexinteger *num=new complexinteger;
		    num->real=com->real;num->imag=com->imag;
                    c.insertFront(num);
		    delete com;
		    com=NULL;
                }
            }
            else if (s=="c")
            {
                c=c1;
		sum=0;
            }
            else if (s=="a")
            {
		if (c.isEmpty()) cout<<endl;
		else
		{                
		    while (t<sum)
                    {
                        com=c.removeFront();
                        if (com->imag<0) cout<<com->real<<com->imag<<"i ";
                        else cout<<com->real<<"+"<<com->imag<<"i ";
		        complexinteger *num=new complexinteger;
		        num->real=com->real;num->imag=com->imag;
                        c.insertBack(num);
		    	delete com;
		    	com=NULL;
		        t++;
                    }
                    cout<<endl;
		    t=0;
		}
            }
            else cout<<"Bad input\n";
        }
        else
        {
            if (s[0]=='-') i++;
            while ((s[i]!='+')&&(s[i]!='-'))
            {
		if (i==l) {cout<<"Bad input\n";input=false;break;}
                if ((s[i]=='0')||(s[i]=='1')||(s[i]=='2')||(s[i]=='3')||(s[i]=='4')||(s[i]=='5')||(s[i]=='6')||(s[i]=='7')||(s[i]=='8')||(s[i]=='9'))
                    {
                        real=real+s[i];
                        i++;
                    }
                else {cout<<"Bad input\n";input=false;break;}
            }
            if (input)
            {
                if (s[0]=='-') real="-"+real;
                a.real=atoi(real.c_str());
                j=i;
                i++;
                while (s[i]!='i')
                {
		    if (i==l) {cout<<"Bad input\n";input=false;break;}
                    if ((s[i]=='0')||(s[i]=='1')||(s[i]=='2')||(s[i]=='3')||(s[i]=='4')||(s[i]=='5')||(s[i]=='6')||(s[i]=='7')||(s[i]=='8')||(s[i]=='9'))
                    {
                        imag=imag+s[i];
                        i++;
                    }
                    else {cout<<"Bad input\n";input=false;break;}
                }
	        if ((input)&&(i==j+1)) {cout<<"Bad input\n";input=false;}
                if (input)
                {
                    if (s[j]=='-') imag="-"+imag;
                    a.imag=atoi(imag.c_str());
		    complexinteger *num=new complexinteger;
		    num->real=a.real;num->imag=a.imag;
                    c.insertFront(num);
		    sum++;
                }
            }
        }
        input=true;
        i=0;
        cin>>s;
    }
}
