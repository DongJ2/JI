#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <vector>
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

extern int flag_cg_unequal;

void d2b(int d, vector<int> &bin, int numBit)
{
	int mod = 0;
	vector<int> tmpstr;
	
	if(d == 0)
	{
		for(int i = 0; i < numBit; i++)
			bin.push_back(0);
		return;	
	}

	while(d > 0)
	{
		mod = d%2;
		d /= 2;
		tmpstr.push_back(mod);
	}
	unsigned int len = tmpstr.size();
	int minus = numBit - len;
	if(minus > 0)
		for(int i = 0; i < minus; i++)
			bin.push_back(0);	
	for(int i = len - 1; i >= 0; i--)
		bin.push_back(tmpstr[i]);
}


void obtain_t_KK(int m, int s, int r, int *S, int *R, int *t, int *KK)
{
	for (int i = 1; i < m; i++)
	{
		S[i] = s;
		R[i] = r;
		if (flag_cg_unequal)
		{
			if (i == m-2) R[i] = 2 * r;
			if (i == m-1) R[i] = 3 * r;
		//	if (i == m-1) R[i] = 2 * r;
		}
		int j = i;
		int rem = R[j];
		t[i] = 0;
		cout << endl << "i = " << i << endl;
		while(rem > 0 && j >= 1)
		{
			rem = rem - S[j-1];
			cout << "rem = " << rem << endl;
			j--;
			t[i]++;
		}
		if (rem < 0)
		{
			rem = rem + S[j];
			cout << "j = " << j << ", rem = " << rem << endl;
			KK[i] = rem;
	 		t[i] = t[i] - 1;	
		}
		else if (rem == 0)
			KK[i] = 0;
		
	}
}


double compute_P_uni(int len)
{
	double P = 1/pow(2.0, len);
	return P;	
}


double compute_GK_uni(int len)
{
	double G = 0.5 - 1/pow(2.0, len+1);
	return G;
}


void obtain_seg_sum_dist(vector<double> &input_dist, int n, int left, int right, map<int, double> &this_seg_dist)
{
	int max = left, min = right;
	int len = max-min+1;
	for (int j = 0; j < pow(2, len); j++)
	{
		double prob = 0;
		if (min == 0)
		{
			if (max == n-1)
			{
				double this_prob = input_dist[j];
				prob += this_prob;	
			}
			else
				for (unsigned int s = 0; s < pow(2, n-1-max); s++)
				{
					unsigned high_value = s << (max+1);
					unsigned value = j + high_value;
					double this_prob = input_dist[value];
					prob += this_prob;	
				}
		}
		else
		{
			if (max == n-1)
				for (unsigned int s = 0; s < pow(2, min+1); s++)
				{
					unsigned low_value = j << min;
					unsigned value = low_value + s;
					double this_prob = input_dist[value];
					prob += this_prob;	
				}	
			else
			{
				unsigned mid_value = j << min;
				for (unsigned int s = 0; s < pow(2, min); s++)
				{
					unsigned low_value = s;
					for (unsigned int r = 0; r < pow(2, n-1-max); r++)
					{
						unsigned high_value = r << (max+1);
						unsigned value = high_value + mid_value + low_value;
						double this_prob = input_dist[value];
						prob += this_prob;	
					}
				} 
			}
		}
		this_seg_dist.insert(make_pair(j, prob));
	}
}


string get_string_from_ints(int min, int max)
{
	stringstream ss;
	ss << min;
	string str = ss.str();
	str.append("-");
	ss.str("");
	ss << max;
	str.append(ss.str());
	return str;
}


