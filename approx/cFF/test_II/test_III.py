from test import bitget, xor, oneBitAdder, nBitAdder, ACAdder, bitMultiply, bitDivision, filterfunction,ETAII
from scipy.fftpack import fft, ifft
import random
import string
import numpy as np
from test_II import bitAdd, generate_distribution
from math import sqrt
from time import clock

def divide(PMF,num):
    C=[]
    for i in range(len(PMF)//num):
        s=0
        for j in range(16):
            s=s+PMF[i*num+j]
        C.append(s)
    return C

n=8
max=2**n
Input_Distribution=[]
for i in range(max//16):
    D=generate_distribution([16*i,16*i+1,16*i+2,16*i+3,16*i+4,16*i+5,16*i+6,16*i+7,16*i+8,16*i+9,16*i+10,16*i+11,16*i+12,16*i+13,16*i+14,16*i+15],max)
    Input_Distribution.append(D)


'''
cFF=[[] for i in range(max//16)]
eFF=[[] for i in range(max//16)]
c=[]
e=[]
k=1
for i in range(max//16):
    for j in range(max//16):
        tem_cFF,tem_eFF=filterfunction(Input_Distribution[i],Input_Distribution[j],max,n,0)
        cFF[i].append(tem_cFF)
        eFF[j].append(tem_eFF)
        
        c.append(tem_cFF)
        e.append(tem_eFF)
        cFF_array = np.array(c)
        np.savetxt('8_cFF' + str(k) + '.csv', cFF_array, delimiter=',')
        eFF_array = np.array(e)
        np.savetxt('8_eFF' + str(k) + '.csv', eFF_array, delimiter=',')
        k = k + 1
        c = []
        e = []
        '''

A=[0.5,0.5,0.5,0.5,0.4,0.6,0.2,0.3]
PMF1=[1]*max
for i in range(max):
    bit=bitget(i,n)
    for j in range(n):
        PMF1[i]=PMF1[i]*(A[j]**bit[j])*((1-A[j])**(1-bit[j]))
B=[0.5,0.5,0.5,0.5,0.5,0.8,0.2,0.3]
PMF2=[1]*max
for i in range(max):
    bit=bitget(i,n)
    for j in range(n):
        PMF2[i]=PMF2[i]*(B[j]**bit[j])*((1-B[j])**(1-bit[j]))
C1=divide(PMF1,16)
C2=divide(PMF2,16)
cPMF=[0 for i in range(max*2-1)]
ePMF=[0 for i in range(max*2-1)]
for i in range(max):
    for j in range(max):
        sum=ETAII(i,j,n,2)
        if i+j==sum:
            cPMF[sum]=cPMF[sum]+PMF1[i]*PMF2[j]
        else:
            ePMF[sum]=ePMF[sum]+PMF1[i]*PMF2[j]
for i in range(max,2*max-1):
    PMF1.append(0)
    PMF2.append(0)
    for j in range(len(Input_Distribution)):
        Input_Distribution[j].append(0)
cOUT=[0]*len(PMF1)
for i in range(len(C1)):
    for j in range(len(C2)):
        cOUT=bitAdd(cOUT,ifft(bitMultiply(fft(cFF[i][j]),bitMultiply(fft(Input_Distribution[i]),fft(Input_Distribution[j])))),C1[i]*C2[j])
s=0
cOUT1=[]
for i in cOUT:
    cOUT1.append(i.real)
for i in range(len(cPMF)):
    print(cPMF[i],cOUT1[i])
HD=0
for i in range(len(cPMF)):
    HD=HD+(sqrt(cPMF[i])-sqrt(cOUT1[i]))**2
HD=sqrt(HD)/sqrt(2)
print(HD)

