n = int(input())
a = list(map(int, input().split()))
b = list(map(int, input().split()))

answer = 0
for i in range(n):
    answer += min(a) * max(b)
    a.pop(a.index(min(a)))
    b.pop(b.index(max(b)))


print(answer)