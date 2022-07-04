def solution(skill, skill_trees):
    answer = 0
    for skill_tree in skill_trees:
        sk = ""     
        for st in skill_tree:       
            if st in skill:         
                sk += st
        
        if skill.find(sk) == 0 :
            answer += 1
    
    return answer