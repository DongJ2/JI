#include <iostream>
#include <cmath>
#include <ctime>
#include <random>
#include "ACA_II.h"
#include <vector>
#include <map>

using namespace std;

int main() {
    int sum=0;
    srand((unsigned)(time(NULL)));
    default_random_engine generator;
    int mu = 1500;
    int sigma = 100;
    double acc_prob;
    double hd = 0;

    int N = 0;
//    normal_distribution<double> distribution(mu,sigma);
    int Monte_Carlo_Num = 100000;
    vector<int> S = {8,4};
    vector<int> R = {4};

    int loop_num = 10;
    map<int,double> probs;
    map<int,double> :: iterator it;
    map<int,double> accurate_distribution;
    map<int,double> Monte_Carlo_distribution;
    map<int,double> :: iterator acc_it;
    accurate_distribution.insert(make_pair(256,0.0292537));
    double ER, MED, MSE;
    ER = 0.0292537;
    MED = 7.48894;
    MSE = 1917.17;

    clock_t begin,end,time;
    int i,j;
    long num1,num2;
    double u1,u2,z0;
    long accurate,approximate,diff;
    double Monte_Carlo_ER = 0;
    double temp_ER = 0;
    int discard = 0;
    for (i = 0; i < S.size(); i++){
        N += S[i];
    }

    time = 0;
    for (j = 0; j < loop_num; j++) {
        begin = clock();
        sum = 0;
        probs.clear();
        discard = 0;
        for (i = 0; i < Monte_Carlo_Num; i++) {
            /*
            distribution.reset();
            num1 = (int) distribution(generator);
            distribution.reset();
            num2 = (int) distribution(generator);
*/
           // num1 = long((double)rand()/RAND_MAX * (long)(pow(2,N)-1));
           // num2 = long((double)rand()/RAND_MAX * (long)(pow(2,N)-1));

            do
            {
                u1 = rand() * (1.0 / RAND_MAX);
                u2 = rand() * (1.0 / RAND_MAX);
                z0 = sqrt(-2 * log(u1)) * cos(2 * 3.1415926535 * u2);
                num1 = round(z0 * sigma + mu);
            }
            while ( num1 < 0 | num1 > pow(2,12));
            do
            {
                u1 = rand() * (1.0 / RAND_MAX);
                u2 = rand() * (1.0 / RAND_MAX);
                z0 = sqrt(-2 * log(u1)) * cos(2 * 3.1415926535 * u2);
                num2 = round(z0 * sigma + mu);
            }
            while ( num2 < 0 | num2 > pow(2,12));
            if (num1 < 0 || num1 >= pow(2, N) || num1 < 0 || num2 > pow(2, N)) {
                discard++;
                continue;
            }
            accurate = num1 + num2;

            approximate = App_Adder(num1, num2, S, R);
            if (accurate != approximate) {
                diff = accurate - approximate;
                if (probs.find(diff) == probs.end()) {
                    probs.insert(make_pair(diff, 0));
                }
                probs[diff]++;
            }
        }
        end = clock();
        time += end - begin;
        int effect = Monte_Carlo_Num - discard;
        temp_ER = 0;
        for (it = probs.begin(); it != probs.end(); it++){
         //   cout << it->first << " " << it->second/effect <<endl;
            Monte_Carlo_distribution[it->first] += it->second/effect/loop_num;
            temp_ER += it->second/effect;
        }
        Monte_Carlo_ER += abs(temp_ER-ER)/ER;
        //cout<<j<<" "<<temp_ER<<" "<<abs(temp_ER-ER)/ER<<endl;
    }
    double Monte_Carlo_prob = 0;
    double Monte_Carlo_MED = 0;
    double Monte_Carlo_MSE = 0;
    for (it = Monte_Carlo_distribution.begin(); it != Monte_Carlo_distribution.end(); it++){
        acc_it = accurate_distribution.find(it->first);
        hd += pow(sqrt(acc_it->second) - sqrt(it->second),2);
        Monte_Carlo_prob += it->second;
        Monte_Carlo_MED += it->first * it->second;
        Monte_Carlo_MSE += it->second * pow(it->first,2);
        cout << it->first << "  " << it->second <<endl;
    }
    hd = sqrt(hd/2);
    cout << "Average Relative Error = " << Monte_Carlo_ER/loop_num<<endl;
    cout << "Monte Carlo Error Rate = " << Monte_Carlo_prob << "(" << abs(Monte_Carlo_prob - ER)/ER << ")" <<endl;
    cout << "Monte Carlo MED = " << Monte_Carlo_MED << "(" << abs(Monte_Carlo_MED - MED)/MED << ")"  <<endl;
    cout << "Monte Carlo MSE = " << Monte_Carlo_MSE << "(" << abs(Monte_Carlo_MSE - MSE)/MSE << ")"  <<endl;
    cout << "Hellinger distance = " << hd <<endl;
    cout << "Time is " << (double)(time)/CLOCKS_PER_SEC/loop_num << "s" << endl;
}
