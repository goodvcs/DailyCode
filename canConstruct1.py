class Solution:
    def canConstruct(self, ransomNote: str, magazine: str) -> bool:
        from collections import Counter
        magazine_c = Counter(magazine)   # use a dictionary to store frequency of each character
        ransomNote_c = Counter(ransomNote)
        for c in ransomNote_c:
            if ransomNote_c[c] > magazine_c[c]:
                return False  # not false, different from java
        return True  # not true
