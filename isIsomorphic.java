class Solution {
    public boolean isIsomorphic(String s, String t) {
                if (s.length() != t.length()) {
            return false;
        }

        // Maps to keep track of mappings from s to t and from t to s
        Map<Character, Character> sToT = new HashMap<>();
        Map<Character, Character> tToS = new HashMap<>();

        for (int i = 0; i < s.length(); i++) {
            char charS = s.charAt(i);
            char charT = t.charAt(i);

            // Check if there is a mapping for charS
            if (sToT.containsKey(charS)) {
                // If the existing mapping does not match the current character in t, return false
                if (!sToT.get(charS).equals(charT)) {
                    return false;
                }
            } else {
                // Create a new mapping from charS to charT
                sToT.put(charS, charT);
            }

            // Check if there is a mapping for charT
            if (tToS.containsKey(charT)) {
                // If the existing mapping does not match the current character in s, return false
                if (!tToS.get(charT).equals(charS)) {
                    return false;
                }
            } else {
                // Create a new mapping from charT to charS
                tToS.put(charT, charS);
            }
        }

        // If we complete the loop without conflicts, the strings are isomorphic
        return true;
    }
}
