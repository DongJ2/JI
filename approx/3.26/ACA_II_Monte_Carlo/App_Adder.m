function [ res ] = App_Adder(n1,n2,S,R)
    sum = S(1);
    res = mod(mod(n1,power(2,S(1))) + mod(n2,power(2,S(1))), power(2,S(1)));
    for i = 2 : length(S)
       pre = mod(bitshift(n1,R(i-1)-sum),power(2,R(i-1))) +   mod(bitshift(n2,R(i-1)-sum),power(2,R(i-1)));
       if (pre >= power(2,R(i-1)))
            if (i ~= length(S))
                res = res + power(2,sum) * mod((1 + mod(bitshift(n1,-sum),power(2,S(i))) + mod(bitshift(n2,-sum),power(2,S(i)))),power(2,S(i)));
            else
                res = res + power(2,sum) * (1 + mod(bitshift(n1,-sum),power(2,S(i))) + mod(bitshift(n2,-sum),power(2,S(i))));
            end
       else
           if (i ~= length(S))
               res = res + power(2,sum) * mod((mod(bitshift(n1,-sum),power(2,S(i))) + mod(bitshift(n2,-sum),power(2,S(i)))),power(2,S(i)));
           else
               res = res + power(2,sum) * (mod(bitshift(n1,-sum),power(2,S(i))) + mod(bitshift(n2,-sum),power(2,S(i))));
           end
       end
       sum = sum + S(i);
    end
end

