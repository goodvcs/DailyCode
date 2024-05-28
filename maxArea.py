class Solution(object):
    def maxArea(self, height):
        l = 0
        r = len(height) -1
        area = 0
        while l < r:
            width = r - l
            # height = min(height[l], height[r])  name conflict!!
            h = min(height[l], height[r]) 
            area = max(area, width * h)
            if height[l] < height[r]:
                l += 1
            else:
                r -= 1
        
        return area
