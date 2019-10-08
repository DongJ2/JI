#ifndef COMPUTE_ER_H 
#define COMPUTE_ER_H 
 
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <sys/timeb.h>
#include <sys/time.h>

using namespace std;

double compute_ER(int n, int *S, int *R, int *t, int *KK, int *CG_lb, vector<double> &input_dist, double *pp, double *pg, double *pk, map<string, double> &P_seg_all, map<string, double> &G_seg_all, int start, int end, double *d);

#endif 

