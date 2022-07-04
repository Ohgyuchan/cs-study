def solution(s):
    answer = len(s)

    for step in range(1, len(s) // 2 + 1):
        result = ""
        unit = s[0:step]  # s에서 앞글자부터 step만큼의 문자열 추출
        count = 1
    
        for j in range(step, len(s), step):
        
            if unit == s[j:j + step]:
                count += 1
            
            else:
                result += str(count) + unit if count >= 2 else unit
                unit = s[j:j + step]
                count = 1
            
        result += str(count) + unit if count >= 2 else unit # count >= 2 이면 count+alphabet 아니면 alphabet
    
        answer = min(answer, len(result)) # 최솟값을 answer에 저장

    return answer