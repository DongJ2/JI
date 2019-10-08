n=8;
A=[0.2,0.3,0.5,0.3,0.7,0.1,0.4,0.2];
B=A;
max=pow2(n);
error=zeros(1,max*2-1);
aPMF=zeros(1,max*2-1);
rPMF=zeros(1,max*2-1);
ePMF=zeros(1,max*2-1);
cPMF=zeros(1,max*2-1);
for i=0:1:max-1
    bit=fact(i,n);
    PMFA(i+1)=1;
    PMFB(i+1)=1;
    for j=1:1:n
        PMFA(i+1)=PMFA(i+1)*A(j)^bit(j)*(1-A(j))^(1-bit(j));
        PMFB(i+1)=PMFB(i+1)*B(j)^bit(j)*(1-B(j))^(1-bit(j));
    end
end
%PMFD=0.4*PMFA+0.6*PMFB;
%PMFA=PMFD;
%PMFB=PMFD;
for i=0 : 1 : max-1
    for j=0 : 1 : max-1
        rPMF(i+j+1)=PMFA(i+1)*PMFB(j+1)+rPMF(i+j+1);
        sum=ACAdder(i,j);
        aPMF(sum+1)=PMFA(i+1)*PMFB(j+1)+aPMF(sum+1);
        if sum~=i+j
            i
            j
            error(abs(sum-i-j))=error(abs(sum-i-j))+PMFA(i+1)*PMFB(j+1);
            ePMF(sum+1)=ePMF(sum+1)+PMFA(i+1)*PMFB(j+1);
        else
            cPMF(sum+1)=cPMF(sum+1)+PMFA(i+1)*PMFB(j+1);
        end
    end
end
for i=max : 1 : 2*max-2
    PMFA(i+1)=0;
    PMFB(i+1)=0;
end
cFF=ifft(fft(cPMF)./(fft(PMFA).*fft(PMFB)));
eFF=ifft(fft(ePMF)./(fft(PMFA).*fft(PMFB)));
fprintf("cFF\n");
cFF
fprintf("eFF\n");
eFF
fprintf("error\n");
error