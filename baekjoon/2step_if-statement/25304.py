price = int(input())

n = int(input())

total_price = 0

for i in range(n):
    temp_price, count = map(int, input().split())
    total_price += temp_price * count
    
if(total_price == price) :
    print("Yes")
else :
    print("No")