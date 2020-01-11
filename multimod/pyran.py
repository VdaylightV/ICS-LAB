import random

with open("test3.txt", "w") as file:
    for i in range(20):
#        a = random.randint(0, 9223372036854775807)
#        b = random.randint(0, 9223372036854775807)
#        m = random.randint(0, 9223372036854775807)
        a = random.randint(0, 9007199254740992)
        b = random.randint(0, 9007199254740992)
        m = random.randint(0, 9007199254740992)
        res = a*b%m
        multi = (a%m)*(b%m)
        #print("{:d} {:x} {:x} {:x}".format(res,a,b,m))
        #print("{:d} || {:d}".format(multi, res))
#        print("0")
        print("{:d}".format(res))
        s = "./multimod-64 -i 3" + ' ' + str(a) + ' '  + str(b) + ' ' + str(m) + ' ' + str(res) + '\n'
        file.write(s)

