public class Solution {
    public List findDisappearedNumbers(int[] nums) {
        List result = new ArrayList();
        int length = nums.length;
        int val = 0;
        
        // nums[i]에 value-1에 해당하는 index를 바라본다.
        // 만약 해당 index에 해당하는 값을 방문하면 음수, 방문하지 않았으면
        // 양수로 만들어 이 문제를 해결한다.
        // nums[nums[i] - 1] = - nums[nums[i] - 1]
        for(int i = 0; i < length; i++){
            // 해당 i번째 index의 값이 [1...n] 중에서 이미 나왔던 값인 경우 음수로 처리했기 때문에
            // 절대값으로 처리한다.
            val = Math.abs(nums[i]) - 1;
            if(nums[val] > 0){ // [1...n] 중에서 이미 나왔던 값인 경우는 제외
                nums[val] = -nums[val];
            }
        }
        
        for(int i = 0; i < length; i++){
            if(nums[i] > 0){
                esult.add(i+1);
            }
        }
        
        return result;
    }
}
