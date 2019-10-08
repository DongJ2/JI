#include "PMF.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
     int L = 3;
    int i;
    double MED = 0;
    double sum,u;
    istringstream iStream;
    vector<int> S = {8,7,7};
    vector<int> R = {3,3};
    map<string,double> PMF = getPMF(L,S,R);
    map<string,double> ::iterator it = PMF.begin();
    while (it != PMF.end()){
        cout << it->first <<" " << it->second <<endl;
        iStream.str(it->first);
        iStream >> sum;
        iStream.clear();
        MED = MED + sum * it->second;
        it++;
    }
    cout << "MED = " << MED <<endl;
    cout << Pr_err(L,S,R) <<endl;

}
