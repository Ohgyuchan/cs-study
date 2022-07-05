class Solution:
    def summaryRange(start, end) :
        if start == end :
            return str(start)
        return str(start) + "->" + str(end)
    
    def summaryRanges(self, nums: List[int]) -> List[str]:
        if not nums:
            return []
        
        start = nums[0]
        answer = []
        
        for i in range(1, len(nums)) :
            if nums[i] - nums[i-1] != 1 :
                answer.append(Solution.summaryRange(start, nums[i-1]))
                start = nums[i]
                
        answer.append(Solution.summaryRange(start, nums[-1]))
        
        return answer
            
            