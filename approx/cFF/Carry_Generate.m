function cout = Carry_Generate(a,b,cin)
    p       = xor(a,b);
    g       = and(a,b);
    k    = not(or(a,b));
    
    if(k==1)
        cout = 0;
    end
    if(g==1)
        cout = 1;
    end
    if(p==1)
        cout = cin; 
    end
end