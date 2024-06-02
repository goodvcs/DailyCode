class Solution {
    public int lengthOfLongestSubstring(String s) {
        int result = 0;
        int left = 0;
        Set<Character> set = new HashSet<>();  // use set to store single substring
        for(int right = 0; right < s.length(); right++){
            if(!set.contains(s.charAt(right))){  // add char to set if it is not in set
                set.add(s.charAt(right));
                result = Math.max(result, right - left + 1);   // get max but not min
            }else{
                while(set.contains(s.charAt(right))){   
                    set.remove(s.charAt(left++));   // remove elements from left in set if char in set, repeat until no repeated charAt(right)
                }
                set.add(s.charAt(right));  // add new char to set
            }
        } 
        return result;
    }
}
