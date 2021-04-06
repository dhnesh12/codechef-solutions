import java.io.IOException;
import java.io.DataInputStream;
import java.util.*;
class TestClass {
    
    public static void main(String args[] ) throws Exception {
        FastReader reader = new FastReader();
        StringBuilder sb = new StringBuilder();
        int t = reader.nextInt();
        while(t-- > 0){
            int n = reader.nextInt();
            
            int[] a = new int[n];
            for(int i = 0; i < n; i++) a[i] = reader.nextInt();
            
            int[] doubleA = new int[2 * n];
            System.arraycopy(a, 0, doubleA, 0, n);
            System.arraycopy(a, 0, doubleA, n, n);
            
            // System.out.println(Arrays.toString(a));
            // System.out.println(Arrays.toString(doubleA));
            
            long[] resultN = getExpectedValueForEachLength(a);
            long[] result2N = getExpectedValueForEachLength(doubleA);
            
            for(int i = 1; i <= n; i++) sb.append(result2N[i] - resultN[i]).append(" ");
            sb.append("\n");
        }
        System.out.print(sb); 
        reader.close();
    }
    
    private static long[] getExpectedValueForEachLength(int[] a){
        int n = a.length;
        // System.out.println(n);
        // System.out.println("a - " + Arrays.toString(a));
        
        int[] nextGreaterLeft = new int[n];
        nextGreaterLeft[0] = -1;
        for(int i = 1; i < n; i++){
            int j = i - 1;
            for(; j != -1 && a[j] < a[i]; j = nextGreaterLeft[j]);
            nextGreaterLeft[i] = j;
        }
        // System.out.println("nextGreaterLeft - " + Arrays.toString(nextGreaterLeft));
        
        int[] nextGreaterRight = new int[n];
        nextGreaterRight[n - 1] = n;
        for(int i = n - 2; i >= 0; i--){
            int j = i + 1;
            for(; j != n && a[j] <= a[i]; j = nextGreaterRight[j]);
            nextGreaterRight[i] = j;
        }
        // System.out.println("nextGreaterRight - " + Arrays.toString(nextGreaterRight));
        
        long[] increasing = new long[n + 2];
        long[] constant = new long[n + 2];
        long[] decreasing = new long[n + 2];
        for(int i = 0; i < n; i++){
            int leftLength = i - nextGreaterLeft[i];
            int rightLength = nextGreaterRight[i] - i;
            int len = leftLength + rightLength - 1; 
            
            if(leftLength > rightLength){
                int temp = rightLength;
                rightLength = leftLength;
                leftLength = temp;
            }
            
            increasing[1] += a[i];
            increasing[leftLength + 1] -= a[i];

            if(rightLength > leftLength){
                long val = (long)a[i] * leftLength;
                constant[leftLength + 1] += val;
                constant[rightLength + 1] -= val;
            }
            
            if(len > rightLength){
                long val = (long)a[i] * (len + 1);
                constant[rightLength + 1] += val;
                constant[len + 1] -= val;
                
                decreasing[rightLength + 1] += a[i];
                decreasing[len + 1] -= a[i];
            }
        }
        
        long[] result = new long[n + 2];
        for(int i = 1; i <= n; i++){
            increasing[i] += increasing[i - 1];
            constant[i] += constant[i - 1];
            decreasing[i] += decreasing[i - 1];
            result[i] = (increasing[i] - decreasing[i]) * i + constant[i];
        }
        // System.out.println("increasing - " + Arrays.toString(increasing));
        // System.out.println("constant - " + Arrays.toString(constant));
        // System.out.println("decreasing - " + Arrays.toString(decreasing));
        // System.out.println("result - " + Arrays.toString(result));
        
        return result;
    }
    
    private static class FastReader{
        final private int BUFFER_SIZE = 1 << 16;
        private byte[] buffer;
        private DataInputStream din;
        private int bufferPointer, bytesRead;
        
        public FastReader(){
            buffer = new byte[BUFFER_SIZE];
            din = new DataInputStream(System.in);
            bufferPointer = bytesRead = 0;
        }
        
        private String nextLine() throws IOException{
            StringBuilder sb = new StringBuilder();
            byte c;
            while((c = read()) != -1 && c != '\n'){
                sb.appendCodePoint(c);
            }
            return sb.toString();
        }
        
        private int nextInt() throws IOException{
            int ret = 0;
            byte c = read();
            while(c <= ' '){
                c = read();
            }
            boolean neg = c == '-';
            if(neg){
                c = read();
            }
            while(c >= '0' && c <= '9'){
                ret = ret * 10 + c - '0';
                c = read();
            }
            return (neg) ? -ret : ret;
        }
        
        private long nextLong() throws IOException{
            long ret = 0;
            byte c = read();
            while(c <= ' '){
                c = read();
            }
            boolean neg = c == '-';
            if(neg){
                c = read();
            }
            while(c >= '0' && c <= '9'){
                ret = ret * 10 + c - '0';
                c = read();
            }
            return (neg) ? -ret : ret;
        }
        
        private double nextDouble() throws IOException{
            double ret = 0, div = 1;
            byte c = read();
            while(c <= ' '){
                c = read();
            }
            boolean neg = c == '-';
            if(neg){
                c = read();
            }
            while(c >= '0' && c <= '9'){
                ret = ret * 10 + (c - '0');
                c = read();
            }
            if(c == '.'){
                while((c = read()) >= '0' && c <= '9'){
                    ret += (c - '0') / (div *= 10);
                }
            }
            return (neg) ? -ret : ret;
        }
        
        private void fillBuffer() throws IOException{
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if(bytesRead == -1){
                buffer[0] = -1;
            }
        }
        
        private byte read() throws IOException{
            if(bufferPointer == bytesRead){
                fillBuffer();
            }
            return buffer[bufferPointer++];
        }
        
        private boolean hasNext() throws IOException{
            if(bufferPointer == bytesRead){
                fillBuffer();
            }
            return (buffer[0] != -1);
        }
        
        private void close() throws IOException{
            if(din != null){
                din.close();
            }
        }
        
    }
}