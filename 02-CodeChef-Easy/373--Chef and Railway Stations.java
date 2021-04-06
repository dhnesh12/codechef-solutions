
import java.io.*;
import java.util.*;

class ChefAndRailwayStations_NlogN {
    static long gcd(long a, long b){
        if(a%b==0)
            return b;
        else return gcd(b, a%b);
    }
    public static void main(String[] args) throws IOException {
        /*long start = System.currentTimeMillis();
        Soumit sc = new Soumit("Input.txt");
        sc.streamOutput("Output1.txt");*/

        Soumit sc = new Soumit();

        int t = sc.nextInt();
        StringBuilder sb = new StringBuilder();
        while (t-->0){
            int n = sc.nextInt();
            int m = sc.nextInt();

            int[] x = sc.nextIntArray(n);
            int[] y = sc.nextIntArray(m);

            int[] hashx_pos = new int[100100];
            int[] hashx_neg = new int[100100];
            int[] hashy_pos = new int[100100];
            int[] hashy_neg = new int[100100];
            for(int i: x){
                if(i>=0)
                    hashx_pos[i]++;
                else hashx_neg[i*-1]++;
            }
            for(int i: y){
                if(i>=0)
                    hashy_pos[i]++;
                else hashy_neg[i*-1]++;
            }

            long ans = 0;
            for(int i=1;i*i<=100000;i++){
                for(int j=i;j*j<=100000;j++){
                    if(gcd(i, j)==1){
                        for(int k=1;;k++){
                            int gab = k*i*j;
                            int a = k*i*i;
                            int b = k*j*j;
                            if(a>100000||b>100000)
                                break;

                            if(hashx_pos[k*i*i]>0 && hashx_neg[k*j*j]>0){
                                if(hashy_pos[gab]>0) {
                                    ans++;
                                }
                                if(hashy_neg[gab]>0) {
                                    ans++;
                                }
                            }
                            if(a!=b && hashx_pos[k*j*j]>0 && hashx_neg[k*i*i]>0){
                                if(hashy_pos[gab]>0){
                                    ans++;
                                }
                                if(hashy_neg[gab]>0){
                                    ans++;
                                }
                            }

                            if(hashy_pos[k*i*i]>0 && hashy_neg[k*j*j]>0){
                                if(hashx_pos[gab]>0){
                                    ans++;
                                }
                                if(hashx_neg[gab]>0){
                                    ans++;
                                }
                            }
                            if(a!=b && hashy_pos[k*j*j]>0 && hashy_neg[k*i*i]>0){
                                if(hashx_pos[gab]>0){
                                    ans++;
                                }
                                if(hashx_neg[gab]>0){
                                    ans++;
                                }
                            }
                        }
                    }
                }
            }

            if(hashx_pos[0]>0 || hashy_pos[0]>0){
                ans += ((long)n-hashx_pos[0])*((long) m-hashy_pos[0]);
            }

            sb.append(ans).append("\n");
        }

        System.out.println(sb.toString());

        sc.close();
    }

    static class Soumit {
        final private int BUFFER_SIZE = 1 << 18;
        final private DataInputStream din;
        final private byte[] buffer;
        private PrintWriter pw;
        private int bufferPointer, bytesRead;
        StringTokenizer st;

        public Soumit() {
            din = new DataInputStream(System.in);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public Soumit(String file_name) throws IOException {
            din = new DataInputStream(new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public void streamOutput(String file) throws IOException {
            FileWriter fw = new FileWriter(file);
            BufferedWriter bw = new BufferedWriter(fw);
            pw = new PrintWriter(bw);
        }

        public void println(String a) {
            pw.println(a);
        }

        public void print(String a) {
            pw.print(a);
        }

        public String readLine() throws IOException {
            byte[] buf = new byte[3000064]; // line length
            int cnt = 0, c;
            while ((c = read()) != -1) {
                if (c == '\n')
                    break;
                buf[cnt++] = (byte) c;
            }
            return new String(buf, 0, cnt);
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        public void sort(int[] arr) {
            ArrayList<Integer> arlist = new ArrayList<>();
            for (int i : arr)
                arlist.add(i);

            Collections.sort(arlist);
            for (int i = 0; i < arr.length; i++)
                arr[i] = arlist.get(i);
        }

        public void sort(long[] arr) {
            ArrayList<Long> arlist = new ArrayList<>();
            for (long i : arr)
                arlist.add(i);

            Collections.sort(arlist);
            for (int i = 0; i < arr.length; i++)
                arr[i] = arlist.get(i);
        }

        public int[] nextIntArray(int n) throws IOException {
            int[] arr = new int[n];
            for (int i = 0; i < n; i++) {
                arr[i] = nextInt();
            }

            return arr;
        }

        public long[] nextLongArray(int n) throws IOException {
            long[] arr = new long[n];
            for (int i = 0; i < n; i++) {
                arr[i] = nextLong();
            }

            return arr;
        }

        public double[] nextDoubleArray(int n) throws IOException {
            double[] arr = new double[n];
            for (int i = 0; i < n; i++) {
                arr[i] = nextDouble();
            }

            return arr;
        }

        public int nextInt() throws IOException {
            int ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');

            if (neg)
                return -ret;
            return ret;
        }

        public long nextLong() throws IOException {
            long ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do {
                ret = ret * 10 + c - '0';
            }
            while ((c = read()) >= '0' && c <= '9');
            if (neg)
                return -ret;
            return ret;
        }

        public double nextDouble() throws IOException {
            double ret = 0, div = 1;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();

            do {
                ret = ret * 10 + c - '0';
            }
            while ((c = read()) >= '0' && c <= '9');

            if (c == '.') {
                while ((c = read()) >= '0' && c <= '9') {
                    ret += (c - '0') / (div *= 10);
                }
            }

            if (neg)
                return -ret;
            return ret;
        }

        private void fillBuffer() throws IOException {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1)
                buffer[0] = -1;
        }

        private byte read() throws IOException {
            if (bufferPointer == bytesRead)
                fillBuffer();
            return buffer[bufferPointer++];
        }

        public void close() throws IOException {
            /*if (din == null)
                return;*/
            if (din != null) din.close();
            if (pw != null) pw.close();
        }
    }
}
