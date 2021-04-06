/* package codechef; // don't place package name! */

import java.util.Scanner;

public class Main{

    public static void main(String[] args){
        try{

            Scanner scanner = new Scanner(System.in);
            int T = scanner.nextInt();

            while(T-->0){
                float[] factory = new float[scanner.nextInt()];
                float[][] store = new float[scanner.nextInt()][factory.length];
                for (int i = 0; i < factory.length; i++) {
                    factory[i] = scanner.nextFloat();
                }
                for (int i = 0; i < store.length; i++) {
                    for (int j = 0; j < factory.length; j++) {
                        store[i][j] = scanner.nextFloat();
                    }
                }

                int[] openFactory = new int[factory.length];
                int[] store_ans = new int[store.length];

                for (int i = 0; i < store.length; i++) {
                    float lowest_cost = Float.MAX_VALUE;
                    for (int j = 0; j < factory.length; j++) {
                        float cost = factory[j] + store[i][j];
                        if (lowest_cost > cost){
                            lowest_cost = cost;
                            store_ans[i] = j;
                        }if (lowest_cost == cost){
                            if (openFactory[j]==1){
                                store_ans[i] = j;
                            }
                        }
                    }
                    openFactory[store_ans[i]] = 1;
                }
                for (int j = 0; j < factory.length; j++) {
                    System.out.print(openFactory[j]);
                    System.out.print(" ");
                }
                System.out.println();
                    for (int i = 0; i < store.length; i++) {
                        System.out.print(store_ans[i]+1);
                        System.out.print(" ");
                }
                System.out.println();
            }

        }
        catch(Exception e){e.printStackTrace();}
    }



}