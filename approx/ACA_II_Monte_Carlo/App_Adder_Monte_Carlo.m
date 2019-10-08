clear
S = [8,4];
R = [6];
range = 0;
for i = 1:length(S)
    range = range + S(i);
end

mu1 =2048;
sigma1 = 500;
mu2 = 2048;
sigma2 = 500;
accurate_probability = [];
accurate_error_distance = [];
accurate_error_item = 0;

for i = 0:power(2,range)-1
    for j = 0:power(2,range)-1
        accurate = i + j;
        approximate = App_Adder(i,j,S,R);
        if (accurate ~= approximate)
            diff = accurate - approximate;
            if (ismember(diff,accurate_error_distance) == 1)
                accurate_probability(find(accurate_error_distance == diff)) = accurate_probability(find(accurate_error_distance == diff)) + f(i,mu1,sigma1)*f(j,mu2,sigma2);
            else
                accurate_error_item = accurate_error_item + 1;
                accurate_error_distance(accurate_error_item) = diff;
                accurate_probability(accurate_error_item) = 0;
                accurate_probability(find(accurate_error_distance == diff)) = accurate_probability(find(accurate_error_distance == diff)) + f(i,mu1,sigma1)*f(j,mu2,sigma2);
            end
        end
    end
end

error_prob = 0;
MSE = 0;
Mean_Error_Distance = 0;

for i = 1:accurate_error_item
    error_prob = error_prob + accurate_probability(i);
    Mean_Error_Distance = Mean_Error_Distance + accurate_probability(i) * accurate_error_distance(i);
    MSE = MSE + accurate_probability(i) * accurate_error_distance(i)* accurate_error_distance(i);
end

error_prob
Mean_Error_Distance
MSE

MonteCarlo_Num = 1000000;
app_error_prob = zeros(1,100);
app_MSE = zeros(1,100);
app_Mean_Error_Distance = zeros(1,100);

for j = 1 : 100
    approximate_probability = zeros(1,accurate_error_item);
    randomN_number1 = floor(normrnd(mu1,sigma1,MonteCarlo_Num,1));
    randomN_number2 = floor(normrnd(mu2,sigma2,MonteCarlo_Num,1));
    real_num = MonteCarlo_Num;

    for i = 1 : MonteCarlo_Num
        if (randomN_number1(i) >= 0 && randomN_number1(i) < power(2,range) && randomN_number2(i) >= 0 && randomN_number2(i) < power(2,range) )
            acc = randomN_number1(i) + randomN_number2(i);
            app = App_Adder(randomN_number1(i), randomN_number2(i), S,R);
            diff = acc - app;
            if (diff ~= 0)
                approximate_probability(find(accurate_error_distance == diff)) = approximate_probability(find(accurate_error_distance == diff)) + 1;
            end
        else
            real_num = real_num - 1;
        end
    end

    approximate_probability = approximate_probability /real_num;
    for i = 1 : accurate_error_item
        app_error_prob(j)  = app_error_prob(j) + approximate_probability(i);
        app_Mean_Error_Distance(j) = app_Mean_Error_Distance(j) + approximate_probability(i) * accurate_error_distance(i);
        app_MSE(j) = app_MSE(j) + approximate_probability(i) * accurate_error_distance(i)*accurate_error_distance(i);
    end
end

app_error_prob = mean(app_error_prob)
app_Mean_Error_Distance = mean(app_Mean_Error_Distance)
app_MSE = mean(app_MSE)

error_prob_rate = abs(app_error_prob-error_prob)/error_prob
MED_rate = abs(app_Mean_Error_Distance - Mean_Error_Distance)/Mean_Error_Distance
MSE_rate = abs(app_MSE - MSE)/MSE

H_distance = 0;
accurate_probability(length(accurate_probability)+1) = 1 - error_prob;
approximate_probability(length(approximate_probability) + 1) = 1 - app_error_prob;

for i = 1 : length(accurate_probability)
    H_distance = H_distance + power(sqrt(accurate_probability(i)) - sqrt(approximate_probability(i)),2);
end
H_distance = sqrt(H_distance)/sqrt(2);

H_distance



                
            
