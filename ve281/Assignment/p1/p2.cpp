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

int main()
{
    int a[5];
    a[0]=4;
    a[1]=8;
    a[2]=1;
    a[3]=6;
    a[4]=5;
    bubble(&a[0],5);
    cout<<a[0]<<" "<<a[1]<<" "<<a[2]<<" "<<a[3]<<" "<<a[4]<<endl;
}
