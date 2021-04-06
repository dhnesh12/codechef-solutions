import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

class Main {
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;
        public FastReader(){
            br = new BufferedReader(new InputStreamReader(System.in));
        }
        String next(){
            while (st==null || !st.hasMoreElements() ){
                try{
                    st = new StringTokenizer(br.readLine());
                }
                catch (IOException e){
                    e.printStackTrace();
                }

            }
            return st.nextToken();
        }
        int readInt(){
            return Integer.parseInt(next());
        }
        long readLong(){
            return Long.parseLong(next());
        }
        float readFloat(){
            return Float.parseFloat(next());
        }
    }
    public static void main(String[] args){
        FastReader reader = new FastReader();
        PrintWriter pw = new PrintWriter(System.out);
        int T = reader.readInt();
        double sum;
        while (T-- > 0){
            int numofpages = reader.readInt();
            int leaves = (numofpages+1)/2;
            sum = (double) (numofpages*(numofpages+1))/2;
            int f = reader.readInt();
            for(int i = 0;i < f;i++){
                int x = reader.readInt();            
                sum -= x;
            }
            int remove = reader.readInt();
            sum = (sum*(leaves-remove))/leaves;
            System.out.printf("%.4f\n",sum);
        }
    }
}