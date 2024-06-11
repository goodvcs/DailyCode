class Solution {
    public int[] twoSum(int[] nums, int target) {
       Map<Integer, Integer> map = new HashMap<>();
       for(int i = 0; i < nums.length; i++){
            int tem = target - nums[i];   // thinking reversely, minus each number interated
            if(map.containsKey(tem)){     
                return new int[]{map.get(tem),i};
            }
            map.put(nums[i], i);
       }
       return new int[]{};
    }
}
