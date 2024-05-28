
class Solution:
    def threeSum(self, nums):
        nums.sort()  # Step 1: Sort the array
        result = []
        n = len(nums)
        
        for i in range(n):
            # Skip duplicate elements
            if i > 0 and nums[i] == nums[i - 1]:
                continue
            
            left, right = i + 1, n - 1  # Step 3: Initialize two pointers
            
            while left < right:
                total = nums[i] + nums[left] + nums[right]
                
                if total == 0:
                    result.append([nums[i], nums[left], nums[right]])
                    left += 1
                    right -= 1
                    
                    # Skip duplicates for the second and third elements
                    while left < right and nums[left] == nums[left - 1]:
                        left += 1
                    while left < right and nums[right] == nums[right + 1]:
                        right -= 1
                
                elif total < 0:
                    left += 1  # Move the left pointer to the right to increase the sum
                else:
                    right -= 1  # Move the right pointer to the left to decrease the sum
        
        return result

# Example usage:
sol = Solution()
print(sol.threeSum([-1, 0, 1, 2, -1, -4]))  # Expected output: [[-1, -1, 2], [-1, 0, 1]]
