function Result = GDA(in1,in2,N,M,P)
% in1       = Input 1                       = 121
% in2       = Input 2                       = 55
% N         = Opernad Total Number of Bits  = 8
% M         = Total Number of Partitions    = 4
% P         = Prediction Bits Used          = 2
% Result    = in1 + in2

cout        = zeros(1,N);           % Array Containing Carry Bits
sum         = zeros(1,N+1);         % Array Containing Sum Bits

for i = 1:N
    a   = bitget(in1,i);
    b   = bitget(in2,i);
    
    if(i==1)
        cout(i)   = Carry_Generate(a,b,0);
    elseif((mod(i,N/M)==0) && (i~=N))
        temp_carry = 0;
        for j = P-1:-1:0
            if((i-j)>0)
                a   = bitget(in1,i-j);
                b   = bitget(in2,i-j);
                temp_carry = Carry_Generate(a,b,temp_carry);
            end
        end
        cout(i)   = temp_carry;
    else
        cout(i) = Carry_Generate(a,b,cout(i-1));
    end
end

for i = 1:N
    a           = bitget(in1,i);
    b           = bitget(in2,i);
    if(i == 1)
        sum(i) = xor(a,xor(b,0));
    else
        sum(i) = xor(a,xor(b,cout(i-1)));
    end
end

sum (N+1) = cout(N);
Result = bi2de(sum);
