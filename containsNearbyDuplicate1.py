class Solution:
    def containsNearbyDuplicate(self, nums: List[int], k: int) -> bool:
        index_map = {}   # how to create a dictionary: key:value, value: index
        for i, num in enumerate(nums):   # brown color is method
            if num in index_map:    #  not for but if
                diff = i - index_map[num]
                if diff <= k:
                    return True   #  blue color is right
            index_map[num] = i  # note: put (value, index) into map
        return False
