class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        left = 0
        result = 0
        charSet = set()  # cannot named as set!!

        for right in range(len(s)):
            if s[right] not in charSet:
                charSet.add(s[right])
                result = max(result, right - left + 1)  # max is lowercase
            else:
                while s[right] in charSet:
                    charSet.remove(s[left])
                    left += 1
                charSet.add(s[right])
        return result

        
