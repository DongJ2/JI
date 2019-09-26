#pragma GCC optimize(3)
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <cassert>
#include <getopt.h>
#include "binary_heap.h"
#include "priority_queue.h"
#include "unsorted_heap.h"
#include "fib_heap.h"

using namespace std;

struct point
{
    int x;
    int y;
    int key;
    int weight;
    point *prev;
    bool mark;
};

struct compare_t
{
    bool operator()(point *a, point *b) const
    {
        if (a->key<b->key) return true;
	else if (a->key==b->key && a->x<b->x) return true;
	else if (a->key==b->key && a->x==b->x && a->y<b->y) return true;
	else return false;
    }
};

int main(int argc, char *argv[])
{
    int width,height,start_x,start_y,end_x,end_y;
    width=5;
    height=5;
    int t=0;
    int k=0;
    int num=0;
    clock_t time;
    clock_t ave[3];
    point *p,*tem;
    while (t<12)
    {
	cout<<"Width is "<<width<<" and height is "<<height<<endl;
	point *pos=new point[width*height];
	start_x=0;start_y=0;
	end_x=width-1;end_y=height-1;
	while (k<5){	
for (int j=0;j<height;j++)
            for (int i=0;i<width;i++)
            {
            	pos[j*width+i].weight=mrand48()%100;
	   	pos[j*width+i].mark=false;
	    	pos[j*width+i].x=i;
	    	pos[j*width+i].y=j;
	    	pos[j*width+i].prev=NULL;
            }
	while (num<3){	
	pos[start_x+start_y*width].prev=&pos[start_x+start_y*width];
	pos[start_x+start_y*width].key=pos[start_x+start_y*width].weight;
	priority_queue<point*, compare_t> *PQ=NULL;
	if (num==0) PQ=new binary_heap<point*, compare_t>;
	if (num==1) PQ=new unsorted_heap<point*, compare_t>;
	if (num==2) PQ=new fib_heap<point*, compare_t>;
	p=&pos[start_x+start_y*width];
	time=clock();    	
	PQ->enqueue(p);
	while (PQ->empty()==false)
    	{
        p=PQ->dequeue_min();
        if (p->x+1<width && pos[p->x+1+p->y*width].mark==false)
        {
            pos[p->x+1+p->y*width].mark=true;
	    pos[p->x+1+p->y*width].prev=p;
	    pos[p->x+1+p->y*width].key=p->key+pos[p->x+1+p->y*width].weight;
            tem=&pos[p->x+1+p->y*width];
            if (tem->x==end_x && tem->y==end_y) break;
            else PQ->enqueue(tem);
        }
        if (p->y+1<height && pos[p->x+(p->y+1)*width].mark==false)
        {
            tem=&pos[p->x+(p->y+1)*width];
	    tem->mark=true;
	    tem->prev=p;
	    tem->key=p->key+tem->weight;
            if (tem->x==end_x && tem->y==end_y) break;
            else PQ->enqueue(tem);
        }
        if (p->x-1>=0 && pos[p->x-1+p->y*width].mark==false)
        {
            tem=&pos[p->x-1+p->y*width];
	    tem->mark=true;
	    tem->prev=p;
	    tem->key=p->key+tem->weight;
            if (tem->x==end_x && tem->y==end_y) break;
            else PQ->enqueue(tem);
        }
        if (p->y-1>=0 && pos[p->x+(p->y-1)*width].mark==false)
        {
            tem=&pos[p->x+(p->y-1)*width];
	    tem->mark=true;
	    tem->prev=p;
	    tem->key=p->key+tem->weight;
            if (tem->x==end_x && tem->y==end_y) break;
            else PQ->enqueue(tem);
        }
    }
	time=clock()-time;
	ave[num]=(k*ave[num]+time)/(k+1);
	num++;
	while (PQ->size()>0) PQ->dequeue_min();
	delete PQ;
	for (int j=0;j<height;j++)
            for (int i=0;i<width;i++)
            {
	   	pos[j*width+i].mark=false;
	    	pos[j*width+i].x=i;
	    	pos[j*width+i].y=j;
	    	pos[j*width+i].prev=NULL;
	   	pos[j*width+i].key=0;
            }
	}
	num=0;
	k++;
}
	k=0;
	delete [] pos;
	cout<<"The average runtime of binary heap is "<<ave[0]<<endl;
	cout<<"The average runtime of unsorted heap is "<<ave[1]<<endl;
	cout<<"The average runtime of fibonacci heap is "<<ave[2]<<endl;
	if (t==0) {width=10;height=10;}
	if (t==1) {width=20;height=20;}
	if (t==2) {width=50;height=50;}
	if (t==3) {width=100;height=100;}
	if (t==4) {width=200;height=200;}
	if (t==5) {width=300;height=300;}
	if (t==6) {width=400;height=400;}
	if (t==7) {width=500;height=500;}
	if (t==8) {width=600;height=600;}
	if (t==9) {width=700;height=700;}
	if (t==10) {width=800;height=800;}
	t++;
    }
}
