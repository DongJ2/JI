import csv
cFF=[[]]*16
eFF=[[]]*16
for i in range(1,257):
    r1=csv.reader(open('8_cFF'+str(i)+'.csv',encoding='utf-8'))
    r2=csv.reader(open('8_eFF'+str(i)+'.csv',encoding='utf-8'))
    for x in r1:
        for j in range(len(x)):
            print(j)
            y=x[1]
            num=complex(y)
            cFF[(i-1)//16].append(num.real)
    for x in r2:
        for j in range(len(x)):
            y=x[j]
            num=complex(y)
            eFF[(i-1)//16].append(num.real)
print(cFF)
