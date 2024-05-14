class Solution {
    public int lengthOfLastWord(String s) {
        int len = 0;
        s = s.trim(); // .trim can only remove leading and tailing whitespace, but
        // not whitespace inside String
        for(int i = s.length()-1; i >= 0; i--){ // note it is .length - 1, not .length
            if(s.charAt(i) == ' ') break;
                len++;
        }
        return len;
    }
}
