def s(a, b, n) :
    result = 0
    for i in range(n) :
        result += a[i] * b[i]
    return result

n = int(input())

a = list(map(int, input().split()))
b = list(map(int, input().split()))
a.sort() ; b.sort(reverse=True)

print(s(a, b, n))