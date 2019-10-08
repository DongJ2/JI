import random

def Q(A,B):
    n=0
    for i in range(len(A)):
        n=n+abs(A[i]-B[i])
    return n

I1=[0]*2**8
I2=[0]*2**8
I3=[0]*2**8
I4=[0]*2**8
