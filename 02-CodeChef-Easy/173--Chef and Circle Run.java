import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.*;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;

class ChefandCircleRun2 {
    public static void main(String[] args) throws IOException {
//                        BufferedReader f = new BufferedReader(new FileReader("C:\\Users\\Owner\\CodeForces\\src\\test.in"));
//        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("C:\\Users\\Owner\\CodeForces\\src\\test.out")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int cases = Integer.parseInt(f.readLine());
        for(int t = 0; t < cases; t++){
            int n = Integer.parseInt(f.readLine());
            String[] raw = f.readLine().split(" ");
            int[] nodes = new int[n + 1];
            int[] sums = new int[n + 1];
            sums[0] = 0;
            for(int i = 0; i < n; i++){
                //node [i] = i to i + 1
                nodes[i] = Integer.parseInt(raw[i]);
                //sums[i] is from 1 to i + 1
                //sums[i] = sums[i  - 1] + nodes[i];
            }

            raw = f.readLine().split(" ");
            int start = Integer.parseInt(raw[0]) - 1;
            int end = Integer.parseInt(raw[1]) - 1;
            int a = solve(nodes, n, start, end);
            int b = solve(nodes, n, end, start);
            out.println(Math.min(a, b));


        }

        out.close();

    }

    public static int solve(int[] nums, int n, int start, int end){
        int sum = 0;
        for(int i = start; i != end; i = (i + 1) % n){
            sum += nums[i];
        }
        int [] partial = new int[n];
        int k = 0;
        for(int i = end; i != start; i = (i + 1) % n){
            sum += 2 * nums[i];
            partial[k++] = nums[i];
        }

        return sum - 2 * subarray(partial);

    }

    public static int subarray(int[] nums){
        int[] returns = new int[nums.length];
        int[] sums = new int[nums.length];
        sums[0] = nums[0];
        returns[0] = Math.max(nums[0], 0);
        for(int i = 1; i < nums.length; i++){
            sums[i] = Math.max(sums[i - 1], 0) + nums[i];
            returns[i] = Math.max(returns[i - 1], sums[i]);
        }
        return returns[nums.length - 1];
    }
}