double compute_P_nonuni(vector<double> &input_dist, int n, int left, int right, map<string, double> &P_seg_all)
{
	map<string, double>::iterator itrm_sd;

	struct timeb st, et;
	ftime(&st);
	cout << "left = " << left << ", right = " << right << endl;
	
	if (left < right) return 1;
	
	string cur_str = get_string_from_ints(left, right);
	itrm_sd = P_seg_all.find(cur_str); 
	if (itrm_sd != P_seg_all.end())
		return itrm_sd->second;

	map<int, double> this_seg_dist;
	map<int, double>::iterator itrm_id;
	obtain_seg_sum_dist(input_dist, n, left, right, this_seg_dist);

	int len = left - right + 1;
	int value = pow(2, len) - 1;	
	double prob_P = 0, prob1, prob2;
	for (int r = 0; r <= value; r++)
	{
		int x = r;
		int y = value - r;
		itrm_id = this_seg_dist.find(x);
		if (itrm_id == this_seg_dist.end())
			prob1 = 0;
		else
			prob1 = itrm_id->second;
		if (prob1 == 0) continue;
		itrm_id = this_seg_dist.find(y);
		if (itrm_id == this_seg_dist.end())
			prob2 = 0;
		else
			prob2 = itrm_id->second;
		prob_P += prob1 * prob2;
	}
	ftime(&et);
    	double runtime = ((et.time - st.time)*1000 + (et.millitm - st.millitm))/1000.0;
	cout << "runtime for compute_P_nonuni: " << runtime << endl;

	P_seg_all.insert(make_pair(cur_str, prob_P));
	return prob_P;
}


double compute_G_nonuni(vector<double> &input_dist, int n, int left, int right, map<string, double> &G_seg_all)
{
	map<string, double>::iterator itrm_sd;

	struct timeb st, et;
	ftime(&st);

	cout << "left = " << left << ", right = " << right << endl;
	if (left < right) return 1;

	string cur_str = get_string_from_ints(left, right);
	itrm_sd = G_seg_all.find(cur_str); 
	if (itrm_sd != G_seg_all.end())
		return itrm_sd->second;

	map<int, double> this_seg_dist;
	map<int, double>::iterator itrm_id;
	obtain_seg_sum_dist(input_dist, n, left, right, this_seg_dist);
	
	double prob_G0 = 0, prob1, prob2;
	int len = left - right + 1;
	for (int j = pow(2, len)-1; j < pow(2, len+1)-1; j++)
	{
		int value = j;
		double prob = 0;
		for (int r = 0; r <= j; r++)
		{
			int x = r;
			int y = j - r;
			itrm_id = this_seg_dist.find(x);
			if (itrm_id == this_seg_dist.end())
				prob1 = 0;
			else
				prob1 = itrm_id->second;
			if (prob1 == 0) continue;
			itrm_id = this_seg_dist.find(y);
			if (itrm_id == this_seg_dist.end())
				prob2 = 0;
			else
				prob2 = itrm_id->second;
			prob += prob1 * prob2;
		}		
		if (value > pow(2, len) - 1)
			prob_G0 += prob;
	}
	ftime(&et);
    	double runtime = ((et.time - st.time)*1000 + (et.millitm - st.millitm))/1000.0;
	cout << "runtime for compute_G_nonuni: " << runtime << endl;

	G_seg_all.insert(make_pair(cur_str, prob_G0));
	return prob_G0;
}


