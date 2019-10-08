function [ add,carryOut ] = oneBitAdder( n1,n2,carryIn )
    add = xor(xor(n1,n2),carryIn);
    carryOut = or(n1*n2,carryIn*or(n1,n2));
end

