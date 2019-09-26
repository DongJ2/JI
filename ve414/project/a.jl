using CSV, DataFrames, Pkg
using LinearAlgebra

function Covariance(mat)
    Cov = Matrix{Float64}(I, 3, 3)
    Cov[1,1]=0
    Cov[2,2]=0
    Cov[3,3]=0
    xmean = []
    mean1 = 0
    mean2 = 0
    mean3 = 0
    for i in 1:size(mat[:,1])[1]
        mean1 = mean1 + mat[i,1]
        mean2 = mean2 + mat[i,2]
        mean3 = mean3 + mat[i,3]
    end
    push!(xmean, mean1 / size(mat[:,1])[1])
    push!(xmean, mean2 / size(mat[:,1])[1])
    push!(xmean, mean3 / size(mat[:,1])[1])
    for i in 1:size(mat[:,1])[1]
        Cov = Cov + (mat[i,:] - xmean)*(mat[i,:]-xmean)'
    end
    Cov = Cov / size(mat[:,1])[1]
    return Cov
end

function sigma(mat, D)
    n = 0;
    sigma_ori = [0.0258824 -0.021797 -0.00703624; -0.021797 0.050163 -0.00736522; -0.00703624 -0.00736522 1.36012]
    for i in 1:size(D)[1]
        if i == D[i]
            n = n + 1
        end
    end
    k = 1
    t = 1
    C = []
    result = Matrix{Float64}(I, n, n)
    while k <= n
        find = 0
        sigma_temp = sigma_ori
        temp_list = []
        for i in 1:size(D)[1]
            if D[i] == t
                push!(temp_list, i)
                find = 1
            end
        end
        if find == 1
            push!(C, temp_list)
            x_mean = []
            mean1 = 0
            mean2 = 0
            mean3 = 0
            for i in 1:size(C[k])[1]
                mean1 = mean1 + mat[C[k][i],1]
                mean2 = mean2 + mat[C[k][i],2]
                mean3 = mean3 + mat[C[k][i],3]
            end
            mean1 = mean1 / size(C[k])[1]
            mean2 = mean2 / size(C[k])[1]
            mean3 = mean3 / size(C[k])[1]
            push!(x_mean, mean1)
            push!(x_mean, mean2)
            push!(x_mean, mean3)
            for i in 1:size(C[k])[1]
                sigma_temp = sigma_temp + (mat[C[k][i],:] - x_mean)*(mat[C[k][i],:] - x_mean)'
            end
            sigma_temp = sigma_temp / (size(C[k])[1] + 1)
            result[k,k] = det(sigma_temp)
            k = k + 1
        end
        t = t + 1
    end
    for i in 1:size(C)[1]
        for j in i+1:size(C)[1]
            mean1 = 0
            mean2 = 0
            mean3 = 0
            x_mean = []
            for p in 1:size(C[i])[1]
                mean1 = mean1 + mat[C[i][p],1]
                mean2 = mean2 + mat[C[i][p],2]
                mean3 = mean3 + mat[C[i][p],3]
            end
            for p in 1:size(C[j])[1]
                mean1 = mean1 + mat[C[j][p],1]
                mean2 = mean2 + mat[C[j][p],2]
                mean3 = mean3 + mat[C[j][p],3]
            end
            mean1 = mean1 / (size(C[i])[1] + size(C[j])[1])
            mean2 = mean1 / (size(C[i])[1] + size(C[j])[1])
            mean3 = mean1 / (size(C[i])[1] + size(C[j])[1])
            push!(x_mean, mean1)
            push!(x_mean, mean2)
            push!(x_mean, mean3)
            sigma_temp = sigma_ori
            for p in 1:size(C[i])[1]
                sigma_temp = sigma_temp + (mat[C[i][p],:] - x_mean)*(mat[C[i][p],:] - x_mean)'
            end
            for p in 1:size(C[j])[1]
                sigma_temp = sigma_temp + (mat[C[j][p],:] - x_mean)*(mat[C[j][p],:] - x_mean)'
            end
            sigma_temp = sigma_temp / (size(C[i])[1] + 1 + size(C[j])[1])
            result[i,j] = det(sigma_temp)
        end
    end
    return result
end

data = CSV.read("data.csv", delim=",")
mat = Matrix{Float64}(I, 40000, 3)
num = 0
for i in 1:40000
    global num
    if data[i, 1]>2
        num = num + 1
    end
end
mat = Matrix{Float64}(I, num, 3)
k = 1
for i in 1:40000
    global k
    if data[i, 1]>2
        mat[k, 1] = ceil(Int, i/200)*107/200
        mat[k, 2] = (i - floor(Int, i/200)*200 + 1)*107/200
        mat[k, 3] = data[i, 1]
        k = k + 1
    end
end
D=1:num
