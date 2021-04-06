/* package codechef; // don't place package name! */


import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Cocechef {


    public static void main(String[] args) throws java.lang.Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine());
            String s[] = br.readLine().split(" ");
            int nums[] = new int[n + 1];
            HashMap<Integer, Integer> hmap = new HashMap<>();
            ArrayList<Integer> m = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                nums[i] = Integer.parseInt(s[i]);
            }
            Map<Integer, Integer> mp1 = new HashMap<Integer, Integer>();
            Map<Integer, Integer> mp2 = new HashMap<Integer, Integer>();
            int cnt = 1;
            nums[n] = -1;
            for (int i = 0; i < n; ++i) {
                if (nums[i] == nums[i + 1])
                    cnt++;
                else {
                    mp1.put(nums[i], mp1.getOrDefault(nums[i], 0) + 1);
                    mp2.put(cnt, mp2.getOrDefault(cnt, 0) + 1);
                    cnt = 1;
                }
            }
            boolean ok = true;
            for (Map.Entry<Integer, Integer> entry : mp1.entrySet())
                if (entry.getValue() != 1) {
                    ok = false;
                    break;
                }
            for (Map.Entry<Integer, Integer> entry : mp2.entrySet())
                if (entry.getValue() != 1) {
                    ok = false;
                    break;
                }
            System.out.println(ok?"YES":"NO");
        }
    }
}