void obtain_block_dist(int n, int m, int *S, int *SUB_lb, vector<double> &input_dist, double *pp, double *pg, double *pk)
{
	map<int, double>::iterator itrm_id;
	struct timeb st, et;
	ftime(&st);

	//step2. get the distribution for each block from input_dist
        vector<map<int, double> > block_dist;
        for (int i = 0; i < m; i++)
	{
		cout << endl << "#block " << i << endl;
		map<int, double> this_block_dist;
		int k = S[i];
		cout << "k = " << k << endl;
	/*	if (i  == 0) {
			cout << "S[1] = " << S[1] << endl;
			double prob = 0;
			for (unsigned int r = 0; r < pow(2, n-S[1]); r++) {
				unsigned rr = r * pow(2, S[1]);
				cout << "rr = " << rr << endl;
				prob += input_dist[rr];
			}
			cout << "prob for block 0 = 0 is " << prob << endl;
			
		}
	*/
		for (int j = 0; j < pow(2, k); j++)
		{
			cout << "j = " << j << endl;
			double prob = 0;
			if (i == 0)
			{
				for (unsigned int r = 0; r < pow(2, n-k); r++)
				{
					unsigned rr = r << k;
					unsigned int value = rr + j; 
					cout << "value = " << value << ", ";
					double this_prob = input_dist[value];
		       			cout << "this_prob = " << this_prob << endl;
					prob += this_prob; 
				}
				cout << "j = " << j << ", prob = " << prob << endl;
			}
			else
			{
				double this_prob;
				for (int s = 0; s < pow(2, SUB_lb[i]); s++)
				{
					int value;
					if (m-1-i > 0)
					{
						unsigned int mid_value = j << SUB_lb[i];	
						for (unsigned int q = 0; q < pow(2, n-SUB_lb[i+1]); q++)
						{
							int shift_bits = SUB_lb[i+1];
							unsigned int qq = q << shift_bits;	
						 	value = s + mid_value + qq; 		
							this_prob = input_dist[value];
							prob += this_prob; 
						}
					}
					else if (m-1-i == 0)
					{
						unsigned int left_value = j << SUB_lb[i];
						value = s + left_value;
						this_prob = input_dist[value];
						prob += this_prob; 
					}
				}
			}
			this_block_dist.insert(pair<int, double>(j, prob));
		}
       		cout << "this_block_dist: " << endl;
       		double sum_block = 0;
		for (itrm_id = this_block_dist.begin(); itrm_id != this_block_dist.end(); itrm_id++)
		{
			cout << itrm_id->first << ": " <<  itrm_id->second  << endl;
			sum_block += itrm_id->second;
		}
		cout << "sum_block = " << sum_block << endl;
	
		block_dist.push_back(this_block_dist);
	}		
	
	//step3. obtain the distribution for the sum of each block by computing convolution
	vector<map<int, double> > sum_block_dist; 
	for (int i = 0; i < m; i++)
	{
		map<int, double> &cur_block_dist = block_dist[i];
		cout << "block = " << i << endl;
		double prob_P = 0;
		int full_value = pow(2, S[i]) - 1;
		for (int r = 0; r <= full_value; r++)
		{
			itrm_id = cur_block_dist.find(r);
			double prob1 = itrm_id->second;
			itrm_id = cur_block_dist.find(full_value-r);
			double prob2 = itrm_id->second;
			prob_P += prob1 * prob2;
		}		
		pp[i] = prob_P;

		double prob_G = 0;
		double prob, prob1, prob2;
		int k = S[i];
		for (int j = pow(2, k); j < pow(2, k+1)-1; j++)
		{
			prob = 0;
			for (int r = 0; r <= j; r++)
			{
				itrm_id = cur_block_dist.find(r);
				if (itrm_id == cur_block_dist.end())
				{
					prob1 = 0;
					continue;
				}
				else
					prob1 = itrm_id->second;

				itrm_id = cur_block_dist.find(j-r);
				if (itrm_id == cur_block_dist.end())
				{
					prob2 = 0;
					continue;
				}
				else
				prob2 = itrm_id->second;
				prob += prob1 * prob2;
			}		
			prob_G += prob;
		}
		pg[i] = prob_G;
		pk[i] = 1 - prob_P - prob_G;
        } 

	ftime(&et);
    	double runtime = ((et.time - st.time)*1000 + (et.millitm - st.millitm))/1000.0;
	cout << "runtime for obtaining block distribution: " << runtime << endl;
}



