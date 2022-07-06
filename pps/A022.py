n = int(input())
arr = list(map(int, input().split()))

y = 0
m = 0

for i in arr:
    y += i // 30 * 10 + 10 # 29초 밑으로는 i // 30 == 0.xxxx
    m += i // 60 * 15 + 15 # 59초 밑으로는 i// 60 == 0.xxxx

if y < m:
    print('Y %d' % y)
elif y > m:
    print('M %d' % m)
else:
    print('Y M %d' % y)