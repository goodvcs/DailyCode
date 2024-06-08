class Solution {
    public boolean wordPattern(String pattern, String s) {
        String[] ss = s.split(" ");  // use " " not "" to split String.
        Map<Character, String> map = new HashMap<>();
        Map<String, Character> map2 = new HashMap<>();  // must check reverse: "abba" "dog dog dog dog"
        if(pattern.length() != ss.length) return false;
        for(int i = 0; i < pattern.length(); i++){
            char c = pattern.charAt(i);
            String word = ss[i];
            if(map.containsKey(c)){
                if(!map.get(c).equals(word)){  // must use .equals to compare two Strings
                    return false;
                }
            }else{
                map.put(c, word);
            }
            if(map2.containsKey(word)){
                if(!map2.get(word).equals(c)){  // must use .equals to compare two Strings
                    return false;
                }
            }else{
                map2.put(word, c);
            }

        }
        return true;
    }
}
