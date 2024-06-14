class Solution {
    public boolean containsNearbyDuplicate(int[] nums, int k) {
        Map<Integer, Integer> map = new HashMap<>();   // use HashMap instead of nested loop, efficiency is f(O)
        for(int i = 0; i< nums.length; i++){
            if(map.containsKey(nums[i])){
                int diff = i - map.get(nums[i]);   // map.get(key)
                if(diff <= k) return true;
                }
            map.put(nums[i],i);
        }
        return false;
    }
}
