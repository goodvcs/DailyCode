package leetCodeTop150;

import java.util.Arrays;

public class Candy135Hard {

    /*here are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
You are giving candies to these children subjected to the following requirements:
Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.*/

    public static void main(String[] args) {
        System.out.println(candy(new int[]{1, 0, 2}));


    }

    public static int candy(int[] ratings){
        int n = ratings.length;
        int[] candy = new int[n];
        Arrays.fill(candy,1);  // initiate 1
        for (int i = 1; i < n; i++) {
            if(ratings[i] > ratings[i-1]){  // compare rating[i], not candy[i]
                candy[i] = candy[i-1] + 1;
            }
        }
        for (int i = n-2; i >= 0 ; i--) {
            if(ratings[i] > ratings[i+1]){
                candy[i] = Math.max(candy[i], candy[i+1] + 1);  //do not forget plus 1
            }
        }
        int totalCandies = 0;
        for (int i : candy) {
            totalCandies += i;
        }
        return totalCandies;
    }
}
