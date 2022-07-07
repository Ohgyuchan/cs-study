t = int(input())

for i in range(t) :
    k = int(input())
    n = int(input())
    count = [x for x in range(1, n+1)] # 0층 1~n호 : 1~n명
    for j in range(k) :
        for l in range(1, n) :
            count[l] += count[l-1]
    print(count[-1])