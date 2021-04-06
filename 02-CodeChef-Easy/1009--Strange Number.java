

import java.io.BufferedReader; 
import java.io.IOException; 
import java.io.InputStreamReader; 
import java.util.Scanner; 
import java.util.StringTokenizer; 
import java.util.*;
  
 class c670a
{ 
    //By shwetank_verma
    static class FastReader 
    { 
        BufferedReader br; 
        StringTokenizer st; 
  
        public FastReader() 
        { 
            br = new BufferedReader(new
                     InputStreamReader(System.in)); 
        } 
  
        String next() 
        { 
            while (st == null || !st.hasMoreElements()) 
            { 
                try
                { 
                    st = new StringTokenizer(br.readLine()); 
                } 
                catch (IOException  e) 
                { 
                    e.printStackTrace(); 
                } 
            } 
            return st.nextToken(); 
        } 
  
        int nextInt() 
        { 
            return Integer.parseInt(next()); 
        } 
  
        long nextLong() 
        { 
            return Long.parseLong(next()); 
        } 
  
        double nextDouble() 
        { 
            return Double.parseDouble(next()); 
        } 
  
        String nextLine() 
        { 
            String str = ""; 
            try
            { 
                str = br.readLine(); 
            } 
            catch (IOException e) 
            { 
                e.printStackTrace(); 
            } 
            return str; 
        } 
    } 
    static int mod=1000000007;
    static boolean primes[]=new boolean[1000007];
    
    static boolean seive(int n){
        Arrays.fill(primes,true);
        primes[0]=primes[1]=false;
        for(int i=2;i*i<=n;i++){
            if(primes[i]==true){
                for(int p=i*i;p<=n;p+=i){
                    primes[p]=false;
                }
            }
        }
        if(n<1000007){
            return primes[n];
        }
        return false;
        
    }
    static int gcd(int a,int b){
        if(b==0)
        return a;
        return gcd(b,a%b);
    }
    static long GCD(long a,long b){
        if(b==0)
        return a;
        return GCD(b,a%b);
    }
    static ArrayList<Integer> prevgreater(int arr[],int n) {
    	Stack<Integer> s=new Stack<>();
    	ArrayList<Integer> l=new ArrayList<>();
    	s.push(arr[0]);
    	for(int i=0;i<n;i++) {
    		while(!s.empty()&&s.peek()<=arr[i]) {
    			s.pop();
    		}
    		int pg=(s.empty())?-1:s.peek();
    		l.add(pg);
    		s.push(arr[i]);
    	}
    	return l;
    }
  
    public static void main(String[] args) 
    { 
        FastReader sc=new FastReader(); 
       
           
                int t=1;
                t=sc.nextInt();
                long s=0;
                while(t-->0){
                	 long n=sc.nextLong();
                	 long k=sc.nextLong();
                	 int c=0;
                	 for(long i=2;i*i<=n;i++) {
                		 while(n%i==0) {
                			 c++;
                			 n=n/i;
                		 }
                	 }
                	 if(n>1)
                		 c++;
                	 if(k>=1&&c>=k) {
                		 System.out.println(1);
                	 }
                	 else
                		 System.out.println(0);
                     
              
                
                } 
            
        
    } 
}