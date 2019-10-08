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

using namespace std;

extern int dist_class;


double compute_ER(int n, int *S, int *R, int *t, int *KK, int *CG_lb, vector<double> &input_dist, double *pp, double *pg, double *pk, map<string, double> &P_seg_all, map<string, double> &G_seg_all, int start, int end, double *d)
{
	cout << "enter into compute_ER! start = " << start << ", end = " << end << endl;

	double dd;

	int m = start - end + 1;
	d[0] = 1;
	for (int i = 1; i < m; i++)
		d[i] = -1;
	int *sub_sum = new int[m];
	for (int i = 0; i < m; i++)
	{
		if (i == 0) 
			sub_sum[0] = S[end];
		else 
			sub_sum[i] = sub_sum[i-1] + S[end+i];
		if (i > 0 && R[end+i] >= sub_sum[i-1])
		{
			cout << "i = " << i << endl;
			cout << "R:" << R[end+i] << ", sub_sum: " << sub_sum[i-1] << endl;
			d[i] = 1;
		}
	}
	delete []sub_sum;

	for (int i = 1; i < m; i++)
	{
		cout << endl << "i = " << i << ", d[i] = " << d[i] << endl;
		if (d[i] == 1) continue;

		double v_part1 = 1;
		for (int j = 0; j <= i-1; j++)
			v_part1 = v_part1 * pp[end+j];

		double v_part2 = 1;
		if (KK[end+i] == 0)
			v_part2 = 0;
		else
		{
			for (int j = 1; j <= t[end+i]; j++)
				v_part2 = v_part2 * pp[end+i-j];
			double pgl;
			if (dist_class == 1)
				pgl = 0.5 - 1/pow(2.0, KK[end+i]+1);	
			else
			{
				int right = CG_lb[end+i];
				int left = CG_lb[end+i] + KK[end+i] - 1;
			//	cout << "part2: left = " << left << ", right = " << right << endl;
				pgl = compute_G_nonuni(input_dist, n, left, right, G_seg_all);
				cout << "pgl = " << pgl << endl;
			}
			v_part2 = v_part2 * pgl * d[i-t[end+i]-1];
		}
		
		double v_part3 = 0;
		for (int j = 1; j <= i; j++)
		{
			double p_tmp = 1;
			for (int q = end+i-1; q >= end+i-j+1; q--)
				p_tmp = p_tmp * pp[q]; 
			cout  << "p_tmp = " << p_tmp << endl;
			double tmp = p_tmp * pk[end+i-j] * d[i-j];  
			cout << "tmp = " << tmp << endl;
			v_part3 += tmp;
	//		v_part3 += p_tmp * pk[end+i-j] * d[i-j];
		}	

		double v_part4 = 0;
		for (int j = 1; j <= t[end+i]; j++)
		{
			double p_tmp = 1;
			for (int q = end+i-1; q >= end+i-j+1; q--)
				p_tmp = p_tmp * pp[q];
			v_part4 += p_tmp * pg[end+i-j] * d[i-j];
		}
			
		cout << "i = " << i << endl;
		cout << "v_part1 = " << v_part1 << ", v_part2 = " << v_part2 << ", v_part3 = " << v_part3 << ", v_part4 = " << v_part4 << endl;
		d[i] = v_part1 + v_part2 + v_part3 + v_part4;
	}

	cout << "values of d: " << endl;
	double ER;
	for (int i = 0; i < m; i++)
	{
		cout << d[i] << " ";
		if (i == m-1)
			ER = 1 - d[i];
	}
	cout << endl;
	cout << "error rate ER = " << ER << endl;

	dd = ER;
	return dd;
}

