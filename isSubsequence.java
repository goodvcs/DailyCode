class Solution {
    public boolean isSubsequence(String s, String t) {
        // if(s.equals(t) || s.equals("")) return true;    redundent, we will check below
        int i = 0, j = 0;
        while(i < s.length() && j < t.length()){  
            // i < s.length() is try to exclude s == "", i == s.length() == 0 will return true
            // if (i == s.length() -1) return true; must put back, as s.length() might == 0
            if(t.charAt(j) != s.charAt(i)){
                j++;
            }else{
                i++;
                j++;
            }
        }
        return i == s.length(); 
        // i is not index in s, but the number of qualified char. so i == s.length()-1 is wrong
    }
}
