#include <iostream>
#include <cmath>
#include <ctime>
#include <random>
#include "ACA_II.h"
#include <map>

using namespace std;

int main() {
    double sum = 0;
    srand((unsigned)(time(NULL)));
    default_random_engine generator;
//    int mu = 500000;
//    int sigma = 70000;
    double Monte_Carlo_prob;
    double acc_prob;
    double hd = 0;
    int N = 20;
//    normal_distribution<double> distribution(mu,sigma);
    int Monte_Carlo_Num = 1000000;

    int loop_num = 500;
    map<int,double> probs;
    map<int,double> :: iterator it;
    map<int,double> accurate_distribution;
    map<int,double> :: iterator acc_it;
    accurate_distribution.insert(make_pair(256,0.0284386));
    accurate_distribution.insert(make_pair(4096,0.0292969));
    accurate_distribution.insert(make_pair(65536,0.0284386));
    accurate_distribution.insert(make_pair(65792,0.000858307));

    clock_t begin,end,time;
    int i,j;
    long num1,num2;
    long accurate,approximate,diff;
    int discard = 0;

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
            num1 = long((double)rand()/RAND_MAX * (long)(pow(2,N)-1));
            num2 = long((double)rand()/RAND_MAX * (long)(pow(2,N)-1));

            if (num1 < 0 || num1 >= pow(2, N) || num1 < 0 || num2 > pow(2, N)) {
                discard++;
                continue;
            }
            accurate = num1 + num2;

            approximate = ACA_II_N_20(num1, num2);
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
        Monte_Carlo_prob = 0;
        acc_prob = 0;
        int effect = Monte_Carlo_Num - discard;

        for (it = probs.begin(); it != probs.end(); it++){
         //   cout << it->first << " " << it->second/effect <<endl;
            acc_it = accurate_distribution.find(it->first);
            sum += pow(sqrt(acc_it->second) - sqrt(it->second/effect),2);
            Monte_Carlo_prob += it->second/effect;
            acc_prob += acc_it->second;
        }
        sum += pow(sqrt(1 - acc_prob) - sqrt(1-Monte_Carlo_prob),2);
        hd += sqrt(sum)/sqrt(2);
    }




    cout << "Time is " << (double)(time)/CLOCKS_PER_SEC/loop_num << "s" << endl;
    cout << "The Helinger distance is " << hd/loop_num <<endl;


}