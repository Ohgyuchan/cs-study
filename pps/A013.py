class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        for n in nums :
            if nums.count(n) == 1 :
                return n
        return -1

# 모범 답안
# class Solution:
#     def singleNumber(self, nums: List[int]) -> int:
#         result = 0
#         for num in nums:
#             result = result ^ num
#         return result