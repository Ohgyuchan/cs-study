class Solution:
    def addDigits(self, num: int) -> int:
        answer = num
        while True :
            num = answer
            answer = 0
            if num >= 10 :
                for n in str(num) :
                    answer += int(n)
            else :
                return num