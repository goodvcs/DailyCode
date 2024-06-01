class Solution {
    public int minSubArrayLen(int target, int[] nums) {
        // sliding windows means move both window's left and right edges
         int left = 0;
         int sum = 0;
         int result = Integer.MAX_VALUE;  // set result as the largest Integer
         for(int i = 0; i < nums.length; i++){
            sum += nums[i];  // move rigth edge to right
            while(sum >= target){     // while not if, to move left edge to the right most
                result = Math.min(result, i - left + 1);  // determine width of window
                sum -= nums[left++];  // move left edge to right
            }
         }
         return (result == Integer.MAX_VALUE)? 0:result;
    }
}
