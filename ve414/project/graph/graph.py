import pandas as pd
import numpy as np
import matplotlib as mpl
nums = [2, 7, 11, 15]
target = 9
result = []
for i in range(0,len(nums)-1):
    for j in range(i+1,len(nums)):
        if (nums[i] + nums[j] == target):
            result.append([i, j])
        print(i,j)
print(result)
##mpl.use('TkAgg')
##import matplotlib.pyplot as plt
##from matplotlib.patches import Ellipse, Circle
#data = pd.read_csv("215.csv")
#data = data.sort_values('Close', ascending=True)
##import csv
##data=[]
##for i in range(200):
##    data.append([])
##num = 199;
##k = 0;
##with open('sklearn(1).csv')as f:
##    f_csv = csv.reader(f)
##    for row in f_csv:
##        temp = float(row[0])
##        data[num].append(temp);
##        k += 1;
##        if k == 200:
##            num -= 1;
##            k = 0;
##fig = plt.figure();
##for i in range(200):
##    for j in range(200):
##        if data[i][j] > 0:
##            x = np.arange(i * 107 / 200, (i + 1) * 107 / 200, 0.001);
##            y1 = x - x + (j + 1) * 107 / 200;
##            y2 = x - x + j * 107 / 200 ;
##            plt.plot(x, y1, alpha = 0);
##            plt.plot(x, y2, alpha = 0); 
##            plt.fill_between(x, y1, y2, where=(i * 107 / 200 < x)&(x < (i + 1) * 107 / 200), facecolor = 'red', interpolate=True, alpha = data[i][j] / 4);
##            print(i,j);
##plt.xticks(np.arange(0, 111, 10));
##plt.yticks(np.arange(0, 111, 10));
#for i in range(150):
#    for j in range(150):
#        plt.scatter(i, j, c='#DC143C', marker = 's', alpha = data[i][j] / max);
#        print(i,j)
##plt.show()
#row = data.shape[0]
#column = data.shape[1]
#color = [ 'whitesmoke', 'gainsboro', 'lightgrey', 'lightgray', 'silver', 'darkgray', 'darkgrey', 'gray', 'grey', 'dimgrey', 'dimgray', 'k', 'black', 'yellow', 'green', 'blue', 'red']
#plt.figure(figsize=(8,4))data.loc[i,'Close']
#fig = plt.figure()
#for i in range(0,21604):
#        plt.scatter(data.loc[i, 'X'], data.loc[i, 'Y'], c='grey')
#l=[]
#for i in range(0,17): 
#        l.append([])
#for i in range(0,21604):
#        l[data.loc[i, 'Close']].append([data.loc[i, 'X'], data.loc[i, 'Y']])
#for i in range(1,17):
#        for j in range(len(l[i])):
#                if (l[i][j][0] > 35) & (l[i][j][0] < 65):
#                        plt.scatter(l[i][j][0], l[i][j][1], c='#DC143C', alpha = i / 80)
#plt.show()

#for x in data.loc:
    #r = 1.0
    #a, b = data.loc[i,'X'], data.loc[i,'Y']
    #theta = np.arange(0, 2 * np.pi, 0.01)
    #x = a + r * np.cos(theta)
    #y = b + r * np.sin(theta)
    #if data.loc[i, 'Close'] > 0 :
    #    plt.scatter(a,b, c=color[data.loc[i, 'Close']], marker='o')

#plt.show()