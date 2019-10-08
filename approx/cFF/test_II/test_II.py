from test import bitget, xor, oneBitAdder, nBitAdder, ACAdder, bitMultiply, bitDivision, filterfunction,ETAII
from scipy.fftpack import fft, ifft
import random
import string
import numpy as np
from math import sqrt
from time import clock

def bitAdd(A,B,k):
    C=[0]*len(A)
    for i in range(len(A)):
        C[i]=A[i]+B[i]*k
    return C

def generate_distribution(D,n):
    dis=[0]*n
    x=1/len(D)
    for i in D:
        dis[i]=x
    return dis

def divide(PMF,bit_num,p):
    l=len(PMF)
    C=[0 for i in range(l//bit_num)]
    k=1/bit_num
    for i in range(len(C)):
        C[i]=(PMF[2*i]*(1-p)+PMF[2*i+1]*p)/k
    return C

n=12
max=2**n
I1=[]
I2=[]
cFF=[]
eFF=[]
for i in range(2**13):
    I1.append(random.random())
    I2.append(random.random())
    cFF.append(random.random())
    eFF.append(random.random())
t=clock()
bitAdd(I1,I2,0.4)
t=clock()-t
print(t)

'''
n=4
max=2**n
Input_Distribution=[]
for i in range(8):
    D=generate_distribution([2*i,2*i+1],max)
    Input_Distribution.append(D)
cFF=[[] for i in range(8)]
eFF=[[] for i in range(8)]
for i in range(8):
    for j in range(8):
        tem_cFF,tem_eFF=filterfunction(Input_Distribution[i],Input_Distribution[j],max,n,1)
        cFF[i].append(tem_cFF)
        eFF[j].append(tem_eFF)

PMF1=[0]* 16
k=1
for i in range(len(PMF1)-1):
    j=random.uniform(0,k)
    k=k-j
    PMF1[i]=j
PMF1[len(PMF1)-1]=k
random.shuffle(PMF1)
PMF2=[0]*16
k=1
for i in range(len(PMF2)-1):
    j=random.uniform(0,k)
    k=k-j
    PMF2[i]=j
PMF2[len(PMF2)-1]=k
random.shuffle(PMF2)

t=0
HD_ave=0
HD_e=0
t1=[]
t2=[]
while t<1000:
    t=t+1
    A=[]
    B=[]
    for i in range(4):
        A.append(random.random())
        B.append(random.random())
    A[0]=random.uniform(0.2,0.8)
    B[0]=random.uniform(0.2,0.8)
    PMF1=[1]*max
    for i in range(max):
        bit=bitget(i,n)
        for j in range(n):
            PMF1[i]=PMF1[i]*(A[j]**bit[j])*((1-A[j])**(1-bit[j]))
    PMF2=[1]*max
    for i in range(max):
        bit=bitget(i,n)
        for j in range(n):
            PMF2[i]=PMF2[i]*(B[j]**bit[j])*((1-B[j])**(1-bit[j]))
    C1=divide(PMF1,2,A[0])
    C2=divide(PMF2,2,B[0])
    cPMF=[0 for i in range(max*2-1)]
    ePMF=[0 for i in range(max*2-1)]
    tem_time=clock()
    for i in range(max):
        for j in range(max):
            sum=ETAII(i,j,n,2)
            if i+j==sum:
                cPMF[sum]=cPMF[sum]+PMF1[i]*PMF2[j]
            else:
                ePMF[sum]=ePMF[sum]+PMF1[i]*PMF2[j]
    t1.append(clock()-tem_time)
    for i in range(max,2*max-1):
        PMF1.append(0)
        PMF2.append(0)
        if t==1:
            for j in range(len(Input_Distribution)):
                Input_Distribution[j].append(0)
    cOUT=[0]*len(PMF1)
    eOUT=[0]*len(PMF1)
    tem_time=clock()
    for i in range(len(C1)):
        for j in range(len(C2)):
            cOUT=bitAdd(cOUT,ifft(bitMultiply(fft(cFF[i][j]),bitMultiply(fft(Input_Distribution[i]),fft(Input_Distribution[j])))),C1[i]*C2[j])
            eOUT = bitAdd(eOUT, ifft(
                bitMultiply(fft(eFF[i][j]), bitMultiply(fft(Input_Distribution[i]), fft(Input_Distribution[j])))),
                          C1[i] * C2[j])
    t2.append(clock()-tem_time)
    cOUT1=[]
    eOUT1=[]
    for i in cOUT:
        cOUT1.append(i.real)
    for i in eOUT:
        eOUT1.append(i.real)
    aPMF=bitAdd(cOUT1,eOUT1,1)
    rPMF=bitAdd(cPMF,ePMF,1)
    HD=0
    for i in range(len(rPMF)):
        HD=HD+(sqrt(rPMF[i])-sqrt(aPMF[i]))**2
    HD=sqrt(HD)/sqrt(2)
    HD_ave=HD_ave+HD
print(HD_ave/1000)
time1=0
time2=0
for i in range(1000):
    time1=time1+t1[i]
    time2=time2+t2[i]
print(time1/1000)
print(time2/1000)





k=1
for i in Input_Distribution:
    for j in Input_Distribution:
        cFF1,eFF1=filterfunction(i,j,max,n,1)
        cFF.append(cFF1)
        eFF.append(eFF1)
    cFF_array=np.array(cFF)
    np.savetxt('cFF'+str(k)+'.csv',cFF_array,delimiter=',')
    eFF_array=np.array(eFF)
    np.savetxt('eFF'+str(k)+'.csv',eFF_array,delimiter=',')
    k=k+1
    cFF=[]
    eFF=[]
 '''

