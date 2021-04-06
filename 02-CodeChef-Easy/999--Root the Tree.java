/* package codechef; // don't place package name! */

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;
import java.lang.*;
import java.io.*;
import java.math.BigInteger;
import java.text.DecimalFormat;
	class Main
		{  
		static class pair implements Comparable<pair>
		 {
		     long x;
		     int y;
		     pair(long x,int y)
		     {
		         this.x=x;
		         this.y=y;
		     }
		     public int compareTo(pair o)
		     {
		         return (int)(x-o.x);
		     }

		 }
	static	class Pair
		{
			int x,y;
			Pair(int x, int y)
			{
				this.x = x;
				this.y = y;
			}
		}
		static class PairComparator implements Comparator<Pair>
		{
			public int compare(Pair a, Pair b)
			{
				if(a.x==b.x)
					return a.y-b.y;
				return a.x-b.x;
			}
		}
		static class Point {
			public double x, y;
		 
			private static final int MAX = (int) 1e6 + 1;
		 
			public Point(double x, double y) {
				this.x = x;
				this.y = y;
			}
		 
			public int hashCode() {
				return (int)x * MAX + (int)y;
			}
		 
			public boolean equals(Object ob) {
				if(ob instanceof Point) {
					Point other = (Point) ob;
					return other.x == x && other.y == y;
				}
				
				return false;
			}
		 
			public String toString() {
				return "(" + x + ", " + y + ")";
			}
		}
	/*	static int days4=0;
		static int all;
		static long phi[]=new long[1000001];
		static long ans[]=new long[1000001];
		//static int tree[],sum[];
		//public static long mod = 1000000007;	public static long [][] tempMatrix;
		public static long max = (long) Math.pow(10, 9) + 7;
		static StringBuilder res = new StringBuilder();
		//static Node tree[];
		//static int a[];
		static long mod = 998244353;
		 public static int rootColor=0;
		 static int MX = (1<<18);
		 static boolean primes[]=new boolean[10000001];
		 */
		static double pi = 3.1415926535; 
		 private static final int MAXN = 5000;
		    private static final int MOD = 1000_000_007;
		 //   private static Modular modular_nCr = new Modular(MOD);
		  //  private static Modular modular = new Modular(MOD);
		    private static final long[][] nCr = new long[MAXN+5][MAXN+5];
		  //  static int[] maxval = new int[1000000];
		 //   static int[] minval = new int[1000000];
		  //  private static long bruteAns = 1;
		 //   static double eps = 1e-7;
		    static {
		    	nCr[0][0]=1;
				for(int i=0;i<=MAXN;i++)
					nCr[i][0]=1;
				for(int i=1;i<=MAXN;i++){
					for(int j=1;j<=i;j++){
						nCr[i][j]=(nCr[i-1][j-1]+nCr[i-1][j])%MOD;
					}
				}
			}
		/*
		    static { nCr[0][0] = 1;
		    for (int i = 1; i < MAXN; i++) {
		        nCr[i][0] = 1;
		        for (int j = 1; j <= i; j++) {
		            nCr[i][j] = modular_nCr.add(nCr[i - 1][j - 1], nCr[i - 1][j]);
		        } }
			}
			*/
		    static long m=1000000007;
			public static void main (String[] args) throws java.lang.Exception
			{  
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			PrintWriter pw=new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
			FastReader in = new FastReader(System.in);
			StringBuilder sb = new StringBuilder();
	      //  FastScanner in=new FastScanner();
		//	Scanner sc = new Scanner(System.in);
			PrintWriter out=new PrintWriter(System.out);
			
		//	HashMap<Integer, Integer> h = new HashMap<Integer, Integer>();
		//	TreeMap<Integer, Integer> h1 = new TreeMap<Integer, Integer>();
			HashMap<Integer, Integer> h2 = new HashMap<Integer, Integer>();
		//	HashSet<Point> s = new HashSet<Point>();
			
		//	HashSet<Double> s2 = new HashSet<Double>();
		//	HashSet<Double> s3 = new HashSet<Double>();
			//	HashSet<Character> h2 = new HashSet<Character>();
			//long t= in.nextLong();
			//	long t = in.nextLong();
			//DecimalFormat df = new DecimalFormat("#,###,##0.000000");
			
	/*	 boolean prime[]=new boolean[10000000];
			   int p[]=new int[10000000];
			    int k=1;
			    Arrays.fill(prime, true);
			    prime[0]=false;
			    prime[1]=false;for(int i=2;i<10000000;i++)
			    {
			        if(!prime[i])
			        {
			        	p[i]=p[i-1];
			            continue;
			        }
			        p[i]=k; k++;
	        for(long j=(long)i*i;j<10000000;j+=i)
            prime[(int)j]=false;
    }*/
			
			int t = in.nextInt();
			while(t-->0)
			{  
				int n=in.nextInt();
		       int[] a = new int[n];
		       for(int i=0;i<n-1;i++) 
		       {
		    	 int x = in.nextInt();
		    	 int y = in.nextInt();
		    	 a[y-1]++;
			 }
		       int ans=0;
		       for(int i=0;i<n;i++)
		       {
		    	   if(a[i]==0)
		    		   ans++;
		       }
		       System.out.println(ans-1);
			}
			}
			
					
				
			
			
			
			
			
				/*
long mod = 1000000007;
//StringBuilder sb = new StringBuilder();
//	DecimalFormat df = new DecimalFormat("######0.00000000000");
//	int[] dp = new int[101];
String[] S1;

double[][] Comb=new double[1000+1][1000+1];
for(int i=0;i<1001;i++)
{
	Comb[i][0]=Comb[i][i]=1.0;
	for(int j=1;j<i;j++)
	Comb[i][j]=Comb[i-1][j]+Comb[i-1][j-1];
}
			*/
			public static long gcd(long a,long b,long n){
			    if(a==b){
			        return (power(a,n,m)+power(b,n,m))%m;
			    }
			    long res=1l;
			    long num=a-b;
			    for(long i=1;i*i<=num;i++){
			        if(num%i==0){
			            long temp= (power(a,n,i)+ power(b,n,i))%i;
			            if(temp==0){
			                res=Math.max(res,i);
			            }
			            temp= (power(a,n,num/i) + power(b,n,num/i))%(num/i);
			             if(temp==0){
			                res=Math.max(res,num/i);
			            }
			        }
			    }
			    return res%m;
			}
			public static long power(long a,long n,long d){
			    long res=1l;
			    while(n>0){
			        if(n%2==1){
			            res =((res%d)*(a%d))%d;
			            n--;
			        }else{
			            a=((a%d)*(a%d))%d;
			            n=n/2;
			        }
				   }
				   return res%m;
			}
/*	static long power(long x,long y) { 
        long res=1;  
        x%=m;  
        while(y>0) { 
            if(y%2!=0) 
                res=(res*x)%m; 
            y=y>>1;
            x=(x*x)%m; 
        } 
        return res; 
    } 			
*/
	    
static long gcd(long a, long b)
{
if(b==0)
return a;
else
return gcd(b, a%b);
}
static long  nextPower_2 (  long x, long y )
{

long  count  =  0 ;
while ( y < x )
{count ++ ;
y  =  y <<  1 ;
}
return  count ;
}
/*
static long power(long a, long b, long p) 
{ 	long x = 1, y = a;
while (b > 0) {
if (b % 2 == 1) {
x = (x * y);
if (x >= p) x %= p;
}
y = (y * y); if (y >= p) y %= p;
b /= 2;}
return x;
}*/
public static class Modular {

private int MOD;

Modular(int MOD) {
   this.MOD = MOD;
}

public long add(long a, long b) {
   return (a + b) % MOD;
}

public long sub(long a, long b) {
   return (a - b + MOD) % MOD;
}

public long mul(long a, long b) {
   return (a * b) % MOD;
}

public long div(long a, long b) {
   return mul(a, inverseEuler(b));
}	public long power(long a, long b) {
long x = 1, y = a;
while (b > 0) {
    if (b % 2 == 1) {
        x = (x * y);if (x >= MOD) x %= MOD;
    }
    y = (y * y);
    if (y >= MOD) y %= MOD;
    b /= 2;}
return x;
}

public long inverseEuler(long n) {
return power(n, MOD - 2);
}
}
	static class FastReader {
byte[] buf = new byte[2048];
int index, total;
InputStream in;FastReader(InputStream is) {
in = is;
}	int scan() throws IOException {
if (index >= total) {
index = 0;
total = in.read(buf);
if (total <= 0) { return -1;
}
}
return buf[index++];
}

String next() throws IOException {
int c;
for (c = scan(); c <= 32; c = scan()) ;
StringBuilder sb = new StringBuilder(); for (; c > 32; c = scan()) {
 sb.append((char) c);}
return sb.toString();
}String nextLine() throws IOException {
int c;for (c = scan(); c <= 32; c = scan()) ;
StringBuilder sb = new StringBuilder();
for (; c != 10 && c != 13; c = scan()) {
    sb.append((char) c);
} return sb.toString();
}char nextChar() throws IOException {
int c;
for (c = scan(); c <= 32; c = scan()) ;
return (char) c;
}	int nextInt() throws IOException {
int c, val = 0;
for (c = scan(); c <= 32; c = scan()) ;
boolean neg = c == '-';
if (c == '-' || c == '+') {
    c = scan(); }
for (; c >= '0' && c <= '9'; c = scan()) {
    val = (val << 3) + (val << 1) + (c & 15);
}
return neg ? -val : val;
}long nextLong() throws IOException {
int c;long val = 0;
for (c = scan(); c <= 32; c = scan()) ;
boolean neg = c == '-';
if (c == '-' || c == '+') {
    c = scan();
}
for (; c >= '0' && c <= '9'; c = scan()) {
    val = (val << 3) + (val << 1) + (c & 15);
}
return neg ? -val : val;
}
}

static class FastScanner{
	BufferedReader br;
	StringTokenizer st;
	public FastScanner(){br=new BufferedReader(new InputStreamReader(System.in));}
	String nextToken(){
		while(st==null||!st.hasMoreElements())
			try{st=new StringTokenizer(br.readLine());}catch(Exception e){}
		return st.nextToken();
	}
	int nextInt(){return Integer.parseInt(nextToken());}
	long nextLong(){return Long.parseLong(nextToken());}
	double nextDouble(){return Double.parseDouble(nextToken());}
}
}
