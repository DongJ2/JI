#=
clust:
- Julia version:
- Author: jijia
- Date: 2019-08-05
=#
using CSV, DataFrames, Pkg
using LinearAlgebra
function Covariance(mat)
    Cov = Matrix{Float64}(I, 3, 3)
    dim1 = mat[:,1]
    dim2 = mat[:,2]
    dim3 = mat[:,3]
    var1 = 0
    var2 = 0
    var3 = 0
    d1 = dim1
    d2 = dim2
    d3 = dim3
    mean1 = sum(dim1)/size(dim1)[1]
    mean2 = sum(dim2)/size(dim2)[1]
    mean3 = sum(dim3)/size(dim3)[1]
    for i in 1:size(dim1)[1]
        var1 = var1 + (dim1[i] - mean1)^2
        var2 = var2 + (dim2[i] - mean2)^2
        var3 = var3 + (dim3[i] - mean3)^2
        d1[i] = mean1
        d2[i] = mean2
        d3[i] = mean3
    end
    var1 = var1 / size(dim1)[1]
    var2 = var2 / size(dim2)[1]
    var3 = var3 / size(dim3)[1]
    cov12 = sum((dim1 - d1).*(dim2 - d2)) / (num - 1)
    cov13 = sum((dim1 - d1).*(dim3 - d3)) / (num - 1)
    cov23 = sum((dim2 - d2).*(dim3 - d3)) / (num - 1)
    Cov[1,1] = var1
    Cov[1,2] = cov12
    Cov[1,3] = cov13
    Cov[2,1] = cov12
    Cov[2,2] = var2
    Cov[2,3] = cov23
    Cov[3,1] = cov13
    Cov[3,2] = cov23
    Cov[3,3] = var3
    return Cov
end

function sigma(mat, D)
    n = 0;
    sigma_ori = Covariance(mat)
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
            println(i,' ',j)
        end
    end
    return result
end
data = CSV.read("data.csv", delim=",")
mat = Matrix{Float64}(I, 40000, 3)
num = 0
for i in 1:40000
    global num
    if data[i, 1]>3
        num = num + 1
    end
end
mat = Matrix{Float64}(I, num, 3)
k = 1
for i in 1:40000
    global k
    if data[i, 1]>3
        mat[k, 1] = ceil(Int, i/200)
        mat[k, 2] = i - floor(Int, i/200)*200 + 1
        mat[k, 3] = data[i, 1]
        k = k + 1
    end
end
d = Array{Float64}(I, num, 1)
for i in 1:num
    d[i,1] = i
end
simi = Matrix{Float64}(I, num, num)
r = 1.5
sig = sigma(mat,d)
for i in 1:num
    for j in i+1:num
        global simi
        amix = 2/num
        ai = 1/num
        aj = 1/num
        Gmix = amix * log(amix) - amix * log(sig[i,j])
        Gi = ai * log(ai) - ai * log(sig[i,i])
        Gj = aj * log(aj) - aj * log(sig[j,j])
        global simi[i,j] = (Gmix - Gi - Gj)/(r^Gmix + 1)
    end
end

while true
    global simi
    class = size(simi)[1]

    maxnum = 0
    maxrow = 0
    maxcol = 0
    for i in 1:class
        for j in i:class
            if (simi[i,j] > maxnum)
                maxnum = simi[i,j]
                maxrow = i
                maxcol = j
            end
        end
    end
    if(maxnum > 0)
        for i in 1:num
            if(d[i] == maxcol)
                d[i] = maxrow
             end
        end
        k=1
        for i in 1:num
            for j in 1:num
                if(d[j] == i)
                    d[j] = k
                end
            end
            k = k + 1
            if(k == class)
                break
            end
        end
        simi = Matrix{Float64}(I, class-1, class-1)
        for i in 1:class-1
            for j in 1:class-1
                numi = 0
                numj = 0
                for k in 1:num
                    if(d[k] == i)
                        numi = numi + 1
                    elseif(d[k] == j)
                         numj = numj + 1
                    end
                end
                amix = (numi+numj)/num
                ai = numi/num
                aj = numj/num
                sig = sigma(mat,d)
                Gmix = amix * log(amix) - amix * log(sig[i,j])
                Gi = ai * log(ai) - ai * log(sig[i,i])
                Gj = aj * log(aj) - aj * log(sig[j,j])
                simi[i,j] = (Gmix - Gi - Gj)/(r^Gmix + 1)
            end
        end
    else
        break
    end
    println(class)
end
