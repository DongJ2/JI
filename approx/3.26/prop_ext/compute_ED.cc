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


void ED(int i, int j, long long ePar, double pPar, int n, int m, int *S, int *R, int *t, int *KK, int *CG_lb, vector<double> &input_dist, double *pp, double *pg, double *pk, map<string, double> &P_seg_all, map<string, double> &G_seg_all, int *S_sum, double **e, vector<long long> &ed_vec, vector<double> &prob_vec, int &count)
{
	cout << endl << "Entering into ED!" << endl;
	cout << "i = " << i << ", j = " << j << ", ePar = " << ePar << ", pPar = " << pPar << endl; 
	count++;
	if (i >= m)
	{
		//multiply the probability of high blocks being correct
		int start = m - 1;
		int end = j;
		if (start > end)
		{
			double *d_seg = new double[start-end+1];
			double ER_high = compute_ER(n, S, R, t, KK, CG_lb, input_dist, pp, pg, pk, P_seg_all, G_seg_all, start, end, d_seg);
			pPar *= (1-ER_high);
			delete []d_seg;
		}
	//	setprecision(10);
		cout << endl << "return from ED: " << endl;
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
	cout << "ePar = " << ePar << "new_ePar = " << new_ePar << endl;
	int q;
	for (q = i+1; q < m; q++)	
	{
		if (e[q][i] != 0)
			break;
	}
	ED(q, i, new_ePar, new_pPar, n, m, S, R, t, KK, CG_lb, input_dist, pp, pg, pk, P_seg_all, G_seg_all, S_sum, e, ed_vec, prob_vec, count);
	ED(i+1, j, ePar, pPar, n, m, S, R, t, KK, CG_lb, input_dist, pp, pg, pk, P_seg_all, G_seg_all, S_sum, e, ed_vec, prob_vec, count);
	return;
}



void compute_ED(int n, int m, int *S, int *R, int *t, int *KK, int *S_sum, int *SUB_lb, int *CG_lb, int *CG_lb_ind, double *pp, double *pg, double *pk, vector<double> &input_dist, map<string, double> &P_seg_all, map<string, double> &G_seg_all)
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


	//step2. calculate e_{i,j}
	struct timeb st, et;
	ftime(&st);
	e[0][0] = 0;
	int count_loop = 0;
	for (int j = 0; j < m-1; j++)
	{
		for (int i = j+1; i < m; i++)
		{
			cout << endl << "i = " << i << ", j = " << j << endl;
			count_loop++;
			//first deal with cases in which e[i][j] = 0
			if (t[i] >= i - j)
			{ 
				cout << "case1: t[i] >= i - j" << endl;
				e[i][j] = 0;
				continue;
			}			

			//initialize e[i][j] to 1
			e[i][j] = 1;

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
					int left = CG_lb[i]+KK[i]-1;
					int right = CG_lb[i]; 
					ppl = compute_P_nonuni(input_dist, n, left, right, P_seg_all);
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
					int left = CG_lb[i] - 1;
					int right = CG_lb[i-1];	
					if (right == SUB_lb[i-1-t[i-1]] && (left-right+1 == S[i-t[i]-1]))
						pgr_int = pg[i-t[i]-1];
					else
						pgr_int = compute_G_nonuni(input_dist, n, left, right, G_seg_all);
				}
				e[i][j] *= pgr_int;

				int start_block = CG_lb_ind[i-1];
				if (start_block > j)
				{
					double *d_seg = new double[start_block-j+1];
					double ER = compute_ER(n, S, R, t, KK, CG_lb,input_dist, pp, pg, pk, P_seg_all, G_seg_all, start_block, j, d_seg);
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
					int left = CG_lb[i] + KK[i] - 1;
					int right = CG_lb[i]; 
					ppl = compute_P_nonuni(input_dist, n, left, right, P_seg_all);
				}
				cout << "ppl = " << ppl << endl;
				e[i][j] *= ppl;
				double pgr;
				if (dist_class == 1)
					pgr = compute_GK_uni(S[i-t[i]-1] - KK[i]);
				else
				{
					int left = CG_lb[i] - 1;
					int right = SUB_lb[i-t[i]-1];
					if (left == SUB_lb[i-t[i]]-1)
						pgr = pg[i-t[i]-1];
					else
						pgr = compute_G_nonuni(input_dist, n, left, right, G_seg_all);
				}
				cout << "pgr = " <<  pgr << endl;
				e[i][j] *= pgr;
				int start_block = CG_lb_ind[i];
				cout << "start_block = " << start_block << ", j = " << j << endl;
				if (start_block > j)
				{
					double *d_seg = new double[start_block-j+1];
					double ER = compute_ER(n, S, R, t, KK, CG_lb, input_dist, pp, pg, pk, P_seg_all, G_seg_all, start_block, j, d_seg);
					e[i][j] *= (1-ER);
					delete []d_seg;
				}
				cout << "e[i][j] = " << e[i][j] << endl;

				//consider block i-1
				cout << "&consider block i-1:" << endl;
				double prob_acc = 0;
				for (int q = 1; q < t[i-1]-t[i]; q++)
				{
					double prob = 1;
					int u;
					for (u = i-1; u <= i-t[i]-q; u++)
						prob *= pp[u];
					prob *= pg[i-t[i]-q-1];

					int start_block = i-t[i]-q-1;
					if (start_block > j)
					{
						double *d_seg = new double[start_block-j+1];
						double ER = compute_ER(n, S, R, t, KK, CG_lb, input_dist, pp, pg, pk, P_seg_all, G_seg_all, start_block, j, d_seg);
						prob *= (1-ER);
						delete []d_seg;
					}
					else if (start_block < j)
						prob = 0;
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
						int left = CG_lb[i-1] + KK[i-1] - 1;	
						int right = CG_lb[i-1];
						pgl = compute_G_nonuni(input_dist, n, left, right, G_seg_all);
					}
					double prob = prob_pp * pgl;
						
					int start_block = i - 1 - t[i-1] - 1;
					if (start_block > j)
					{
						double *d_seg = new double[start_block-j+1];
						double ER = compute_ER(n, S, R, t, KK, CG_lb, input_dist, pp, pg, pk, P_seg_all, G_seg_all, start_block, j, d_seg);
						prob *= (1-ER);
						delete []d_seg;
					}
					e[i][j] += prob;
				}	
				cout << "e[i][j] = " << e[i][j] << endl;
			}
		}
	}
	ftime(&et);
    	double runtime = ((et.time - st.time)*1000 + (et.millitm - st.millitm))/1000.0;
	cout << "runtime for the for loop " << runtime << endl;
	cout << "values of e: " << endl;
	for (int j = 0; j < m-1; j++)
	{
		for (int i = j+1; i < m; i++)
			cout << "e[" << i << "][" << j << "] = " << e[i][j] << endl;
	}
	cout << "count_loop = " << count_loop << endl;


	vector<long long> ed_vec;
	vector<double> prob_vec;
	int count = 0;
	int q;
	for (q = 1; q < m; q++)	
		if (e[q][0] != 0)
			break;
	ftime(&st);
	ED(q, 0, 0, 1, n, m, S, R, t, KK, CG_lb, input_dist, pp, pg, pk, P_seg_all, G_seg_all, S_sum, e, ed_vec, prob_vec, count);
	ftime(&et);
    	runtime = ((et.time - st.time)*1000 + (et.millitm - st.millitm))/1000.0;
	cout << "runtime for ED: " << runtime << endl;
	cout << "count = " << count << endl;
	double sum_prob = 0;
	for (int i = 0; i < prob_vec.size(); i++)
		sum_prob += prob_vec[i];
	cout << "sum_prob = " << sum_prob << endl;
	map<long long, double> ed_prob_map, ed_prob;
	map<long long, double>::iterator itrm_id;
	for (int i = 0; i < ed_vec.size(); i++)
		ed_prob_map.insert(make_pair(ed_vec[i], prob_vec[i]));	
	double MSE = 0, MED = 0;
	cout << endl << "ed_prob_map: " << endl;
	ofstream fout;
	fout.open("scatter", ios::app);
	fout << endl << "****************************************************************" << endl;
	fout << "n = " << n << ", s = " << S[m-1] << ", r = " << R[m-1] << endl;
	fout << "ed: " << endl;
	for (itrm_id = ed_prob_map.begin(); itrm_id != ed_prob_map.end(); itrm_id++)
	{
		cout << itrm_id->first << ": " << itrm_id->second << endl;
		double ed = itrm_id->first;
		double er = itrm_id->second;
		MED += er * ed;
		MSE += er * ed * ed; 
		fout << log2(itrm_id->first) << " ";
	} 
	fout << endl;
	fout << "prob: " << endl;
	for (itrm_id = ed_prob_map.begin(); itrm_id != ed_prob_map.end(); itrm_id++)
		fout << log2(itrm_id->second) << " ";
	fout << endl;
	
	cout << "MSE = " << MSE << ", MED = " << MED << endl;
	cout << endl;


	for(int i = 0; i < ed_vec.size(); i++)
	{
		int integ_part = (int)log2(ed_vec[i]);
		if (log2(ed_vec[i]) - integ_part >= 0.5)
			integ_part++;
		itrm_id = ed_prob.find(integ_part);
		if (itrm_id == ed_prob.end())
			ed_prob.insert(make_pair(integ_part, prob_vec[i]));
		else
			itrm_id->second += prob_vec[i];	
	}
	cout << endl << "ed_prob: " << endl;
	for (itrm_id = ed_prob.begin(); itrm_id != ed_prob.end(); itrm_id++)
		cout << itrm_id->first << ": " << itrm_id->second << endl;
	
	cout << endl;
	for (itrm_id = ed_prob.begin(); itrm_id != ed_prob.end(); itrm_id++)
		cout << itrm_id->first << " ";
	cout << endl;
	for (itrm_id = ed_prob.begin(); itrm_id != ed_prob.end(); itrm_id++)
		cout << itrm_id->second << " ";
	cout << endl;


	//free dynamic-allocated memory for e_{i,j}
	for (int i = 0; i < m; i++)
		delete []e[i];
	delete []e;
	delete []S_sum;
	delete []SUB_lb;
	delete []CG_lb;
	delete []CG_lb_ind;
}
