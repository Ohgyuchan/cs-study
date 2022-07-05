class Solution:
    def countPrimes(self, n: int) -> int:
        count = 0
        if n <= 2 :
            return 0
        
        for i in range(2, n) :
            primeCheck = True
            for j in range(2, i + 1) :
                if i != j and i % j == 0 :
                    primeCheck = False
                    break
            
            if primeCheck :
                count += 1
        
        return count