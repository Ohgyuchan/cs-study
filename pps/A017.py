room = input()

answer = [0] * 9 # 0~8까지만 쓸 거

for i in range(len(room)) :
    num = int(room[i])
    if num == 6 or num == 9 :
        answer[6] += 1
    else :
        answer[num] += 1

if(answer[6] % 2 == 0) : # 짝수면
    answer[6] //= 2
else : # 홀수면
    answer[6] = answer[6] // 2 + 1
    
print(max(answer))

# Using Dictionary type
# room = input()
# answer = {'0':0, '1':0, '2':0, '3':0, '4':0, '5':0, '6':0, '7':0, '8':0}
# for i in range(len(room)):
#     if room[i] in ['6', '9']:
#         answer['6'] += 1
#     else:
#         answer[room[i]] += 1
# if answer['6'] % 2 == 0:
#     answer['6'] = answer['6'] // 2
# else:
#     answer['6'] = answer['6'] // 2 + 1
# print(max(answer.values()))