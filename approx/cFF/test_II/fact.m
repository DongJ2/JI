function Result=fact(n,l)
bit=zeros(1,l);
for i=l:-1:1
    if n>=pow2(i-1)
        n=n-pow2(i-1);
        bit(i)=1;
    end
end
Result=bit;