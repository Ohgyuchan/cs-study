def solution(people, limit):
    people.sort()
    answer = 0; i = 0; j = len(people) - 1
    
    while i <= j :
        if people[i] + people[j] <= limit : # 2명씩 타는 게 최대
            i += 1
        j -= 1
        answer += 1

    return answer