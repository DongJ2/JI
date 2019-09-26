#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <cassert>
#include "sort.h"

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
