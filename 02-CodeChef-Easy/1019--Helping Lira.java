/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	   public static void main(String[] args) throws IOException {

        Scanner fk = new Scanner(System.in);
        PrintWriter pr = new PrintWriter(System.out);
        //FileWriter writer = new FileWriter("output.txt");

        int n = fk.nextInt();

        double[] area = new double[n];
        for(int i=0; i<n; i++){

            long x1= fk.nextLong(), y1 = fk.nextLong(),
                    x2= fk.nextLong(), y2 = fk.nextLong(),
                    x3= fk.nextLong(), y3 = fk.nextLong();

            double a = Math.abs(0.5*(x1*(y2-y3) - y1*(x2-x3) + (x2*y3 - x3*y2)));
            area[i] = a;
        }

        double min =Double.MAX_VALUE, min_i = 0, max = 0, max_i = 0;

        for(int i=0; i<n; i++){
            if(area[i] <= min) {
                min = area[i];
                min_i = i + 1;
            } if(area[i] >= max){
                max = area[i];
                max_i = i+1;
            }
        }

        pr.println((long)min_i+" "+(long)max_i);

        pr.close();
        //writer.close();
    }


}