/*
void obtain_block_dist_GL(int n, int k, int kk, vector<double> &input_dist, vector<double> &P_prob, vector<double> &G_prob, vector<double> &K_prob, vector<double> &GL_prob)
{
	int m = n/k;
	obtain_block_dist(n, k, input_dist, P_prob, G_prob, K_prob);

        vector<map<int, double> > block_dist_left;
	map<int, double>::iterator itrm_id;
        for (int i = 0; i < m; i++)
	{
		cout << endl << "#block " << i << endl;
		map<int, double> this_block_dist_left;
		//obtain this_block_dist_left
		int kr = k - kk;
		for (int j = 0; j < pow(2, kk); j++)
		{
	//		cout << "j = " << j << endl;
			double prob = 0, this_prob;
			for (int s = 0; s < pow(2, k*i+kr); s++)
			{
				int value;
				if (m-1-i > 0)
				{
					unsigned int mid_value = j << (k*i+kr);	
					for (unsigned int q = 0; q < pow(2, k*(m-1-i)); q++)
					{
						int shift_bits = k * (i+1);
						unsigned int qq = q << shift_bits;	
					 	value = s + mid_value + qq; 		
						this_prob = input_dist[value];
				//		cout << "value = " << value << ", this_prob = " << this_prob << endl;
						prob += this_prob; 
					}
				}
				else if (m-1-i == 0)
				{
					unsigned int left_value = j << (k*i+kr);
					value = s + left_value;
					this_prob = input_dist[value];
			//		cout << "value = " << value << ", this_prob = " << this_prob << endl;
					prob += this_prob; 
				}
			}
			this_block_dist_left.insert(pair<int, double>(j, prob));
		}
		cout << "this_block_dist_left: " << endl;
		double sum_block_left = 0;
		for (itrm_id = this_block_dist_left.begin(); itrm_id != this_block_dist_left.end(); itrm_id++)
		{
			cout << itrm_id->first << ": " <<  itrm_id->second  << endl;
			sum_block_left += itrm_id->second;
		}
//		cout << "sum_block_left = " << sum_block_left << endl;
		block_dist_left.push_back(this_block_dist_left);
	}		
	
	//step2. obtain the distribution for the sum of each block by computing convolution
	for (int i = 0; i < m; i++)
	{
		//obtain GL_prob
		map<int, double> cur_block_dist_left = block_dist_left[i];
		double prob_GL = 0;
		for (int j = 0; j < pow(2, kk+1)-1; j++)
		{
			int value = j;
			double prob = 0;
			for (int r = 0; r <= j; r++)
			{
				int x = r;
				int y = j - r;
				itrm_id = cur_block_dist_left.find(x);
				double prob1 = itrm_id->second;
				itrm_id = cur_block_dist_left.find(y);
				double prob2 = itrm_id->second;
				prob += prob1 * prob2;
			}		
			if (value > pow(2, kk) - 1)
				prob_GL += prob;
		}
		GL_prob.push_back(prob_GL);
        } 
}
*/

