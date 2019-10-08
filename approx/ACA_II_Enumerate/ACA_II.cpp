//
// Created by dell on 2018/1/16.
//

#include <cmath>
#include "ACA_II.h"
#include <iostream>

using namespace std;

int ACA_II(int n1, int n2, vector<int> S, vector<int> R)
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

int ACA_II_N_12(int n1, int n2)
{
    int sub1,pre2,sub2;
    sub1 = ((n1 % 256) + (n2 % 256)) % 256;
    pre2 = ((((n1 >> 4) % 16) + ((n2 >> 4) % 16)));
    if (pre2 >= 16){
        sub2 = 1 + ((n1 >> 8) % 16) + ((n2 >> 8) % 16);
    }else{
        sub2 = ((n1 >> 8) % 16) + ((n2 >> 8) % 16);
    }
    return sub1 + 256 * sub2;
}

int ACA_II_N_16(int n1, int n2)
{
    int sub1,sub2,sub3,pre2,pre3;
    sub1 = ((n1 % 256) + (n2 % 256)) % 256;

    pre2 = ((((n1 >> 4) % 16) + ((n2 >> 4) % 16)));
    if (pre2 >= 16){
        sub2 = (1 + ((n1 >> 8) % 16) + ((n2 >> 8) % 16)) % 16;
    }else{
        sub2 = (((n1 >> 8) % 16) + ((n2 >> 8) % 16)) % 16;
    }

    pre3 = ((((n1 >> 8) % 16) + ((n2 >> 8) % 16)));
    if (pre3 >= 16){
        sub3 = 1 + ((n1 >> 12) % 16) + ((n2 >> 12) % 16);
    }else{
        sub3 = ((n1 >> 12) % 16) + ((n2 >> 12) % 16);
    }
    return sub1 + 256 * sub2 + 4096 * sub3;
}

int ACA_II_N_20(int n1, int n2)
{
    int sub1,sub2,sub3,sub4,pre2,pre3,pre4;
    sub1 = ((n1 % 256) + (n2 % 256)) % 256;

    pre2 = ((((n1 >> 4) % 16) + ((n2 >> 4) % 16)));
    if (pre2 >= 16){
        sub2 = (1 + ((n1 >> 8) % 16) + ((n2 >> 8) % 16)) % 16;
    }else{
        sub2 = (((n1 >> 8) % 16) + ((n2 >> 8) % 16)) % 16;
    }

    pre3 = ((((n1 >> 8) % 16) + ((n2 >> 8) % 16)));
    if (pre3 >= 16){
        sub3 = (1 + ((n1 >> 12) % 16) + ((n2 >> 12) % 16)) % 16;
    }else{
        sub3 = (((n1 >> 12) % 16) + ((n2 >> 12) % 16)) % 16;
    }

    pre4 = ((((n1 >> 12) % 16) + ((n2 >> 12) % 16)));
    if (pre4 >= 16){
        sub4 = 1 + ((n1 >> 16) % 16) + ((n2 >> 16) % 16);
    }else{
        sub4 = ((n1 >> 16) % 16) + ((n2 >> 16) % 16);
    }
    return sub1 + 256 * sub2 + 4096 * sub3 + 65536 * sub4;
}