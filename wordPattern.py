class Solution:
    def wordPattern(self, pattern: str, s: str) -> bool:
        char_to_word = {}   // map? using dictionary
        word_to_char = {}
        words = s.split()   // how to split a string?
        if(len(pattern) != len(words)): return False   // note: F capitalized
        for w, c in zip(words, pattern):   // zip to combine two elements into tuple
            if(w in word_to_char):
                if(word_to_char[w] != c):   // != for string is ok
                    return False
            if(c in char_to_word):
                if(char_to_word[c] != w):
                    return False
            char_to_word[c] = w
            word_to_char[w] = c

        return True;        
