a = int(input())
b = int(input())
c = int(input())

nums = [0] * 10
n = a * b * c

for i in str(n) :
    index = int(i)
    nums[index] += 1

for i in nums :
        print(i)