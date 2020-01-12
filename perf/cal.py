with open('3.txt', 'r') as fp1:
    lst1 = fp1.readlines()

len_lst1 = len(lst1)

res = 0
for i in range(len_lst1):
    res = res + eval(lst1[i][:8]) 

res = res / len_lst1
print(res)
