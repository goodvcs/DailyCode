package leetCodeTop150;

public class LengthOfLastWord58Easy {

    /*Given a string s consisting of words and spaces, return the length of the last word in the string.
    A word is a maximal substring consisting of non-space characters only.*/
    public static void main(String[] args) {
        System.out.println(lengthOfLastWord("how are you   "));
    }

    public static  int lengthOfLastWord(String s) {
        String[] strings = s.split(" ");
        return strings[strings.length-1].length();

    }
}
