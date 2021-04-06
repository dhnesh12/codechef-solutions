import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

class Codechef {
    public static void main(String[] args) throws java.lang.Exception {

        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        int t = Integer.parseInt(bf.readLine());
        while (t-- > 0) {
            String str = bf.readLine();
            long sum = 0;
            for (int i = 0; i < str.length(); i++) {
                sum = sum + (long)(str.charAt(i) - '0');
            }
            // for no greater than 0 & less than 9
            if(sum == sum %9 && str.length() != 1) {
                bw.write( 9 - (sum % 9) + "\n");
            }else {
                long min = Math.min(sum % 9, 9 - (sum % 9));
                bw.write(min + "\n");
            }
        }
        bw.close();
        bf.close();
    }
}
