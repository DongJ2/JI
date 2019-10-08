n=8;
A=rand(1,n);
max=pow2(n);
for i=0:1:max-1
    bit=fact(i,n);
    PMF1(i+1)=1;
    for j=1:1:n
        PMF1(i+1)=PMF1(i+1)*A(j)^bit(j)*(1-A(j))^(1-bit(j));
    end
end
B=rand(1,n);
for i=0:1:max-1
    bit=fact(i,n);
    PMF2(i+1)=1;
    for j=1:1:n
        PMF2(i+1)=PMF2(i+1)*B(j)^bit(j)*(1-B(j))^(1-bit(j));
    end
end
C=rand(1,n);
for i=0:1:max-1
    bit=fact(i,n);
    PMF3(i+1)=1;
    for j=1:1:n
        PMF3(i+1)=PMF3(i+1)*C(j)^bit(j)*(1-C(j))^(1-bit(j));
    end
end
[cFF11,eFF11]=filterfunction(PMF1,PMF1,max,n);
[cFF12,eFF12]=filterfunction(PMF1,PMF2,max,n);
[cFF13,eFF13]=filterfunction(PMF1,PMF3,max,n);
[cFF21,eFF21]=filterfunction(PMF2,PMF1,max,n);
[cFF22,eFF22]=filterfunction(PMF2,PMF2,max,n);
[cFF23,eFF23]=filterfunction(PMF2,PMF3,max,n);
[cFF31,eFF31]=filterfunction(PMF3,PMF1,max,n);
[cFF32,eFF32]=filterfunction(PMF3,PMF2,max,n);
[cFF33,eFF33]=filterfunction(PMF3,PMF3,max,n);
for i=max:1:2*max-2
    PMF1(i+1)=0;
    PMF2(i+1)=0;
    PMF3(i+1)=0;
end
Input1=0.2*PMF1+0.2*PMF2+0.6*PMF3;
Input2=0.3*PMF1+0.5*PMF2+0.2*PMF3;
cOUT=0.06*ifft(fft(cFF11).*(fft(PMF1).*fft(PMF1)))+0.1*ifft(fft(cFF12).*(fft(PMF1).*fft(PMF2)))+0.04*ifft(fft(cFF13).*(fft(PMF1).*fft(PMF3)))+0.06*ifft(fft(cFF21).*(fft(PMF2).*fft(PMF1)))+0.1*ifft(fft(cFF22).*(fft(PMF2).*fft(PMF2)))+0.04*ifft(fft(cFF23).*(fft(PMF2).*fft(PMF3)))+0.18*ifft(fft(cFF31).*(fft(PMF3).*fft(PMF1)))+0.3*ifft(fft(cFF32).*(fft(PMF3).*fft(PMF2)))+0.12*ifft(fft(cFF33).*(fft(PMF3).*fft(PMF3)));
eOUT=0.06*ifft(fft(eFF11).*(fft(PMF1).*fft(PMF1)))+0.1*ifft(fft(eFF12).*(fft(PMF1).*fft(PMF2)))+0.04*ifft(fft(eFF13).*(fft(PMF1).*fft(PMF3)))+0.06*ifft(fft(eFF21).*(fft(PMF2).*fft(PMF1)))+0.1*ifft(fft(eFF22).*(fft(PMF2).*fft(PMF2)))+0.04*ifft(fft(eFF23).*(fft(PMF2).*fft(PMF3)))+0.18*ifft(fft(eFF31).*(fft(PMF3).*fft(PMF1)))+0.3*ifft(fft(eFF32).*(fft(PMF3).*fft(PMF2)))+0.12*ifft(fft(eFF33).*(fft(PMF3).*fft(PMF3)));
rPMF=zeros(1,max*2-1);
aPMF=zeros(1,max*2-1);
ePMF=zeros(1,max*2-1);
cPMF=zeros(1,max*2-1);
for i=0:1:max-1
    for j=0:1:max-1
        rPMF(i+j+1)=Input1(i+1)*Input2(j+1)+rPMF(i+j+1);
        sum=ACAdder(i,j);
        aPMF(sum+1)=Input1(i+1)*Input2(j+1)+aPMF(sum+1);
        if sum~=i+j
            ePMF(sum+1)=ePMF(sum+1)+Input1(i+1)*Input2(j+1);
        else
            cPMF(sum+1)=cPMF(sum+1)+Input1(i+1)*Input2(j+1);
        end
    end
end
