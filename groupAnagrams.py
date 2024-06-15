class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        map = {}
        for s in strs:
            s_sorted = "".join(sorted(s))   # sorted(s) return a list: ['a', 'b'] but we want "ab"
            if s_sorted in map:
                map[s_sorted].append(s)   # add to list as s not [s]: not .applend([s]) otherwish : [["ab",["ba"]]] 
            else:
                map[s_sorted] = [s]   # set valse as [s] not s: not = s otherwise ["ab","ba"] but not [["ab","ba"]]
        return list(map.values())  #  if not list(), map.values would return a view: dict_values([['eat', 'tea', 'ate'], ['tan', 'nat'], ['bat']])
