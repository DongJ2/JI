#include "PMF.h"

double Pr_err(int L, vector<int> subAdders, vector<int> Rs){
    int i,j;
    double Pr_err = 0;
    double Pr_int;
    vector<int> S;
    for (i = 2; i <= L; i++)
        S.push_back(i);
    vector<vector<int> > P_S = getAllSubsets(S);
    for (i = 1; i < L; i++){
        for (j = 0; j < P_S.size(); j++){
            if (P_S[j].size() == i){
                Pr_int = jointProb(subAdders, Rs, P_S[j]).Pr_int;
                if (i%2 == 0)
                    Pr_err -= Pr_int;
                else
                    Pr_err += Pr_int;
            }
        }
    }
    return Pr_err;
}

//***********************************Algorithm 2***********************************************
errorValue jointProb(vector<int> S, vector<int> R, vector<int> I)
{
    int i,k,t,j;
    vector<vector<int> > r_i;
    errorValue res;
    // Get r_i
    for (i = 2; i <= S.size(); i++){
        vector<int> temp;
        t = 0;
        for (k = 1; k <= i -1; k++){
            t += S[k-1];
        }
        for (j = t - R[i-2]; j <= t - 1; j++)
            temp.push_back(j);
        r_i.push_back(temp);
    }
    vector<vector<int> > R_U_temp;
    // ***********************************
    for (i = 0; i < I.size(); i++) {
        R_U_temp.push_back(r_i[I[i] - 2]);
    }
    vector<int> R_U = unionSet(R_U_temp);
    res.Pr_int = pow(0.5, R_U.size());
    // Get g_i
    vector<vector<int> > g_i;
    for (i = 0; i < I.size(); i++){
        t = 0;
        vector<int> temp;
        for (j = 0; j < I[i] - 1; j++) {
            t += S[j];
        }
        for (j = 0; j <= t; j++)
            temp.push_back(j);
        temp = setMinus(temp, r_i[I[i] - 2]);
        temp = setMinus(temp, R_U);
        g_i.push_back(temp);
    }

    //***************************************
    vector<int> G_I = intersectSet(g_i);

    vector<vector<int> > S_G = {G_I};
    res.Pr_int *= (0.5 - pow(0.5,G_I.size()+1));
    //Get G_D
    vector<vector<int> > G_D;
    for (i = 0; i < g_i.size(); i++){
        vector<int> temp;
        temp = setMinus(g_i[i], G_I);
        if (temp.size() != 0)
            G_D.push_back(temp);
    }

    //*************************************
    for (i = 0; i < G_D.size(); i++){
        G_I = intersectSet(G_D);
        res.Pr_int *= (0.5 + pow(0.5,G_I.size()+1));
        S_G.push_back(G_I);
        for (j = 0; j < G_D.size(); j++){
            G_D[j] = setMinus(G_D[j], G_I);
            if (G_D[j].size() == 0){
                vector<vector<int> > :: iterator temp = find(G_D.begin(), G_D.end(), G_D[j]);
                G_D.erase(temp);
                j--;
                i--;
            }
        }
    }
    // Get error value
    vector<int> s_i ;
    res.V = 0;
    int sum = 0;
    for (i = 0; i < S.size(); i++){
        sum += S[i];
        s_i.push_back(sum);
    }

    for (i = 0; i < S_G.size(); i++){
        for (j = 0 ;j < s_i.size(); j++){
            if (s_i[j] - max(S_G[i]) >= 0){
                res.V += pow(2,s_i[j]);
                break;
            }
        }
    }
    /*
    for (i = 0; i < I.size(); i++)
        cout << I[i] << " ";
    cout << res.Pr_int <<endl;
     */
    return res;
}

//***********************************Algorithm 3***********************************************
map<string, double> getPMF(int L, vector<int> Subadders, vector<int> R)
{
    int i,j,v;
    double sum = 0;
    string key;
    double Pr_i;
    stringstream iStream;
    map<string, double> P_V;
    map<string, double> ::iterator it;
    vector<int> S;
    for (i = 2; i <= L; i++){
        S.push_back(i);
    }
    vector<vector<int> > P_S = getAllSubsets(S);
    for (i = 1; i < L; i++){
        for (j = 0; j < P_S.size(); j++){
            if (P_S[j].size() == i){
                Pr_i = getProb(L, P_S[j], Subadders, R);
                v = jointProb(Subadders ,R, P_S[j]).V;
                key = to_string(v);
                if (P_V.find(key) != P_V.end()){
                    P_V[key] += Pr_i;
                }else{
                    P_V.insert(make_pair(key,Pr_i));
                }
            }
        }
    }
    it = P_V.begin();
    while (it != P_V.end()){
        sum += it->second;
        it++;
    }
    P_V.insert(make_pair("0",1-sum));
    return P_V;
}

