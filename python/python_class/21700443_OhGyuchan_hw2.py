from random import *
from datetime import *

def is_leap_year(year): # year가 윤년인지 판별하는 함수
    if year % 400 == 0:
        return True

    if year % 100 == 0:
        return False

    if year % 4 == 0:
        return True

    return False

def get_date() : # 랜덤 날짜 생성 함수
    start = date(2010, 10, 1) # 2010.10.1을 시작일로 변수에 저장
    today = datetime.today() # 오늘 날짜를 변수에 저장
    end = date(today.year, today.month, today.day) # 오늘 날짜의 시간을 제외한 년월일만 end 변수에 저장
    random_date = start + (end - start) * random() # end 날짜에서 start 날짜 사이의 랜덤 날짜 생성
    return random_date # 생성된 랜덤 날짜 return

# def get_random_date() :
#     start = '2020-10-1'
    
def get_doomsday(date: date) :
    date_dict = {0: 'Mon.', 1:'Tue.', 2:'Wed.', 3:'Thu.', 4:'Fri.', 5:'Sat.', 6:'Sun.'} # 요일을 dictionary 에 저장
    return date_dict[date.weekday()] # date의 요일을 return (weekday()는 요일에 따라 월~일을 0~6으로 return 해주는 datetime 모듈의 내장 함수)


names = []
birth_days = []
opt = False
while True :
    while not opt : # opt 가 False 면 실행
        inputs = input("Enter names seperated by comma: ").split(",") # ','를 기준으로 split
        for i in inputs :
            i = i.strip() # 좌우 공백 제거
            if i != "" and not i in names : # 공백이 아니면 names에 append
                names.append(i) 
        
        print("Valid names received are ", names)
        
        if len(names) > 2 : # names에 저장된 이름의 갯수가 2보다 크면 break
            break
        else : # names에 저장된 이름의 갯수가 2보다 작거나 같으면 에러 메시지 출력
            print("The number of valid names is less than 3.")

    if not opt : # opt가 False면 실행
        print("*" * 30)
        for i in range(len(names)) :
            birth_days.append(get_date()) # 랜덤 날짜를 생일로 저장
            print(names[i], '\t', birth_days[i]) # 데이터 출력
        print("*" * 30)

    u_index = -1 # user가 고르는 이름의 index 저장 변수
    c_index = -1 # computer가 고르는 이름의 index 저장 변수
    while True :
        character = input("Please choose your character among %s:" % names) # 이름 입력 받기
        
        if character in names : # 유효한 이름이면
            u_index = names.index(character) # u_index에 해당 이름의 index 저장
            break
    
    c_index = randrange(0, len(names)) # c_index에 0 ~ (names의 길이 -1) 값 사이에 있는 값 랜덤으로 저장
    print("You have chosen %s born in %s (%s)" % (names[u_index], birth_days[u_index], get_doomsday(birth_days[u_index]))) # u_index에 해당하는 데이터 출력
    print("The computer has chosen %s born in %s (%s)" % (names[c_index], birth_days[c_index], get_doomsday(birth_days[c_index]))) # c_index에 해당하는 데이터 출력
    
    result_str = "" # 결과 출력에 해당하는 문자열 변수
    if c_index == u_index : # u_index 와 c_index 가 같으면 같다고 출력
        print("They are same person.")
    else : # u_index와 c_index가 다른 값이면 실행
        if birth_days[u_index] < birth_days[c_index] : # u_index의 해당하는 생일 날짜가 더 옛날이면 u_index가 order
            result_str = "order than" # result_str에 order than 저장
        elif birth_days[u_index] > birth_days[c_index] : # u_index의 해당하는 생일 날짜가 더 최근이면 u_index가 younger
            result_str = "younger than" # result_str에 younger than 저장
        else :
            result_str = "the same age as" # 같은 날짜면 the same age as 저장
        
        print("%s is %s %s." % (names[u_index], result_str, names[c_index])) # 결과 출력
    
    if "y" == input("Do you want to play again? (y):") : # 입력 값이 'y'면 opt 값을 True로 변경
        opt = True
    else : # 입력 값이 'y'가 아니면 break
        break

