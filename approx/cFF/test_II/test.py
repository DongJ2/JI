from scipy.fftpack import fft, ifft
import random

def bitget(n,l):
    bit=[0 for i in range(l)]
    i=l-1
    while i>=0:
        if n>=2**i:
            n=n-2**i
            bit[i]=1
        i=i-1
    return bit

def xor(a,b):
    return (a and (not b)) or ((not a) and b)

def oneBitAdder(n1,n2,carryIn):
    add=xor(xor(n1,n2),carryIn)
    carryOut=(n1*n2) or (carryIn * (n1 or n2))
    return add, carryOut

def nBitAdder(n1,n2,carryIn,n,type):
    if (n==0):
        add=0
        carryOut=0
    else:
        add=[0 for i in range(n)]
        for i in range(1,n+1):
            add[i-1],carryOut=oneBitAdder(n1[i-1],n2[i-1],carryIn)
            carryIn=carryOut
    if (type==1):
        if (carryOut==1):
            add.append(1)
        else:
            add.append(0)
    return add,carryOut

def ACAdder(n1,n2):
    res=0
    N=16
    L=3
    sum_sum=0
    S=[8,4,4]
    R=[4,4]
    n1_bin=bitget(n1,N)
    n2_bin=bitget(n2,N)
    carryIn=0
    sum=[0 for i in range(17)]
    for i in range(1,L+1):
        if (i!=L):
            sum[sum_sum:sum_sum+S[i-1]],carryOut=nBitAdder(n1_bin[sum_sum:sum_sum+S[i-1]],n2_bin[sum_sum:sum_sum+S[i-1]],carryIn,S[i-1],0)
            sum_sum=sum_sum+S[i-1]
            s,carryIn=nBitAdder(n1_bin[sum_sum-R[i-1]:sum_sum],n2_bin[sum_sum-R[i-1]:sum_sum],0,R[i-1],0)
        else:
            sum[sum_sum:sum_sum + S[i - 1]+1], carryOut = nBitAdder(n1_bin[sum_sum:sum_sum + S[i - 1]],n2_bin[sum_sum:sum_sum + S[i - 1]], carryIn, S[i - 1],1)
    for i in range(1,N+2):
        res=res+sum[i-1]*(2**(i-1))
    return res

def bitMultiply(n1,n2):
    n=[0]*len(n1)
    i=0
    while i<len(n1):
        n[i]=n1[i]*n2[i]
        i=i+1
    return n

def bitDivision(n1,n2):
    n=[0]*len(n1)
    i=0
    while i<len(n1):
        n[i]=n1[i]/n2[i]
        i=i+1
    return n

def filterfunction(PMF1,PMF2,max,n,type):
    PMFA=[0]*len(PMF1)
    PMFB=[0]*len(PMF2)
    for i in range(len(PMF1)):
        PMFA[i]=PMF1[i]
    for i in range(len(PMF2)):
        PMFB[i]=PMF2[i]
    error=[0 for i in range(max*2-1)]
    aPMF=[0 for i in range(max*2-1)]
    rPMF=[0 for i in range(max*2-1)]
    cPMF=[0 for i in range(max*2-1)]
    ePMF=[0 for i in range(max*2-1)]
    for i in range(max):
        for j in range(max):
            rPMF[i+j]=PMFA[i]*PMFB[j]+rPMF[i+j]
            if type==0:
                sum=ACAdder(i,j)
            else:
                if type==1:
                    sum=ETAII(i,j,n,2)
                else:
                    sum=i+j
            aPMF[sum]=aPMF[sum]+PMFA[i]*PMFB[j]
            if sum != i+j:
                error[abs(sum-i-j)]=error[abs(sum-i-j)]+PMFA[i]*PMFB[j]
                ePMF[sum]=ePMF[sum]+PMFA[i]*PMFB[j]
            else:
                cPMF[sum]=cPMF[sum]+PMFA[i]*PMFB[j]
    for i in range(max,2*max-1):
        PMFA.append(0)
        PMFB.append(0)
    cFF=ifft(bitDivision(fft(cPMF),bitMultiply(fft(PMFA),fft(PMFB))))
    eFF=ifft(bitDivision(fft(ePMF),bitMultiply(fft(PMFA),fft(PMFB))))
    return cFF,eFF

