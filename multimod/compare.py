with open('record_true.txt', 'r') as fp1:
    lst1 = fp1.readlines()

with open('record_doubt.txt', 'r') as fp2:
    lst2 = fp2.readlines()

len_lst1 = len(lst1)
len_lst2 = len(lst2)

count = 0
for i in range(len_lst1):
    if (lst1[i] != lst2[i]):
        count = count + 1
#        print("Error occur!!!INDEX:{}--TRUE VALUE:{}--FALSE VALUE:{}".format(i, lst1[i], lst2[i]))

rate = float(count) / float(len_lst1)
print("Wrong Rate:{}".format(rate))
