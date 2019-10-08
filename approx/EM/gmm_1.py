import numpy as np
import random
import matplotlib.pyplot as plt
from time import clock
def gaussian(x,mu,sigma):
    temp = -np.square(x-mu)/(2*sigma)
    return np.exp(temp)/(np.sqrt(2.0*np.pi*sigma))
def e_step(data, phais, mus, sigmas):
    Qs = []
    for i in range(len(data)):
        q = [phai*gaussian(data[i],mu,sigma) for phai,mu,sigma in zip(phais,mus,sigmas)]
        Qs.append(q)
    Qs = np.array(Qs)
    Qs = Qs / np.sum(Qs,axis=1).reshape(-1,1)
    return Qs
def m_step(data, omega, mu, sigma, Qs):
    data = np.array(data)
    gama_j = np.sum(Qs,axis=0)
    new_omega = gama_j/len(data)
    mu_temp = np.sum(Qs*(data.reshape(-1,1)),axis=0)
    new_mu =mu_temp/gama_j
    X_i_mu_j = np.square(np.array([data]).reshape(-1,1)-np.array([mu]))
    new_sigma = np.sum(Qs*X_i_mu_j,axis=0)/gama_j
    return new_omega,new_mu,new_sigma
def EM(data,k=1):
    omega = [1.0/k for i in range(k)]
    mu = [i for i in range(k)]
    sigma = [1 for i in range(k)]
    for i in range(100):
        Qs = e_step(data,omega,mu,sigma)
        omega, mu, sigma= m_step(data,omega,mu,sigma,Qs)
        print (omega,mu,sigma)


s1 = []
n=1
for i in range(2**12):
    j=random.random()
    s1.append(j*n)
    n=n*(1-j)
s2 = np.random.normal(25,1,10000)
t=clock()
EM(s1,4)
t=clock()-t
print(t)