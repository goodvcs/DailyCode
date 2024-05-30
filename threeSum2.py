class Solution(object):
    def threeSum(self, nums):
        s = set()   #  how to creat set
        result = []  # how to creat list 
        nums.sort()  # know how to sort!!
        for i in range(len(nums)):
            j = i + 1
            k = len(nums) - 1
            while j < k:  #  you forget!!
                sum = nums[i] + nums[j] + nums[k]
                if sum == 0:
                    s.add((nums[i], nums[j], nums[k]))   # how to add elements to set, add tuple!!!
                    j += 1
                    k -= 1
                elif sum < 0:
                    j += 1
                else:
                    k -= 1
        # wrong: result.add(s)
        result = list(s) # how to change set to list!
        return result
