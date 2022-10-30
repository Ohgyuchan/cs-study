from random import *
import datetime

def is_leap_year(year): # year가 윤년인지 판별하는 함수
    if year % 400 == 0:
        return True

    if year % 100 == 0:
        return False

    if year % 4 == 0:
        return True

    return False

def get_date() :
    start = datetime.date(2010, 10, 1)
    today = datetime.datetime.today()
    end = datetime.date(today.year, today.month, today.day)
    random_date = start + (end - start) * random()
    return random_date

def get_random_date() :
    start = '2020-10-1'
    
def get_doomsday(date: datetime.date) :
    dateDict = {0: '월요일', 1:'화요일', 2:'수요일', 3:'목요일', 4:'금요일', 5:'토요일', 6:'일요일'}
    dateDict[date.weekday()]
    return 0


names = []
birthDays = []
while True :
    while True :
        inputs = input("Enter names seperated by comma: ").split(",")
        for i in inputs :
            i = i.strip()
            if i != "" and not i in names :
                names.append(i)
        print("Valid names received are ", names)
        
        if len(names) > 2 :
            break
        else :
            print("The number of valid names is less than 3.")

    print("*" * 30)
    for i in range(len(names)) :
        birthDays.append(get_date())
        print(names[i], '\t', birthDays[i])
    print("*" * 30)

    index = -1
    while True :
        character = input("Please choose your character among %s:" % names)
        
        if character in names :
            index = names.index(character)
            break
    
    print("You have chosen %s born in %s (%s)" % (names[index], birthDays[index], get_doomsday(birthDays[index])))
    

