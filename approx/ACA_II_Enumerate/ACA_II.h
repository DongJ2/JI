//
// Created by dell on 2018/1/16.
//
#include<vector>
using namespace std;

#ifndef ACA_II_ACA_II_H
#define ACA_II_ACA_II_H

struct n_bit_out{
    vector<int> add;
    int carryOut;
};

struct one_bit_out{
    int add;
    int carryOut;
};

int ACA_II(int n1, int n2, vector<int> S, vector<int> R);

one_bit_out OneBitAdder(int n1, int n2, int carryIn);

n_bit_out nBitAdder(vector<int>  n1, vector<int>  n2, int carryIn, int n, int type);

int ACA_II(int n1, int n2, int N, vector<int> S, vector<int> R);

void toBinary(int num, vector<int> &res,int N);

int ACA_II_N_12(int n1, int n2);

int ACA_II_N_16(int n1, int n2);

int ACA_II_N_20(int n1, int n2);


#endif //ACA_II_ACA_II_H
