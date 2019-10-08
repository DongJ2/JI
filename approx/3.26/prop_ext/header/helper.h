#ifndef HELPER_H
#define HELPER_H 
 
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

void d2b(int d, vector<int> &bin, int numBit);

void obtain_t_KK(int m, int s, int r, int *S, int *R, int *t, int *KK);

double compute_P_uni(int len);

double compute_GK_uni(int len);

double compute_P_nonuni(vector<double> &input_dist, int n, int left, int right, map<string, double> &P_seg_all);

double compute_G_nonuni(vector<double> &input_dist, int n, int left, int right, map<string, double> &G_seg_all);

void obtain_seg_sum_dist(vector<double> &input_dist, int n, int left, int right, map<int, double> &this_seg_dist);

double compute_P_nonuni(vector<double> &input_dist, int n, int left, int right, map<string, double> &P_seg_all);

double compute_G_nonuni(vector<double> &input_dist, int n, int left, int right, map<string, double> &G_seg_all);

void obtain_block_dist(int n, int m, int *S, int *SUB_lb, vector<double> &input_dist, double *pp, double *pg, double *pk);

//void obtain_block_dist_GL(int n, int k, int kk, vector<double> &input_dist, vector<double> &P_prob, vector<double> &G_prob, vector<double> &K_prob, vector<double> &GL_prob);


//void obtain_block_sep_dist(int n, int k, int kk, vector<double> &input_dist, vector<double> &PL_prob, vector<double> &PR_prob, vector<double> &GL_prob, vector<double> &GR_prob, vector<double> &KL_prob, vector<double> &KR_prob);

#endif 

