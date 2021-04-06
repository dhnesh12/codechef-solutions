

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;

public class Main {
    public static void main(String[] arg) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            String[] input = br.readLine().split("\\s+");
            int n = Integer.parseInt(input[0]);
            int x = Integer.parseInt(input[1]);
            long vac = x;
            ArrayList<Long> a = new ArrayList<>();
            input = br.readLine().split("\\s+");
            for (int i = 0; i < n; i++) {
                a.add((long) Integer.parseInt(input[i]));   
            }

            int days = 0, i = 0;
            Collections.sort(a);
            while (i < n) {
                long cur = a.get(i);
                if(cur <= vac/2){
                    i++;
                } else if(cur <= vac){
                    i++;
                    vac = cur << 1;
                } else {
                    vac = vac << 1;
                }
                days++;
            }
            System.out.println(days);
        }
    }
}

