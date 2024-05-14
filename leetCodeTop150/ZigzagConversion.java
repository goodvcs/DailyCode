class Solution {
    public String convert(String s, int numRows) {
        if(numRows == 1) return s;  // do it at first!
        String[] rows = new String[Math.min(s.length(), numRows)];  // array to store each row elements
        Arrays.fill(rows, "");
        int curRow = 0;  // current row
        boolean goDown = false;
        for(char c : s.toCharArray()){ // c in char is lowercase; String.toCharArray() to get chars
            rows[curRow] += c;
            if(curRow == 0 || curRow == numRows - 1) goDown = !goDown; // change direction
            curRow += goDown?  1 : -1;  // change curRow by += not =
        }
        String result = "";
        for(String r : rows){
            result += r;           
        }
        return result;
    }
}
        
