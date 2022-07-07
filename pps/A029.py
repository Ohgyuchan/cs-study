n = int(input())
first = int(input())

if (n > 5) :
    print('Love is open door')
else :
    for i in range(n-1) :
        first = not first
        print(int(first))