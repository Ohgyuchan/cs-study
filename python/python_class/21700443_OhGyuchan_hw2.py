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

def get_date() :
    start = date(2010, 10, 1)
    today = datetime.today()
    end = date(today.year, today.month, today.day)
    random_date = start + (end - start) * random()
    return random_date

def get_random_date() :
    start = '2020-10-1'
    
def get_doomsday(date: date) :
    date_dict = {0: 'Mon.', 1:'Tue.', 2:'Wed.', 3:'Thu.', 4:'Fri.', 5:'Sat.', 6:'Sun.'}
    return date_dict[date.weekday()]


names = []
birth_days = []
opt = False
while True :
    while not opt :
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

    if not opt :
        print("*" * 30)
        for i in range(len(names)) :
            birth_days.append(get_date())
            print(names[i], '\t', birth_days[i])
        print("*" * 30)

    u_index = -1
    c_index = -1
    while True :
        character = input("Please choose your character among %s:" % names)
        
        if character in names :
            u_index = names.index(character)
            break
    
    c_index = randrange(0, len(names))
    print("You have chosen %s born in %s (%s)" % (names[u_index], birth_days[u_index], get_doomsday(birth_days[u_index])))
    print("The computer has chosen %s born in %s (%s)" % (names[c_index], birth_days[c_index], get_doomsday(birth_days[c_index])))
    
    result_str = ""
    if c_index == u_index :
        print("They are same person.")
    else :
        if birth_days[u_index] < birth_days[c_index] :
            result_str = "order than"
        elif birth_days[u_index] > birth_days[c_index] :
            result_str = "younger than"
        else :
            result_str = "the same age as"
        
        print("%s is %s %s." % (names[u_index], result_str, names[c_index]))
    
    if "y" == input("Do you want to play again? (y):") :
        opt = True
    else :
        break

