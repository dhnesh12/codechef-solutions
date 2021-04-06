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
            String s = br.readLine();
            StringBuilder sb= new StringBuilder("");

            ArrayList<Character> alps = new ArrayList<>();
            int count = 0;
           alps.add(s.charAt(0));
            for (int i = 0; i < s.length()-1; i++) {
                if (s.charAt(i) != s.charAt(i + 1)) {


                    alps.add(s.charAt(i + 1));

                }
            }

            for(int i=0;i<alps.size();i++){
                for(int j=0;j<s.length();j++){
                    if(alps.get(i)==s.charAt(j))
                        count++;

                }
                sb.append(alps.get(i)+""+count);
                count=0;



            }
            System.out.println(sb.length()<s.length()?"YES":"NO");


        }
    }
}












