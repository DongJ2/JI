#include <iostream>
#include "ACA_II.h"
#include <vector>
#include <map>
#include <cmath>
#include <math.h>

using namespace std;

double f(double n)
{
    double u = 1500;
    double sigma = 10;
    double p = 0.01;
    int N = 12;
    //return 1/pow(2,N);
    return exp(-pow(n-u,2)/(2*sigma*sigma))/(sigma*sqrt(2*3.1415926535));
    return pow(1-p,n) * p;
}

int main() {
    vector<int> S = {8,4};
    vector<int> R = {4};
    double prob = 0;
    double MED = 0;
    double MSE= 0;
    map<int,double> pmf,ppp;
    int N = 0;
    int i,j;
    double p = 0;


    for (i = 0; i < S.size(); i++){
        N += S[i];
    }

    int app,acc;
double sum = 0;
    for (i = 0; i < pow(2,N); i++){
            sum = sum + f(i);
        for (j = 0; j < pow(2,N); j++){
            app = ACA_II(i,j,S,R);
            acc = i + j;

            if (app != acc){
                if (pmf.find(acc-app) == pmf.end()){
                    pmf.insert(make_pair(acc-app,0));
                }
                pmf[acc-app] += f(i) * f(j);
            }
        }
    }
    map<int,double> ::iterator it;
    for (it = pmf.begin(); it != pmf.end(); it++){
        cout << it->first << "   " << it->second <<";"<<endl;
        prob += it->second;
        MED += it->first * it->second;
        MSE += it->second * pow(it->first,2);
    }

    cout << "ER: " << prob <<endl;
    cout << "MED: " << MED <<endl;
    cout << "MSE: " << MSE <<endl;
    cout << sum <<endl;
    return 0;
}