def Carry_Generate(a,b,cin):
    p=xor(a,b)
    g=a and b
    k=not(a or b)
    if (k==1):
        cout=0
    if (g==1):
        cout=1
    if (p==1):
        cout=cin
    return cout


def ETAII(in1,in2,N,Q):
    M=(N//Q)+1
    cout=[0]* N
    sum=[0]*(N+1)
    a=bitget(in1,N)
    b=bitget(in2,N)
    for i in range(1,Q):
        if (i==1):
            cout[i-1]=Carry_Generate(a[i-1],b[i-1],0)
        else:
            cout[i-1]=Carry_Generate(a[i-1],b[i-1],cout[i-2])
    for i in range(Q,N+1):
        if (i==1):
            cout[i-1]=Carry_Generate(a[i-1],b[i-1],0)
        else:
            if i%(N//M)==0 and i!=N:
                temp_carry=0
                j=Q//2-1
                while j>=0:
                    if (i-j)>0:
                        temp_carry=Carry_Generate(a[i-j-1],b[i-j-1],temp_carry)
                    j=j-1
                cout[i-1]=temp_carry
            else:
                cout[i-1]=Carry_Generate(a[i-1],b[i-1],cout[i-2])
    for i in range(1,N+1):
            if (i==1):
                sum[i-1]=xor(a[i-1],xor(b[i-1],0))
            else:
                sum[i-1]=xor(a[i-1],xor(b[i-1],cout[i-2]))
    sum[N]=cout[N-1]
    result=0
    for i in range(len(sum)):
        if sum[i]==1 or sum[i]==True:
            result=result+2**i
    return result



'''
n=8
A=[0.2,0.3,0.5,0.3,0.7,0.1,0.4,0.2]
max=2**8
PMF1=[1]*max
for i in range(max):
    bit=bitget(i,n)
    for j in range(n):
        PMF1[i]=PMF1[i]*(A[j]**bit[j])*((1-A[j])**(1-bit[j]))
cFF11,eFF11=filterfunction(PMF1,PMF1,max,n)
B=[0.6,0.5,0.3,0.1,0.2,0.4,0.7,0.8]
PMF2=[1]*max
for i in range(max):
    bit=bitget(i,n)
    for j in range(n):
        PMF2[i]=PMF2[i]*(B[j]**bit[j])*((1-B[j])**(1-bit[j]))
cFF22,eFF22=filterfunction(PMF2,PMF2,max,n)
cFF12,eFF12=filterfunction(PMF1,PMF2,max,n)
cFF21,eFF21=filterfunction(PMF2,PMF1,max,n)
PMF3=[0]*max
for i in range(max):
    PMF3[i]=0.4*PMF1[i]+0.6*PMF2[i]
for i in range(max,2*max-1):
    PMF1.append(0)
    PMF2.append(0)
cPMF=[0 for i in range(max*2-1)]
ePMF=[0 for i in range(max*2-1)]
for i in range(max):
    for j in range(max):
        sum=ACAdder(i,j)
        if i+j==sum:
            cPMF[sum]=cPMF[sum]+PMF3[i]*PMF3[j]
        else:
            ePMF[sum]=ePMF[sum]+PMF3[i]*PMF3[j]
print(cPMF)
P1=ifft(bitMultiply(fft(cFF11),bitMultiply(fft(PMF1),fft(PMF1))))
P2=ifft(bitMultiply(fft(cFF12),bitMultiply(fft(PMF1),fft(PMF2))))
P3=ifft(bitMultiply(fft(cFF21),bitMultiply(fft(PMF2),fft(PMF1))))
P4=ifft(bitMultiply(fft(cFF22),bitMultiply(fft(PMF2),fft(PMF2))))
cOUT=[0]*len(P1)
for i in range(len(P1)):
    cOUT[i]=0.16*P1[i]+0.24*P2[i]+0.24*P3[i]+0.36*P4[i]
print(cOUT)
'''
