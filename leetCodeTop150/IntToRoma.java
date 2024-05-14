class Solution {
    public String intToRoman(int num) {
        String[] ones = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};  
        // not int[] but String[], = { } not = []
        String[] tens = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
        String[] hrds = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"}; 
        String[] thds = {"", "M", "MM", "MMM"};  // the greatest of M is 3
        StringBuilder sb = new StringBuilder();
        sb.append(thds[num / 1000]);
        sb.append(hrds[num / 100 % 10]);
        sb.append(tens[num / 10 % 10]);
        sb.append(ones[num % 10]);
        return sb.toString();  // StringBuilder is not String, need .toString
    }
}
