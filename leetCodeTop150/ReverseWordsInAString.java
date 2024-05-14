class Solution {
    public String reverseWords(String s) {
        String[] arr = s.split(" ");
        StringBuilder result = new StringBuilder();
        for(int i = arr.length - 1; i >= 0; i--){
            if(arr[i].isEmpty()) continue;  // Sting.isEmpty() to judge whitespace
            result.append(arr[i].trim());
            result.append(" ");
        }
        return result.toString().trim();
    }
}
