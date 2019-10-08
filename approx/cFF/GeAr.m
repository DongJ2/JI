function Result = GeAr(in1,in2,N,R,P)
% in1       = Input 1                                   = 121
% in2       = Input 2                                   = 55
% N         = Opernad Total Number of Bits              = 8
% R         = Resultant Bits of Sub-Adder               = 2
% P         = Previous/Prediction Bits of Sub-Adder     = 2
% Result    = in1 + in2

cout        = zeros(1,N);           % Array Containing Carry Bits
sum         = zeros(1,N+1);         % Array Containing Sum Bits
L           = R + P;                % Length of Sub-Adder

for i = 1:L-1                % Carry Generation for First Sub-Adder
    a   = bitget(in1,i,'int64');
    b   = bitget(in2,i,'int64');
    
    if(i==1)
        cout(i)   = Carry_Generate(a,b,0);
    else
        cout(i)   = Carry_Generate(a,b,cout(i-1));
    end
end

count = R;
for i = L:N                 % Carry Generation for Remaining Sub-Adders
    a   = bitget(in1,i,'int64');
    b   = bitget(in2,i,'int64');
    
    if( (count == R) && (i ~= N ))
        count = 0;
        temp_carry = 0;
        for j = P-1:-1:0
            a   = bitget(in1,i-j,'int64');
            b   = bitget(in2,i-j,'int64');
            temp_carry  = Carry_Generate(a,b,temp_carry);
        end
        cout(i)   = temp_carry;
    else
        cout(i)    = Carry_Generate(a,b,cout(i-1));
    end
    count = count + 1;
end

for i = 1:N                 % Sum Generation for All Sub-Adders
    a           = bitget(in1,i,'int64');
    b           = bitget(in2,i,'int64');
    if(i == 1)
        sum(i) = xor(a,xor(b,0));
    else
        sum(i) = xor(a,xor(b,cout(i-1)));
    end
end

sum (N+1) = cout(N);
Result = bi2de(sum);
