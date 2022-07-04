class Solution:
    def plusOne(self, digits: List[int]) -> List[int]:
        bigNum = 0
        length = len(digits)
        for i in digits :
            length -= 1
            bigNum += i * (10 ** length)
        bigNum += 1
        
        result = []
        while True :
            if bigNum == 0 :
                break
            result.append(bigNum % 10)
            bigNum //= 10
        
        return reversed(result)