start = int(input('달력 시작 요일 : '))
days = int(input('day count: '))

print("Sun\tMon\tTue\tWed\tThu\tFri\tSat")
print("===========================")

for i in range(0, start) :
  print("", end="\t")
  
for j in range(1, days+1) :
  print("%3d" %j, end="\t")
  if((j+start)%7 == 0) :
   print()
