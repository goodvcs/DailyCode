class Solution {
    public void rotate(int[] nums, int k) {
        int n = nums.length;
        k %= n;

        //reverse(nums, 0, n-k-1);  not easy to understand
        //reverse(nums, n-k, n-1);
        //reverse(nums, 0, n-1);

        reverse(nums, 0, n - 1);  // reverse the whole
        reverse(nums, 0, k - 1);  // first k numbers
        reverse(nums, k, n - 1);  // rest numbers
        
    }
    private void reverse(int[] nums, int start, int end){
        for(int i = start, j = end; i < j; i++,j--){
            int tem = nums[i];
            nums[i] = nums[j];
            nums[j] = tem;
        }
    }
}
