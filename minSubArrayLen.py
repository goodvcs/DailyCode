class Solution(object):
    def minSubArrayLen(self, target, nums):
        """
        :type target: int
        :type nums: List[int]
        :rtype: int
        """
        left = 0
        sum = 0
        result = float("inf")  # set result as the largest possible value
        for i in range(len(nums)):  # iterate range() and put len()inside
            sum += nums[i]
            #   need to continue shrinking the window while sum is greater than or equal to 
            #    target to ensure you find the minimal length subarray. not if !!!!!!
            while sum >= target:
                result = min(result, i - left + 1)
                sum -= nums[left]
                left += 1  # move left to right by +1, not -1
        return 0 if result == float("inf") else result  # it is inf not int!
