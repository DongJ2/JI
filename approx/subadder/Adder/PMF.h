#ifndef PMF_H_INCLUDED
#define PMF_H_INCLUDED

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
#include <sstream>
#include <string>
#include <cstdlib>

struct errorValue{
    double Pr_int;
    int V;
};

map<string, double> conv(map<string, double> f1, map<string, double> f2);

double getProb(int L, vector<int> I, vector<int>S, vector<int> R);

map<string, double> getPMF(int L, vector<int> Subadders, vector<int> R);

errorValue jointProb(vector<int> S, vector<int> R, vector<int> I);

vector<int> setMinus(vector<int> v1, vector<int> v2);

vector< vector<int> > getAllSubsets(vector<int> set);

int max(vector<int> v);

double Pr_err(int L, vector<int> subAdders, vector<int> Rs);

vector<int> unionSet(vector<vector<int> > sets);

vector<int> intersectSet(vector<vector<int> > sets);


#endif // PMF_H_INCLUDED
