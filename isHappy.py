class Solution:
    def isHappy(self, n: int) -> bool:
        def sum_squares(num):
                return sum(int(digit)**2 for digit in str(num))

        slow = n
        fast = n
        while True:
            slow = sum_squares(slow)   #"Floyd's Tortoise and Hare"
            fast = sum_squares(sum_squares(fast))
            if(slow == 1 or fast == 1):
                return True
            if(slow == fast):
                return False
