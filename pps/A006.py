def solution(s):
    answer = True
    if s.lower().find('p') == -1 and s.lower().find('y') == -1 :
        return True
    p = 0
    y = 0
    
    for ch in s.lower() :
        if 'y' == ch :
            y += 1
        if 'p' == ch :
            p += 1 
    if p == y :
        return True
    else :
        return False