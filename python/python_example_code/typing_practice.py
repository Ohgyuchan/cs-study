from random import *
import time
 
f = open("all.txt", "rt")
 
l1 = f.readlines()
l2 = []
for i in l1:
    l2.append(i[:-1])
 
shuffle(l2)
start = time.time()
x = input(l2[0]+"\n")
if( x == l2[0]):
    print("correct!")
else:
    print("wrong!")
end = time.time()
dur = end-start
res = (len(l2[0])/dur) * 60
print("Time : %.2f, Result : %.2f" %(dur, res) )