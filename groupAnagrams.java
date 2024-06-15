class Solution {
    public List<List<String>> groupAnagrams(String[] strs) {
        Map<String, List<String>> map = new HashMap<>();
        for(String s: strs){    // miss String
            char[] c = s.toCharArray();
            Arrays.sort(c);   // not Array
            String ss = new String(c);
            if(!map.containsKey(ss)){   // not containKeys
                map.put(ss, new ArrayList<>());
            }
            map.get(ss).add(s);
        }
        return new ArrayList<>(map.values());   // not new HashMap
    }
}
