class Solution {
    public boolean canConstruct(String ransomNote, String magazine) {
        int[] c = new int[26];
        for(char i : magazine.toCharArray()){
            c[i - 'a']++;    // learn to count each letter's frenquency
        }
        for(char i : ransomNote.toCharArray()){
            if(c[i - 'a'] == 0){   
              return false;
            }
            c[i - 'a']--;
        }
        return true;   // minus each letter
    }
}
    
