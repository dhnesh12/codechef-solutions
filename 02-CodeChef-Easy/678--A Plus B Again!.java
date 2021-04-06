import java.util.*;
import java.io.*;
import java.lang.*;
public class Main{
       static class FastReader{
               BufferedReader br;
               StringTokenizer st;
               public FastReader()throws IOException{
                 br=new BufferedReader(new InputStreamReader(System.in));
               }
               public FastReader(String s)throws IOException{
                 br=new BufferedReader(new FileReader(new File(s)));
               }
               String next(){
                 while(st==null || !st.hasMoreElements()){
                   try{
                      st=new StringTokenizer(br.readLine());
                   }
                   catch(Exception e){
                     e.printStackTrace();
                   }
                 
                 }
                 return st.nextToken();
               }
               String nextLine(){
               String str="";
                 try{
                   str=br.readLine();
                 }
                catch(Exception e){
                  e.printStackTrace();
                }
               return str;
               }
              int nextInt(){
                return Integer.parseInt(next()); 
              } 
            long nextLong(){
              return Long.parseLong(next());
            }
            double nextDouble(){
              return Double.parseDouble(next());
            }
       
       }
        private static final int N=200;
        private static int[] primes;
        public static void main(String args[]) throws IOException {
            FastReader in = new FastReader();
           PrintWriter out=new PrintWriter(new BufferedOutputStream(System.out));
           double []e=new double[100001];
           e[1]=0.45;
           for(int i=2;i<e.length;i++){
              e[i]=0.45+0.1*e[i-1];
           }
           for(int i=2;i<e.length;i++){
             e[i]+=e[i-1];
           }
           int T=in.nextInt();
           while(T-->0){
              int n=in.nextInt();
              out.println(e[n]);
           
           }
            out.close();
        }
      
 
}  

