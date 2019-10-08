//
// Created by dell on 2018/1/16.
//

#include <cmath>
#include "ACA_II.h"
#include <iostream>

using namespace std;

int App_Adder(int n1, int n2, vector<int> S, vector<int> R)
{
    int res,pre ;
    int sum = S[0];
    int i;
    res = ((n1 % int(pow(2,S[0]))) + (n2 % int(pow(2,S[0])))) % int(pow(2,S[0]));
    for(i = 1; i < S.size(); i++){
        pre = ((n1 >> (sum - R[i-1])) % int(pow(2,R[i-1]))) + ((n2 >> (sum - R[i-1])) % int(pow(2,R[i-1])));
        if (pre >=  int(pow(2,R[i-1]))){
            if (i != S.size() - 1)
                res += int(pow(2,sum)) * ((1 + ((n1 >> sum) % int(pow(2,S[i]))) + ((n2 >> sum) % int(pow(2,S[i])))) %  int(pow(2,S[i])));
            else
                res += int(pow(2,sum)) * (1 + ((n1 >> sum) % int(pow(2,S[i]))) + ((n2 >> sum) % int(pow(2,S[i]))));
        }else{
            if (i != S.size() - 1)
                res += int(pow(2,sum)) * ((((n1 >> sum) % int(pow(2,S[i]))) + ((n2 >> sum) % int(pow(2,S[i])))) %  int(pow(2,S[i])));
            else
                res += int(pow(2,sum)) * ((n1 >> sum) % int(pow(2,S[i])) + ((n2 >> sum) % int(pow(2,S[i]))));
        }
        sum += S[i];
    }
    return res;
}