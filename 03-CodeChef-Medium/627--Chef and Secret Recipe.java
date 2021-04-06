// https://www.codechef.com/problems/SCRRCP

import java.io.File;
import java.io.FileInputStream;
import java.io.IOError;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

class SCRRCP {
    static Scanner sc;
    static ArrayList<Long> results;
    final static long MAX = (long) Math.pow(2, 60) - 1;
    static long maxYet = -1;

    public static void main(String[] args) throws IOException {
        sc = new Scanner(System.in);

        //sc = new Scanner(new FileInputStream("D:\\Workspace\\IdeaProjects\\Methane\\target\\classes\\scrrcp_input.txt"));
        int t = sc.nextInt();
        while (t-- > 0) {
            execute();
        }
    }

    public static void execute() {
        results = new ArrayList<>();
        int n = sc.nextInt();
        long lastAnswer = -1;
        if (n-- > 0) {
            results.add(query(0));
            maxYet = results.get(0);
        }
        if (n-- > 0)
            lastAnswer = query(MAX);
        while (n-- > 0) {
            maxYet = getIngredient();
            results.add(maxYet);
        }
        if (lastAnswer != -1)
            results.add(lastAnswer);
        if (results.size() > 0)
            printResult();
    }

    private static long getIngredient() {
        long input = maxYet, currMax = maxYet;
        long queryResponse = -1;
        long orMask = 1;
        do {
            long andMask = (orMask - 1) ^ MAX;
            input = (input | orMask) & andMask;
            queryResponse = query(input);
            orMask = orMask << 1;
        }while (queryResponse <= currMax);
        return queryResponse;
    }

    private static long query(long num) {
        System.out.println("1 " + num);
        return sc.nextLong();
    }

    private static void printResult() {
        System.out.println("2 " + Arrays.toString(
                results.toArray())
                .replace(",", "")
                .replace("[", "")
                .replace("]", "").trim());
        sc.nextLong();
    }
}
