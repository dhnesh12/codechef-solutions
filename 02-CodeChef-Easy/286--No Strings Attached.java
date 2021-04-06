/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
    public static void main(String[] args) throws IOException {
        int t;
        String str;

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int[] left, right;
        t = Integer.parseInt(br.readLine());

        while (t-->0){
            left = new int[26];
            right = new int[26];

            str = br.readLine();

            for (int i = 0; i < str.length(); i++) {
                int charIndex = str.charAt(i) - 'a';
                right[charIndex]++;
            }
            int maxReduction = 0; 
            long totalY=0;
            for (int i = 0; i < str.length(); i++) {
                int charIndex = str.charAt(i) - 'a';
                right[charIndex]--;
                int leftP = getLeftPairs(left, charIndex);
                int rightP = getRightPairs(right, charIndex);
                int y = leftP+rightP, minY = y;
                for (int j = 0; j < 26; j++) {
                    int leftPairs = getLeftPairs(left, j);
                    int rightPairs = getRightPairs(right, j);
                    int cost = Math.abs(charIndex-j);
                    minY = Math.min(minY, leftPairs + rightPairs + cost);
                }
                totalY = totalY + (long)rightP;
                int reduction = y-minY;
                maxReduction = Math.max(reduction, maxReduction);
                left[charIndex]++;
            }
            System.out.println(totalY-(long)maxReduction);
        }
    }

    private static int getRightPairs(int[] right, int charIndex) {
        int resp = 0;
        for (int i = charIndex+1; i < 26; i++) {
            resp+=right[i];
        }
        return resp;
    }

    private static int getLeftPairs(int[] left, int charIndex) {
        int resp = 0;
        for (int i = 0; i < charIndex; i++) {
            resp+=left[i];
        }
        return resp;
    }
}
