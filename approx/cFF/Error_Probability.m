function [error_prob] = Error_Probability(N,R,P)
% Function for computing the Error Probability
% N          = Opernad Total Number of Bits              = 16
% R          = Resultant Bits of Sub-Adder               = 2
% P          = Previous/Prediction Bits of Sub-Adder     = 4
% error_prob = Probability of error for the desired adder

format long

L           = R + P;              % Sub-adder Length
k           = ((N - L)/R) + 1;    % No. of Sub Adders
m           = k - 1;              % No. of Sub Adders that can contain error
A           = 0.5;                % Propagate Probability
B           = 0.25;               % Generate Probability

error_prob  = 0;                  % Error Probability
for i = 0:R-1
    error_prob = error_prob + ( m * B * (A^(P+i)));
end

if (m == 0)
    error_prob = 0;
elseif( m == 1 )              % No Repeating Terms
    % Nothing more to be done
else
    % Terms Count = R x m
    index = 1;
    for i = 1:m
        for j = 1:R
            array_terms(index).start    = index;
            array_terms(index).end      = L + ((i-1)*R);
            array_terms(index).prop     = array_terms(index).end - array_terms(index).start;
            index                       = index + 1;
        end
    end
    
    max_index = m*R;
    remaining_prob_term = 0;
    for i = 1 : max_index
        end_index   = array_terms(i).end;
        prop_terms  = array_terms(i).prop;
        gnrt_terms  = 1;
        mult_terms  = -1;
        for j = i+1:max_index
            if(array_terms(j).start > end_index)             
                gnrt_terms_temp     = gnrt_terms + 1;
                prop_terms_temp     = prop_terms + array_terms(j).prop;
                end_index_temp      = array_terms(j).end;
                remaining_prob_term = remaining_prob_term + (mult_terms * (B^gnrt_terms_temp) * (A^prop_terms_temp));
                remaining_prob_term = Error_Probability_Internal(remaining_prob_term, array_terms, gnrt_terms_temp, prop_terms_temp, j+1, mult_terms * -1, max_index,end_index_temp);   
            end
        end
    end
    error_prob = error_prob + remaining_prob_term;
end
