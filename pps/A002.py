class Solution:
    def generate(self, numRows: int) -> List[List[int]]:
        result = [[1] * i for i in range(1, numRows + 1)]

        for i in range(2, len(result)):
            for j in range(1, len(result[i]) - 1):
                result[i][j] = result[i - 1][j - 1] + result[i - 1][j]
                
        return result