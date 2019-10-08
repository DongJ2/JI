function [cFF,eFF]=filterfunction(PMFA,PMFB,max,n)
error=zeros(1,max*2-1);
aPMF=error;
rPMF=error;
cPMF=error;
ePMF=error;
for i=0:1:max-1
    for j=0:1:max-1
        rPMF(i+j+1)=PMFA(i+1)*PMFB(j+1)+rPMF(i+j+1);
        sum=ACAdder(i,j);
        aPMF(sum+1)=PMFA(i+1)*PMFB(j+1)+aPMF(sum+1);
        if sum~=i+j
            error(abs(sum-i-j))=error(abs(sum-i-j))+PMFA(i+1)*PMFB(j+1);
            ePMF(sum+1)=ePMF(sum+1)+PMFA(i+1)*PMFB(j+1);
        else
            cPMF(sum+1)=cPMF(sum+1)+PMFA(i+1)*PMFB(j+1);
        end
    end
end
P1=PMFA;
P2=PMFB;
for i=max:1:2*max-2
    P1(i+1)=0;
    P2(i+1)=0;
end
cFF=ifft(fft(cPMF)./(fft(P1).*fft(P2)));
eFF=ifft(fft(ePMF)./(fft(P1).*fft(P2)));
end

