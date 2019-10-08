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
#include "header/helper.h"
#include "header/compute_ER.h"

using namespace std;

extern int dist_class;


void ED(int i, int j, long long ePar, double pPar, int m, int *S, int *R, int *t, int *KK, double *pp, double *pg, double *pk, int *S_sum, double *d, double **e, vector<long long> &ed_vec, vector<double> &prob_vec, int &count)
{
	cout << endl << "Entering into ED!" << endl;
	cout << "i = " << i << ", j = " << j << endl; 
	count++;
	if (i >= m)
	{
		//multiply the probability of high blocks being correct
		int start = m - 1;
		int end = j;
		if (start > end)
		{
			double *d_seg = new double[start-end+1];
			double ER_high = compute_ER(S, R, t, KK, pp, pg, pk, start, end, d_seg);
			pPar *= (1-ER_high);
			delete []d_seg;
		}
	//	pPar *= d[m-j-1];
	//	setprecision(10);
		cout << "ePar = " << setprecision(12) << ePar << ", pPar = " << pPar << endl;
	//	cout << "log2(ePar) = " << setprecision(7) << log2(ePar) << ", log2(pPar) = " << log2(pPar) << endl;
		if (ePar < 1e-20 && ePar >= 0);
		else 
		{
		//	ed_vec.push_back(log2(ePar));
		//	prob_vec.push_back(log2(pPar));
			ed_vec.push_back(ePar);
			prob_vec.push_back(pPar);
		}
		return;
	}
	
	double new_pPar = pPar * e[i][j];
	long long new_ePar = ePar + pow(2.0, S_sum[i-1]);
	int q;
	for (q = i+1; q < m; q++)	
	{
		if (e[q][i] != 0)
			break;
	}
	ED(q, i, new_ePar, new_pPar, m, S, R, t, KK, pp, pg, pk, S_sum, d, e, ed_vec, prob_vec, count);
	ED(i+1, j, ePar, pPar, m, S, R, t, KK, pp, pg, pk, S_sum, d, e, ed_vec, prob_vec, count);
	return;
}



