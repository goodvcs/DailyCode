class Solution {
    public List<List<Integer>> threeSum(int[] nums) {
        Set<List<Integer>> set = new HashSet<>();
        List<List<Integer>> output = new ArrayList<>();
        Arrays.sort(nums);  // important!!! must sort before using pointers
        for(int i = 0; i < nums.length; i++){
            int j = i + 1, k = nums.length - 1;
            while(j < k){
                if(nums[i] + nums[j] + nums[k] == 0){
                    set.add(Arrays.asList(nums[i], nums[j], nums[k]));  // how add array to list?
                    j++;  // don't forget 
                    k--;  // don't forget
                }else if(nums[i] + nums[j] + nums[k] < 0){
                    j++;
                }else if(nums[i] + nums[j] + nums[k] > 0){
                    k--;
                }
            }
        }
        output.addAll(set);
        return output;
    }
}
