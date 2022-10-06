# num = int(input())
num = 10
# triangle1
for i in range(1, num) :
    for j in range(i) :
        print("*", end="")
    print()

# triangle2
print()
for i in range(num-1, 0, -1) :
    for j in range(i) :
        print("*",end="")
    print()

# triangle3
print()
for i in range(num-1, 0, -1) :
    for j in range(i-1) :
        print(" ",end="")
    for j in range(num - i) :
        print("*", end="")
    print()

# diamond
print()
for i in range(1,num) :
    for j in range((num)-i) :
        print(" ", end="")
    for j in range(1, i * 2) :
        print("*", end="")
    print()

for i in range(num, 0, -1) :
    for j in range((num)-i, 0, -1) :
        print(" ", end="")
    for j in range(i * 2, 1, -1) :
        print("*", end="")
    print()