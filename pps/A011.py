def solution(N, stages):
    playerNum = len(stages)
    failure = {}
    
    for i in range(1, N+1) :
        if playerNum != 0 :
            failure[i] = stages.count(i) / playerNum
            playerNum -= stages.count(i)
        else :
            failure[i] = 0
    
    return sorted(failure, key=lambda i : failure[i], reverse = True)