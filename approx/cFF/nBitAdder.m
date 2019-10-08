function [ add,carryOut ] = nBitAdder(n1,n2,carryIn,n,type)
    if (n == 0)
        add = 0;
        carryOut = 0;
    else
        for i = 1 : 1 : n
            [add(i),carryOut] = oneBitAdder(n1(i),n2(i),carryIn);
            carryIn = carryOut;
        end
    end
    if (type == 1)
        if (carryOut == 1)
            add(n+1) = 1;
        else
            add(n+1) = 0;
        end
    end
end

