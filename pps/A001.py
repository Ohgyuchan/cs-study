class Solution:
    def findContentChildren(self, g: List[int], s: List[int]) -> int:
        g.sort()
        s.sort()

        i = 0
        result = 0

        for j in range(len(s)):
            if i > len(g) - 1:
                return result
            if s[j] >= g[i]:
                result += 1
                i += 1
            j += 1
        
        return result