function [res] = ACAdder( n1,n2 )
    res = 0;
    N = 16;
    L = 3;
    sum_sum = 0;
    S = [8,4,4];
    R = [4,4];
    n1_bin = bitget(n1,1:1:N);
    n2_bin = bitget(n2,1:1:N);
    carryIn = 0;
    for i = 1 : 1 : L
       if (i ~= L)
           [sum(sum_sum + 1 : sum_sum + S(i)),~] = nBitAdder(n1_bin(sum_sum +1 : sum_sum + S(i)), n2_bin(sum_sum +1: sum_sum + S(i)), carryIn, S(i) , 0);
           sum_sum = sum_sum + S(i);
           [~,carryIn] = nBitAdder(n1_bin(sum_sum +1 - R(i) : sum_sum), n2_bin(sum_sum +1 - R(i) : sum_sum), 0, R(i),0);   
       else
           sum(sum_sum+1 : sum_sum + S(i) + 1) = nBitAdder(n1_bin(sum_sum + 1 : sum_sum + S(i)), n2_bin(sum_sum + 1: sum_sum + S(i)),carryIn, S(i) , 1);
       end  
    end
    
    for i = 1: 1 : N+1
         res = res + sum(i) * 2^(i-1);
    end
end

