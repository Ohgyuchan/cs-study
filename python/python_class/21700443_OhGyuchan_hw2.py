from random import *
import datetime

def is_leap_year(year):
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
    
def get_doomsday() :
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

    while True :
        character = input("Please choose your character among %s:" % names)
        
        if character in names :
            break


