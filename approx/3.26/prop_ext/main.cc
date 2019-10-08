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
#include "header/compute_ED.h"

using namespace std;

int dist_class;
#define miu pow(2.0, 11) 
//#define miu 32760 =
#define sigma 900
#define p_geo 0.01
#define flag_prob_real 0
#define flag_sub_unequal 1 
int flag_cg_unequal = 0;

void previous(int n, int k, int l)
{
	int kk = k+l;
	int B = k;
	double p = (pow(2.0, B) - 1)/pow(2.0, kk+1);
	int power = ceil((n-kk)/B);
	double ER = 1 - pow((1-p), power);
	double MSE = pow(2.0, 2*n-kk-1)/(pow(2.0, B) + 1);
	
	cout << "previous method: ER = " << ER << ", MSE = " << MSE << endl;
}

void proposed(int n, int m, int *S, int *R, int *t, int *KK, int mode)
{	 
	struct timeb st, et;

	//step2. compute d and/or e
	double *pp = new double[m];
	double *pg = new double[m];
	double *pk = new double[m];
	vector<double> input_dist;
	if (dist_class == 1)
	{
		for (int i = 0; i < m; i++)
		{
			pp[i] = compute_P_uni(S[i]);
			pg[i] = compute_GK_uni(S[i]);
			pk[i] = pg[i];
		}
	}
	else if (dist_class == 2 || dist_class == 3)
	{
		ftime(&st);
		//generate input distributions and then obtain P_prob, G_prob, K_prob 
		unsigned long long num;
		double prob, prob_real;
		if (dist_class == 2)
		{
			double coefficient = 1.0/(sqrt(2*M_PI)*sigma);
			for (int i = 0; i < pow(2, n); i++)
			{
				prob = coefficient * exp(-pow(i-miu, 2)/(2*sigma*sigma));
				num = prob * pow(2, n);	
				if (num > 0)
				{
					prob_real = num/pow(2, n);
				//	cout << "num = " << num << ", prob_real = " << prob_real << endl;
				}
				else
					prob_real = 0;
				if (flag_prob_real)
					input_dist.push_back(prob_real);
				else
					input_dist.push_back(prob);
			//	cout << "i = " << i << ", prob = " << prob << ", prob_real = " << prob_real << endl;
				cout << "i = " << i << ", prob = " << prob << endl;
			}
		}
		else if (dist_class == 3)
		{
			for (int i = 0; i < pow(2, n); i++)
			{
				prob = pow((1 - p_geo), i) * p_geo;	
				cout << "i = " << i << ", prob = " << prob << endl;
				num = prob * pow(2, n);	
				if (flag_prob_real)
				{
					if (num > 0)
					{
						prob_real = num/pow(2, n);
					//	prob_real = prob;
					}
					else
						prob_real = 0;
				//	input_dist.push_back(prob_real);
				}
				else 		
					input_dist.push_back(prob);
			}
		}
		ftime(&et);
    		double runtime = ((et.time - st.time)*1000 + (et.millitm - st.millitm))/1000.0;
		cout << "runtime for generating input_dist: " << runtime << endl;
		int *SUB_lb = new int[m];
		for (int i  = 0; i < m; i++)
		{
			if (i == 0) SUB_lb[i] = 0;
			else SUB_lb[i] = S[i-1] + SUB_lb[i-1];
		}
		obtain_block_dist(n, m, S, SUB_lb, input_dist, pp, pg, pk);
		delete SUB_lb;
	}
	cout << "pp, pg, pk: " << endl;
	for (int i = 0; i < m; i++)
	{
		cout << "pp[" << i << "] = " << pp[i] << endl;
		cout << "pg[" << i << "] = " << pg[i] << endl;
		cout << "pk[" << i << "] = " << pk[i] << endl;
	}

	//calculate S_sum, SUB_lb, CG_lb, CG_lb_ind 
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
		CG_lb_ind[i] = i - t[i] - 1;
		cout << "CG_lb_ind[" << i << "] = " << CG_lb_ind[i] << endl;
	}		


	//calculate di
	map<string, double> P_seg_all, G_seg_all;
	if (mode == 1)
	{
		cout << "**********************************************" << endl;
		cout << "start computing error rate!" << endl; 
		double *d = new double[m];
		double ER = compute_ER(n, S, R, t, KK, CG_lb, input_dist, pp, pg, pk, P_seg_all, G_seg_all, m-1, 0, d);
		delete []d;
	}

	//calculate distribution 
	if (mode == 2)
	{
		cout << "**********************************************" << endl;
		cout << "start computing error distribution!" << endl; 
		compute_ED(n, m, S, R, t, KK, S_sum, SUB_lb, CG_lb, CG_lb_ind, pp, pg, pk, input_dist, P_seg_all, G_seg_all);
	}
		
	
	//free dynamic-allocated memory
	delete []pp;
	delete []pg;
	delete []pk;
}



int main(int argc, char *argv[]) 
{
    	if(argc != 6)
    	{
    		//n: total number of bits of the adder
    		//k: block size
    		//l: carry generator length
       		cout << "Correct usage: ./main n k l mode dist_class > record_file " << endl;
        	exit(1);
    	}
    
	struct timeb startTime, endTime;                         //Record the computing time.
	ftime(&startTime);
	
	struct timeval st, et;
	gettimeofday(&st, NULL);
 	
	int n = atoi(argv[1]);
	int s = atoi(argv[2]);
	int r = atoi(argv[3]);
	int mode = atoi(argv[4]);
	dist_class = atoi(argv[5]);
	int m;
	if (flag_sub_unequal)
		m = 1 + (n-s-r)/s;
	else
		m = n/s;
	cout << "m = " << m << endl;
	int *t = new int[m];
	int *S = new int[m];
	int *R = new int[m];
	int *KK = new int[m];
	if (flag_sub_unequal)
		S[0] = s + r;
	else
		S[0] = s;
	R[0] = 0;
	t[0] = 0;

	//obtain t and KK
	obtain_t_KK(m, s, r, S, R, t, KK);
	cout << "R: ";
	for (int i = 0; i < m; i++)
		cout << R[i] << " ";
	cout << endl;
	cout << "t: ";
	for (int i = 0; i < m; i++)
		cout << t[i] << " ";
	cout << endl;
	cout << "KK: ";
	for (int i = 0; i < m; i++)
		cout << KK[i] << " ";
	cout << endl;
	
	//start proposed algorithm
	proposed(n, m, S, R, t, KK, mode);
	
	//previous: on error modeling and analysis
//	previous(n, s, r);	

	//dynamic memory restorage
	delete []t;
	delete []S;
	delete []R;
	delete []KK;

    	ftime(&endTime);
        
    	double runtime = ((endTime.time - startTime.time)*1000 + (endTime.millitm - startTime.millitm))/1000.0;
	cout << "total runtime: " << runtime << endl;

 	gettimeofday(&et, NULL);
 	cout << "total time: " << ((et.tv_sec - st.tv_sec) * 1000000 + et.tv_usec - st.tv_usec) << endl;
	
    	return 0;
}

