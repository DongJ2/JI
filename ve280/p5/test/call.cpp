#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "dlist.h"

using namespace std;

struct caller
{
    string name;
    int waiting;
    int duration;
};

int main()
{
    Dlist<caller> regular;
    Dlist<caller> silver;
    Dlist<caller> gold;
    Dlist<caller> platinum;
    int num_r,num_s,num_g,num_p,num,agent;
    num_r=0;num_s=0;num_g=0;num_p=0;
    caller *member;
    caller people;
    member=&people;
    agent=0;
    bool busy;
    busy=false;
    string s;
    istringstream iStream;
    getline(cin,s);
    int t,w,d;
    string name,status;
    int n,m;
    m=0;
    n=atoi(s.c_str());
    int time=0;
    getline(cin,s);
    iStream.str(s);
    iStream>>t>>name>>status>>w>>d;
    while (m<n)
    {
        cout<<"Starting tick #"<<time<<endl;
        if (busy) agent--;
	if ((busy)&&(agent==0)) busy=false;
        num=0;
        while (num<num_p)
        {
            member=platinum.removeBack();
            if (member->waiting==0) {cout<<member->name<<" hangs up\n";num_p--;num--;m++;}
            else 
	    {
		caller *cal=new caller;
		cal->name=member->name;
		cal->waiting=member->waiting;
		cal->duration=member->duration;
		platinum.insertFront(cal);
	    }
            num++;
        }
        num=0;
        while (num<num_g)
        {
            member=gold.removeBack();
            if (member->waiting==0) {cout<<member->name<<" hangs up\n";num_g--;num--;m++;}
            else 
	    {
		caller *cal=new caller;
		cal->name=member->name;
		cal->waiting=member->waiting;
		cal->duration=member->duration;
		gold.insertFront(cal);
	    }
            num++;
        }
        num=0;
        while (num<num_s)
        {
            member=silver.removeBack();
            if (member->waiting==0) {cout<<member->name<<" hangs up\n";num_s--;num--;m++;}
            else 
	    {
		caller *cal=new caller;
		cal->name=member->name;
		cal->waiting=member->waiting;
		cal->duration=member->duration;
		silver.insertFront(cal);
	    }
            num++;
        }
        num=0;
        while (num<num_r)
        {
            member=regular.removeBack();
            if (member->waiting==0) {cout<<member->name<<" hangs up\n";num_r--;num--;m++;}
            else 
	    {
		caller *cal=new caller;
		cal->name=member->name;
		cal->waiting=member->waiting;
		cal->duration=member->duration;
		regular.insertFront(cal);
	    }
            num++;
        }
        while (time==t)
        {
            cout<<"Call from "<<name<<" a "<<status<<" member\n";
            member->name=name;
            member->waiting=w;
            member->duration=d;
            iStream.clear();
            if (status=="platinum") 
	    {
		caller *cal=new caller;
		cal->name=member->name;
		cal->waiting=member->waiting;
		cal->duration=member->duration;
		platinum.insertFront(cal);
		num_p++;
	    }
            if (status=="gold") 
	    {
		caller *cal=new caller;
		cal->name=member->name;
		cal->waiting=member->waiting;
		cal->duration=member->duration;
		gold.insertFront(cal);
		num_g++;
	    }
            if (status=="silver")
	    {
		caller *cal=new caller;
		cal->name=member->name;
		cal->waiting=member->waiting;
		cal->duration=member->duration;
		silver.insertFront(cal);
		num_s++;
	    } 
            if (status=="regular") 
	    {
		caller *cal=new caller;
		cal->name=member->name;
		cal->waiting=member->waiting;
		cal->duration=member->duration;
		regular.insertFront(cal);
		num_r++;
	    }
            if (getline(cin,s))
            {
		iStream.str(s);
                iStream>>t>>name>>status>>w>>d;
    	    }
	    else t=-1;
        }
        if (!busy)
        {
            if (!platinum.isEmpty())
            {
                member=platinum.removeBack();
                cout<<"Answering call from "<<member->name<<endl;
                agent=member->duration;
                busy=true;
		m++;
		num_p--;
            }
            else if (!gold.isEmpty())
            {
                member=gold.removeBack();
                cout<<"Answering call from "<<member->name<<endl;
                agent=member->duration;
                busy=true;
		m++;
		num_g--;
            }
            else if (!silver.isEmpty())
            {
                member=silver.removeBack();
                cout<<"Answering call from "<<member->name<<endl;
                agent=member->duration;
                busy=true;
		m++;
		num_s--;
            }
            else if (!regular.isEmpty())
            {
                member=regular.removeBack();
                cout<<"Answering call from "<<member->name<<endl;
                agent=member->duration;
                busy=true;
		m++;
		num_r--;
            }
        }
        num=0;
        while (num<num_p)
        {
            member=platinum.removeBack();
            member->waiting--;
            caller *cal=new caller;
	    cal->name=member->name;
	    cal->waiting=member->waiting;
	    cal->duration=member->duration;
	    platinum.insertFront(cal);
            num++;
        }
        num=0;
        while (num<num_g)
        {
            member=gold.removeBack();
            member->waiting--;
	    caller *cal=new caller;
	    cal->name=member->name;
	    cal->waiting=member->waiting;
	    cal->duration=member->duration;
	    gold.insertFront(cal);
            num++;
        }
        num=0;
        while (num<num_s)
        {
            member=silver.removeBack();
            member->waiting--;
	    caller *cal=new caller;
	    cal->name=member->name;
	    cal->waiting=member->waiting;
	    cal->duration=member->duration;
	    silver.insertFront(cal);
            num++;
        }
        num=0;
        while (num<num_r)
        {
            member=regular.removeBack();
            member->waiting--;
	    caller *cal=new caller;
	    cal->name=member->name;
	    cal->waiting=member->waiting;
	    cal->duration=member->duration;
	    regular.insertFront(cal);
            num++;
        }
        time++;
    }
    cout<<"Starting tick #"<<time<<endl;
}
