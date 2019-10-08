function [ res ] = f( n,mu,sigma )
    res = exp(-power(n-mu,2)/(2*sigma*sigma))/(sigma*sqrt(2*pi));
end

