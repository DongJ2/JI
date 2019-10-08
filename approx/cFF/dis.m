n=8;
A=rand(1,n);
max=pow2(n);
for i=0:1:max-1
    bit=fact(i,n);
    PMFA(i+1)=1;
    for j=1:1:n
        PMFA(i+1)=PMFA(i+1)*A(j)^bit(j)*(1-A(j))^(1-bit(j));
    end
end