/*void obtain_block_sep_dist(int n, int k, int kk, vector<double> &input_dist, vector<double> &PL_prob, vector<double> &PR_prob, vector<double> &GL_prob, vector<double> &GR_prob, vector<double> &KL_prob, vector<double> &KR_prob)
{
	map<int, double>::iterator itrm_id;

	//step2. get the distribution for each block from input_dist
	int m = n/k;
        vector<map<int, double> > block_dist_left, block_dist_right;
        for (int i = 0; i < m; i++)
	{
		cout << endl << "#block " << i << endl;
		map<int, double> this_block_dist_left, this_block_dist_right;
		int kr = k - kk;
		//obtain this_block_dist_left
		for (int j = 0; j < pow(2, kk); j++)
		{
			cout << "j = " << j << endl;
			double prob = 0;
			double this_prob;
			for (int s = 0; s < pow(2, i*k+kr); s++)
			{
				int value;
				if (m-1-i > 0)
				{
					unsigned int mid_value = j << (k*i+kr);	
					for (unsigned int q = 0; q < pow(2, k*(m-1-i)); q++)
					{
						int shift_bits = k * (i+1);
						unsigned int qq = q << shift_bits;	
					 	value = s + mid_value + qq; 		
						this_prob = input_dist[value];
						cout << "value = " << value << ", this_prob = " << this_prob << endl;
						prob += this_prob; 
					}
				}
				else if (m-1-i == 0)
				{
					unsigned int left_value = j << (k*i+kr);
					value = s + left_value;
					this_prob = input_dist[value];
					cout << "value = " << value << ", this_prob = " << this_prob << endl;
					prob += this_prob; 
				}
			}
			this_block_dist_left.insert(pair<int, double>(j, prob));
		}
		cout << "this_block_dist_left: " << endl;
		double sum_block_left = 0;
		for (itrm_id = this_block_dist_left.begin(); itrm_id != this_block_dist_left.end(); itrm_id++)
		{
			cout << itrm_id->first << ": " <<  itrm_id->second  << endl;
			sum_block_left += itrm_id->second;
		}
		cout << "sum_block_left = " << sum_block_left << endl;
		block_dist_left.push_back(this_block_dist_left);

		
		//obtain this_block_dist_right
		for (int j = 0; j < pow(2, kr); j++)
		{
			cout << "j = " << j << endl;
			double prob = 0;
			double this_prob;
			for (int s = 0; s < pow(2, i*k); s++)
			{
				int value;
				unsigned int mid_value = j << (k*i);	
				for (unsigned int q = 0; q < pow(2, k*(m-1-i)+kk); q++)
				{
					int shift_bits = k * i + kr;
					unsigned int qq = q << shift_bits;	
				 	value = s + mid_value + qq; 		
					this_prob = input_dist[value];
					cout << "value = " << value << ", this_prob = " << this_prob << endl;
					prob += this_prob; 
				}
			}
			this_block_dist_right.insert(pair<int, double>(j, prob));
		}
		cout << "this_block_dist_right: " << endl;
		double sum_block_right = 0;
		for (itrm_id = this_block_dist_right.begin(); itrm_id != this_block_dist_right.end(); itrm_id++)
		{
			cout << itrm_id->first << ": " <<  itrm_id->second  << endl;
			sum_block_right += itrm_id->second;
		}
		cout << "sum_block_right = " << sum_block_right << endl;
		block_dist_right.push_back(this_block_dist_right);
	}		
	
	//step3. obtain the distribution for the sum of each block by computing convolution
	vector<map<int, double> > sum_block_dist; 
	for (int i = 0; i < m; i++)
	{
		//obtain PL_prob, GL_prob, KL_prob
		map<int, double> cur_block_dist_left = block_dist_left[i];
		map<int, double> cur_sum_block_dist_left;
		double prob_GL = 0, prob_KL = 0;
		for (int j = 0; j < pow(2, kk+1)-1; j++)
		{
			int value = j;
			double prob = 0;
			for (int r = 0; r <= j; r++)
			{
				int x = r;
				int y = j - r;
				itrm_id = cur_block_dist_left.find(x);
				double prob1 = itrm_id->second;
				itrm_id = cur_block_dist_left.find(y);
				double prob2 = itrm_id->second;
				prob += prob1 * prob2;
			}		
		        cur_sum_block_dist_left.insert(pair<int, double>(value, prob));	
			if (value == pow(2, kk) - 1)
				PL_prob.push_back(prob);
			if (value > pow(2, kk) - 1)
				prob_GL += prob;
			if (value < pow(2, kk) - 1)
				prob_KL += prob;
		}
		GL_prob.push_back(prob_GL);
		KL_prob.push_back(prob_KL);
		sum_block_dist_left.push_back(cur_sum_block_dist_left);

		//obtain PR_prob, GR_prob, KR_prob
		map<int, double> cur_block_dist_right = block_dist_right[i];
		map<int, double> cur_sum_block_dist_right;
		double prob_GR = 0, prob_KR = 0;
		for (int j = 0; j < pow(2, kr+1)-1; j++)
		{
			int value = j;
			double prob = 0;
			for (int r = 0; r <= j; r++)
			{
				int x = r;
				int y = j - r;
				itrm_id = cur_block_dist_right.find(x);
				double prob1 = itrm_id->second;
				itrm_id = cur_block_dist_right.find(y);
				double prob2 = itrm_id->second;
				prob += prob1 * prob2;
			}		
		        cur_sum_block_dist_right.insert(pair<int, double>(value, prob));	
			if (value == pow(2, kr) - 1)
				PR_prob.push_back(prob);
			if (value > pow(2, kr) - 1)
				prob_GR += prob;
			if (value < pow(2, kr) - 1)
				prob_KR += prob;
		}
		GR_prob.push_back(prob_GR);
		KR_prob.push_back(prob_KR);
		sum_block_dist_right.push_back(cur_sum_block_dist_right);
        } 
}
*/