//***********************************Algorithm 4***********************************************
double getProb(int L, vector<int> I, vector<int>S, vector<int> R)
{
    int i,j,k;
    double P2 = 0;
    double P2_i,Pr_IJ;
    vector<int> base;
    for (i = 2; i <= L; i++){
        base.push_back(i);
    }
    vector<int> J = setMinus(base, I);
    double P1 = jointProb(S,R,I).Pr_int;
    vector<vector<int> > P_J = getAllSubsets(J);
    for (i = 1; i <= J.size(); i++){
        for (j = 0; j < P_J.size(); j++){
            if (P_J[j].size() == i){
                vector<vector<int> > temp_1 = {I,P_J[j]};
                vector<int> temp = unionSet(temp_1);
                P2_i = jointProb(S,R,temp).Pr_int;
           //     P2_i = 0;
                if (i % 2 == 0)
                    P2 = P2 - P2_i;
                else
                    P2 = P2 + P2_i;
            }
        }
    }
    Pr_IJ = P1 - P2;
    return Pr_IJ;
}

vector< vector<int> > getAllSubsets(vector<int> set)
{
    vector< vector<int> > subset;
    vector<int> empty;
    subset.push_back( empty );

    for (int i = 0; i < set.size(); i++)
    {
        vector< vector<int> > subsetTemp = subset;

        for (int j = 0; j < subsetTemp.size(); j++)
            subsetTemp[j].push_back( set[i] );

        for (int j = 0; j < subsetTemp.size(); j++)
            subset.push_back( subsetTemp[j] );
    }
    return subset;
}


int max(vector<int> v)
{
    int i,m;
    int sum = v[0];
    for (i = 0; i < v.size(); i++){
        if (v[i] > sum)
            sum = v[i];
    }
    return sum;
}

vector<int> unionSet(vector<vector<int> > sets)
{
    vector<int> u;
    int i,j;
    if (sets.size() == 0)
        return u;
    else{
        u = sets[0];
        for (i = 1; i < sets.size(); i++){
            for (j = 0; j < sets[i].size(); j++){
                if (find(u.begin(),u.end(),sets[i][j]) == u.end())
                    u.push_back(sets[i][j]);
            }
        }
    }
    return u;
}

vector<int> setMinus(vector<int> v1, vector<int> v2)
{
    vector<int> res = v1;
    vector<int> :: iterator temp;
    int i;
    for (i = 0; i < v2.size(); i++){
        temp = find(res.begin(), res.end(), v2[i]);
        if ( temp != res.end()){
            res.erase(temp);
        }
    }
    return res;
}

vector<int> intersectSet(vector<vector<int> > sets)
{
    vector<int> u = unionSet(sets);
    int i,j;
    for (i = 0; i < sets.size(); i++){
        for (j = 0; j <u.size(); j++){
            if (find(sets[i].begin(),sets[i].end(), u[j]) == sets[i].end()){
                vector<int > :: iterator temp = find(u.begin(),u.end(),u[j]);
                u.erase(temp);
                j--;
            }
        }
    }
    return u;
}

//*********************************Convolusion*****************
map<string, double> conv(map<string, double> f1, map<string, double> f2)
{
    stringstream iStream;
    int foo,bar,t1,t2,index;
    double sum;
    string key;
    map<string, double> ::iterator it1 = f1.begin();
    map<string, double> res;
    while(it1 != f1.end()){
        iStream.str(it1->first);
        iStream >> foo;
        iStream.clear();
        map<string, double> ::iterator it2 = f2.begin();
        while(it2 != f2.end()){
            iStream.str(it2->first);
            iStream >> bar;
            iStream.clear();
            index = foo + bar;
            key = to_string(index);
            if (res.find(key) == res.end()) {
                sum = 0;
                map<string, double>::iterator temp1 = f1.begin();
                while (temp1 != f1.end()) {
                    map<string, double>::iterator temp2 = f2.begin();
                    iStream.str(temp1->first);
                    iStream >> t1;
                    iStream.clear();
                    while (temp2 != f2.end()) {
                        iStream.str(temp2->first);
                        iStream >> t2;
                        iStream.clear();
                        if (index - t1 == t2) {
                            sum += (temp2->second * temp1->second);
                        }
                        temp2++;
                    }
                    temp1++;
                }
                res.insert(make_pair(key,sum));
            }
            it2++;
        }
        it1++;
    }
    return res;
}
