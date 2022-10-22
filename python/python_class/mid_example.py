print("*** 병원 온라인 예약 시스템")

dates = []
names = []
symptoms = []

while True :
    
    while True :
        date = input("예약 날짜 :")
        if date.isdecimal() and len(date) == 4 :
            if not date in dates :
                dates.append(date)
                print("정상적으로 예약 되었습니다.")
                break
            else :
                print("해당 날짜는 이미 예약 되었습니다.")
        else :
            print("잘못 입력하셨습니다.")
        
    while True :
        name = input("환자 이름: ")
        if len(name) >= 2:
            names.append(name)
            break
        else :
            print("이름은 2글자 이상이어야 합니다.")
    
    symptoms.append(input("증상: "))
    
    check = input("추가 예약(y)")
    
    if check == 'y' :
        continue
    else :
        break

print("-"*20+"예약 목록"+"-"*20)
for i in range(len(dates)) :
    print("예약번호", i+1)
    print("예약 날짜: ", dates[i])
    print("환자 이름: ", names[i])
    print("증상", symptoms[i])
    print("="*40)