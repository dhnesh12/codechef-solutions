/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;
import java.math.BigInteger;
import java.text.DecimalFormat;
 
class Main
{  
/*	static class pair{
		long area;int idx;
		pair(){}
		pair(long a,int b)
		{
		 area=a;
		 idx=b;
		}
	 }  

	 private static class Book {
	        int exercises;
	        String name;
	        int index;
	        public Book(){
	            this.index=0;
	        }
	    }*/
	static class box implements Comparable<box>
	{
	
	int balls;
	int color;
	public box(int balls, int color)
	{	this.balls = balls;
	this.color = color;
	
}
@Override
public int compareTo (box ob)
{	
	 return(Integer.compare(this.balls, ob.balls));
	     
}
}
static class Color implements Comparable {
    Integer color;
    Integer value;

    public Color(Integer color, Integer value) {
        this.color = color;
        this.value = value;
    }

    @Override
    public int compareTo(Object o) {
        return Integer.compare(this.value, ((Color)o).value);
    }
}
/*	static class Pair
{
 int a,b;
 Pair(int a,int b)
 {this.a = a;this.b=b;}
}*/
static	class PairComparator implements Comparator<Pair>{
	public int compare(Pair p1, Pair p2) {
		return Integer.compare(p2.x, p1.x);}
}
static		class Pair {
int i,j,x;
public Pair(int i,int j, int x){
	this.i= i;
	this.j=j;
	this.x=x;
}

}
static class Triplet
{
int x[]=new int[3];
Triplet(int a,int b,int c)
{
 this.x[0]=a;
 this.x[1] =b;
 this.x[2] = c;
}
}
static class Rec
{
String s;
int pri;
}static class Point  
{ 
int x; 
int y; 

public Point(int x, int y) 
{ 
this.x = x; 
this.y = y; } 
}; 
static long phi[]=new long[1000001];
static long ans[]=new long[1000001];
static int tree[],sum[];
public static long mod = 1000000007;
public static long [][] tempMatrix;
public static long max = (long) Math.pow(10, 9) + 7;
	static StringBuilder sb = new StringBuilder();
	 public static int rootColor=0;
	 static boolean primes[]=new boolean[10000001];
	public static void main (String[] args) throws java.lang.Exception
	{  
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		FastReader in = new FastReader(System.in);
		Scanner sc = new Scanner(System.in);
		PrintWriter out=new PrintWriter(System.out);
		
	//	HashMap<Integer, Integer> h = new HashMap<Integer, Integer>();
	   // HashSet<Integer> s = new HashSet<Integer>();
	//	HashSet<Character> h2 = new HashSet<Character>();
		//long t= in.nextLong();
	//	long t = in.nextLong();
		//DecimalFormat df = new DecimalFormat("#,###,##0.000000");
		
		long mod = 1000000007;

         int t=Integer.parseInt(br.readLine());
		 while(t-->0)
		{
		    	
		int n=Integer.parseInt(br.readLine());
            int x[]=new int[n+3];
            int y[]=new int[n+3];
            for(int i=1;i<=n;i++)
            {
                String s[]=br.readLine().trim().split(" ");
                x[i+1]=Integer.parseInt(s[0]);
                y[i+1]=Integer.parseInt(s[1]);
            }
            String s[]=br.readLine().trim().split(" ");
            x[1]=Integer.parseInt(s[0]);
            y[1]=Integer.parseInt(s[1]);
            s=br.readLine().trim().split(" ");
            x[n+2]=Integer.parseInt(s[0]);
            y[n+2]=Integer.parseInt(s[1]);
			long cost[][]=new long[n+3][n+3];
            for(int i=1;i<n+3;i++)
            {
                for(int j=1;j<n+3;j++)
                {
                    cost[i][j]=((x[i]-x[j])*(x[i]-x[j]))+((y[i]-y[j])*(y[i]-y[j]));
                }
            }
            long dist[]=new long[n+3];
            boolean vis[]=new boolean[n+3];
            Arrays.fill(dist,30000000000L);
           
            dist[1]=0;
            for(int i=1;i<(n+2);i++)
            {
                int ind=-1;long min=Long.MAX_VALUE/2;
                for(int j=1;j<(n+3);j++)
                {
                    if(dist[j]<min && !vis[j])
                    {
                        min=dist[j];
                        ind=j;
                    }
                }
                vis[ind]=true;
               
                for(int j=1;j<n+3;j++)
                {
                    if(!vis[j] && cost[ind][j]!=0 && dist[j]!=3000000000L)
                    {
                        if(dist[ind]+cost[ind][j] < dist[j])
                        {
                            dist[j]=dist[ind]+cost[ind][j];
                           
                        }
                    }
		        		}
		        		
		        }
		        System.out.println(dist[n+2]);
				 }

}

	  
 static long power(long x, long y, long p) 
    { 
        
        long res = 1;      
         
    
        x = x % p;  
  
       if (x == 0) return 0;     
  
        while (y > 0) 
        { 
           
            if((y & 1)==1) 
                res = (res * x) % p; 
       
            y = y >> 1;  
            x = (x * x) % p;  
        }   return res; 
    } static int gcd(int n, int m) {
	    if(m == 0) return n;
	    return gcd(m, n % m);
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
	    StringBuilder sb = new StringBuilder();
	    for (; c > 32; c = scan()) {
	        sb.append((char) c);
	    }
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
	    int c;
	    long val = 0;
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
}