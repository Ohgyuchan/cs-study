passengers = 0
answer = 0
for i in range(0,4) :
    inOut = list(map(int, input().split()))
    passengers -= inOut[0]
    passengers += inOut[1]
    answer = passengers if passengers >= answer else answer

print(answer)