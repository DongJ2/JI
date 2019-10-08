function [remaining_prob_term] = Error_Probability_Internal(remaining_prob_term, array_terms, gnrt_terms, prop_terms, index, mult_terms, max_index, end_index)

A           = 0.5;                % Propagate Probability
B           = 0.25;               % Generate Probability

for j = index:max_index
    if(array_terms(j).start > end_index)
        gnrt_terms_temp     = gnrt_terms + 1;
        prop_terms_temp     = prop_terms + array_terms(j).prop;
        end_index_temp      = array_terms(j).end;
        remaining_prob_term = remaining_prob_term + (mult_terms * (B^gnrt_terms_temp) * (A^prop_terms_temp));
        remaining_prob_term = Error_Probability_Internal(remaining_prob_term, array_terms, gnrt_terms_temp, prop_terms_temp, j+1, mult_terms * -1, max_index, end_index_temp);
    end
end
