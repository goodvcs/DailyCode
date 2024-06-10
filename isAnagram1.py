class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        if(len(s) != len(t)):
            return False  # F is capitalized
        ss = sorted(s)   # sorted(string) to list of char
        tt = sorted(t)

        return ss == tt  # compare sorted char list
