def solution(x):
    total = 0
    for ch in str(x) :
        total += int(ch)
    
    return x % sum([int(ch) for ch in str(x)]) == 0