void compute_ED(int n, int m, int *S, int *R, int *t, int *KK, double *d, double *pp, double *pg, double *pk, vector<double> &input_dist)
{
	//step0. allocate memory for e_{i,j}
	double **e = new double *[m];
	if (e == NULL)
	{
		cout << "allocating memory for e fails!" << endl;
		exit(2);
	}
	for (int i = 0; i < m; i++)
	{
		e[i] = new double[m];
		if (e[i] == NULL)
		{
			cout << "allocating memory for e fails!" << endl;
			exit(3);
		}
	}

	//step1. calculate lb: the upper bound of each carry speculative chain
	int *S_sum = new int[m];
	int *SUB_lb = new int[m];
	cout << endl << "$SUB_lb: " << endl;
	for (int i = 0; i < m; i++)
	{
		if (i == 0)
		{
			S_sum[i] = S[0];
			SUB_lb[i] = 0;
		}
		else 
		{
			S_sum[i] = S_sum[i-1] + S[i];
			SUB_lb[i] = S_sum[i-1];
		}
		cout << "SUB_lb[" << i << "] = " << SUB_lb[i] << endl;
	}		
	int *CG_lb = new int[m];
	int *CG_lb_ind = new int[m];
	for (int i = 0; i < m; i++)
	{
		if (i == 0) CG_lb[i] = 0;
		else CG_lb[i] = S_sum[i-1] - R[i]; 
		cout << "CG_lb[" << i << "] = " << CG_lb[i] << endl;
		if (CG_lb[i] <= 0)
		{
			CG_lb_ind[i] = -1;
			cout << "CG_lb_ind[" << i << "] = " << CG_lb_ind[i] << endl;
			continue;
		}
		if (CG_lb[i] == S_sum[i-1])
		{
			CG_lb_ind[i] = i-1;
			cout << "CG_lb_ind[" << i << "] = " << CG_lb_ind[i] << endl;
			continue;
		}
		for (int j = i-1; j > 0; j--)
		{
			if (CG_lb[i] < S_sum[j] && CG_lb[i] >= S_sum[j-1])
			{
				if (CG_lb[i] > S_sum[j-1])
					CG_lb_ind[i] = j;
				else if (CG_lb[i] == S_sum[j-1])
					CG_lb_ind[i] = j-1;
				break;
			}
		}	
		cout << "CG_lb_ind[" << i << "] = " << CG_lb_ind[i] << endl;
	}		

	//step2. calculate e_{i,j}
	e[0][0] = 0;
	for (int j = 0; j < m-1; j++)
	{
		for (int i = j+1; i < m; i++)
		{
			cout << endl << "i = " << i << ", j = " << j << endl;
			//first deal with cases in which e[i][j] = 0
			if (t[i] >= i - j)
			{ 
				cout << "case1: t[i] >= i - j" << endl;
				e[i][j] = 0;
				continue;
			}			

			//initialize e[i][j] to 1
			e[i][j] = 1;

			//cases for t[i] = 0
		/*	if (t[i] == 0)
			{
				cout << "case2: t[i] = 0" << endl;
				double ppl = compute_P_uni(KK[i]);
				cout << "ppl = " << ppl << endl;
				int len = S[i-1] - KK[i];
				cout << "len = " << len << endl;
				double pgr = compute_GK_uni(len); 
				cout << "pgr = " << pgr << endl;
				e[i][j] = ppl * pgr;	
				cout << "e[i][j] = " << e[i][j] << endl;
				double dd = 1;
				int start = i-1;
				int end = j;
				if (start > end)
				{
					double *d_seg = new double[start-end+1];
					double ER = compute_ER(S, R, t, KK, pp, pg, pk, start, end, d_seg);
					e[i][j] *= (1-ER);
					delete []d_seg;
					cout << "e[i][j] = " << e[i][j] << endl;
				}
				continue;
			}
		*/

			//cases for t[i] > 0
			if (CG_lb_ind[i-1] == CG_lb_ind[i])
			{
				cout << "case2: equal!" << endl;
				if (CG_lb[i-1] == CG_lb[i])	
				{
					e[i][j] = 0;
					continue;
				}	
				for (int q = i - 1; q >= i - t[i]; q--)
				{
					double p = pp[q];
					e[i][j] *= p;
				}
				double ppl;
				if (dist_class == 1)
					ppl = compute_P_uni(KK[i]);
				else
				{
					int left = CG_lb[i] - KK[i] + 1;
					int right = CG_lb[i]; 
					ppl = compute_P_nonuni(input_dist, left, right);
				}
				e[i][j] *= ppl;
				double pgr_int;
				if (dist_class == 1)
				{
					int len_int = KK[i-1] - KK[i];
					pgr_int = compute_GK_uni(len_int);
				}
				else
				{
					int left = CG_lb[i] + 1;
					int right = CG_lb[i-1];	
					pgr_int = compute_G_nonuni(input_dist, left, right);
				}
				e[i][j] *= pgr_int;

				int start_block = CG_lb_ind[i-1];
				if (start_block > j)
				{
					double *d_seg = new double[start_block-j+1];
					double ER = compute_ER(S, R, t, KK, pp, pg, pk, start_block, j, d_seg);
					e[i][j] *= (1-ER);
					delete []d_seg;
				}
				cout << "e[i][j] = " << e[i][j] << endl;
			}
			else if (CG_lb_ind[i-1] < CG_lb_ind[i])
			{
				cout << "case3: unequal!" << endl;
				//consider block i
				cout << "&consider block i:" << endl;
				for (int q = i - 1; q >= i - t[i]; q--)
				{
					double p = pp[q];
					e[i][j] *= p;
				}
				cout << "e[i][j] = " << e[i][j] << endl;
				double ppl;
				if (dist_class == 1)
					ppl = compute_P_uni(KK[i]);
				else
				{
					int left = CG_lb[i] - KK[i] + 1;
					int right = CG_lb[i]; 
					ppl = compute_P_nonuni(input_dist, left, right);
				}
				cout << "ppl = " << ppl << endl;
				e[i][j] *= ppl;
				double pgr;
				if (dist_class == 1)
					pgr = compute_GK_uni(S[i-t[i]-1] - KK[i]);
				else
				{
					int left = CG_lb[i] + 1;
					int right = SUB_lb[i-t[i]-1];
					pgr = compute_G_nonuni(input_dist, left, right);
				}
				cout << "pgr = " <<  pgr << endl;
				e[i][j] *= pgr;
				int start_block = CG_lb_ind[i];
				cout << "start_block = " << start_block << ", j = " << j << endl;
				if (start_block > j)
				{
					double *d_seg = new double[start_block-j+1];
					double ER = compute_ER(S, R, t, KK, pp, pg, pk, start_block, j, d_seg);
					e[i][j] *= (1-ER);
					delete []d_seg;
				}
				cout << "e[i][j] = " << e[i][j] << endl;

				//consider block i-1
				cout << "&consider block i-1:" << endl;
				double prob_acc = 0;
				if (CG_lb_ind[i] - CG_lb_ind[i-1] > 1)
					for (int q = 0; q < t[i-1]-1; q++)
					{
						double prob = 1;
						int u;
						for (u = 0; u < q+2; u++)
							prob *= pp[i-1-u];
						prob *= pg[i-1-u];

						int start_block = i - 1 - u;
						if (start_block > j)
						{
							double *d_seg = new double[start_block-j+1];
							double ER = compute_ER(S, R, t, KK, pp, pg, pk, start_block, j, d_seg);
							prob *= (1-ER);
							delete []d_seg;
						}
						prob_acc += prob;
					}
				e[i][j] += prob_acc;

				if (CG_lb_ind[i-1] >= j && KK[i-1] > 0)
				{
					double prob_pp = 1;
					for (int q = 0; q <= t[i-1]; q++)
						prob_pp *= pp[i-1-q];
					double pgl;
					if (dist_class == 1)
						pgl = compute_GK_uni(KK[i-1]);
					else
					{
						int left = CG_lb[i-1] - KK[i-1] + 1;	
						int right = CG_lb[i-1];
						pgl = compute_G_nonuni(input_dist, left, right);
					}
					double prob = prob_pp * pgl;
						
					int start_block = i - 1 - t[i-1] - 1;
					if (start_block > j)
					{
						double *d_seg = new double[start_block-j+1];
						double ER = compute_ER(S, R, t, KK, pp, pg, pk, start_block, j, d_seg);
						prob *= (1-ER);
						delete []d_seg;
					}
					e[i][j] += prob;
				}	
				cout << "e[i][j] = " << e[i][j] << endl;
			}
		}
	}
	cout << "values of e: " << endl;
	for (int j = 0; j < m-1; j++)
	{
		for (int i = j+1; i < m; i++)
			cout << "e[" << i << "][" << j << "] = " << e[i][j] << endl;
	}


	vector<long long> ed_vec;
	vector<double> prob_vec;
	int count = 0;
	int q;
	for (q = 1; q < m; q++)	
		if (e[q][0] != 0)
			break;
	ED(q, 0, 0, 1, m, S, R, t, KK, pp, pg, pk, S_sum, d, e, ed_vec, prob_vec, count);
	map<long long, double> ed_prob_map;
	map<long long, double>::iterator itrm_id;
	for (int i = 0; i < ed_vec.size(); i++)
		ed_prob_map.insert(make_pair(ed_vec[i], prob_vec[i]));	
	cout << endl << "ed_prob_map: " << endl;
	for (itrm_id = ed_prob_map.begin(); itrm_id != ed_prob_map.end(); itrm_id++)
		cout << itrm_id->first << ": " << itrm_id->second << endl;

	//free dynamic-allocated memory for e_{i,j}
	for (int i = 0; i < m; i++)
		delete []e[i];
	delete []e;
	delete []S_sum;
	delete []SUB_lb;
	delete []CG_lb;
	delete []CG_lb_ind;
}
