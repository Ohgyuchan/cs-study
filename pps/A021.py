import sys
input = sys.stdin.readline

n = int(input())
answer = 0
for i in range(n) :
    answer += int(input()) - 1
    
print(answer + 1)