import java.math.*;
import java.util.*;
import java.io.*;



class main
{
 
    public static void main(String[] args)
    {
        InputReader in = new InputReader(System.in);
        PrintWriter pw = new PrintWriter(System.out);
 
        int test_case =1;
                    StringBuilder sb=new StringBuilder();
        for(int t=0;t<test_case;t++)
        {
            
            int n=in.nextInt();
            int[] a=in.nextIntArray(n);
            
            Set<Integer> set=new HashSet<Integer>();
            
            List<Integer> ls=new ArrayList<Integer>();
            
            for(int i=0;i<n;i++)
            {
                set.add(a[i]);
            }
            
            for(int i=1;i<=n;i++)
            {
              if(!set.contains(i))
              {
                  System.out.print(i+" ");
              }
            }
            
            
            System.out.println();
            
         

           
        }
 
 
 
        pw.flush();
        pw.close();
    }
    
    static int foo(int x,int y,int q)
    {
        if(x<=0&&y<=0)
        {
            return q;
        }
        
        if(x<=0)
        {
            return foo(x,y-q,q);
        }
        if(y<=0)
        {
            return foo(x-q,y,q);
        }
        return foo(x-q,y,q)+foo(x,y-q,q);
    }
    
  static  void pramutation(int i,int[] a,List<int[]> ls,boolean f[])
    {
        if(i==a.length)
        {
            ls.add(a.clone());
            return;
        }
        
        for(int j=1;j<=a.length;j++)
        {
            if(!f[j])
            {
                f[j]=true;
                a[i]=j;
                i++;
                pramutation(i,a,ls,f);
                i--;
                f[j]=false;
            }
        }
        
    }
    
    static int length(long l)
    {
        int c=0;
        while(l>0)
        {
            c++;
            l/=2;
        }
        
        return c;
    }
 
    
    static  Pair dfs(int z,List<List<Integer>> ls)
    { 
        int size=1;
        long max=0;
        Pair temp=new Pair();
        temp.x=max+size;
        temp.y=size;
        for(int i:ls.get(z))
        {
            temp=dfs(i,ls);
            //System.out.println(temp.x+" "+temp.y);
            max=Math.max(max,temp.x);
            size+=temp.y;
            temp.x=max+size;
            temp.y=size;
          //  System.out.println("S"+size);
        }
        return temp;
        
    }
    
    static int CeilIndex(int A[], int l, int r, int key) 
    { 
        while (r - l > 1) { 
            int m = l + (r - l) / 2; 
            if (A[m] <= key) 
                r = m; 
            else
                l = m; 
        } 
  
        return r; 
    } 
    static int LongestIncreasingSubsequenceLength(int A[], int size) 
    { 
        // Add boundary case, when array size is one 
  
        int[] tailTable = new int[size]; 
        int len; // always points empty slot 
  
        tailTable[0] = A[0]; 
        len = 1; 
        for (int i = 1; i < size; i++) { 
            if (A[i] > tailTable[0]) 
 
                tailTable[0] = A[i]; 
  
            else if (A[i] <= tailTable[len - 1]) 
 
                tailTable[len++] = A[i]; 
  
            else
 
                tailTable[CeilIndex(tailTable, -1, len - 1, A[i])] = A[i]; 
        } 
  
        return len; 
    }
    
    static boolean check(int[] a,int x)
    {
        for(int i=0;i<a.length;i++)
        {
            if(a[i]==x)
            {
                return true;
            }
        }
        return false;
    }
 
    
    static int[] next(int arr[], int n) { 
 
        Stack<Integer> S = new Stack<>(); 
  
        int[] next=new int[n];
 
        for (int i = n-1; i >= 0; i--) { 
 
            while (!S.empty() && arr[S.peek()] <= arr[i]) { 
                S.pop(); 
 
            } 
            if (S.empty()) { 
                next[i]=-1;
            } 
            else 
            { 
 
                next[i]=S.peek(); 
            } 
            S.push(i); 
        } 
        return next;
    }
    static int[] back(int arr[], int n) { 
 
        Stack<Integer> S = new Stack<>(); 
  
        int[] back=new int[n];
 
        for (int i = 0; i < n; i++) { 
 
            while (!S.empty() && arr[S.peek()] < arr[i]) { 
                S.pop(); 
            } 
            if (S.empty()) { 
                back[i]=-1;
            } 
            else 
            { 
                back[i]=S.peek(); 
            } 
            S.push(i); 
        } 
        
        return back;
    }
 
    
    
 
    static class InputReader
    {
 
        private final InputStream stream;
        private final byte[] buf = new byte[8192];
        private int curChar, snumChars;
        private SpaceCharFilter filter;
 
        public InputReader(InputStream stream)
        {
            this.stream = stream;
        }
 
        public int snext()
        {
            if (snumChars == -1)
                throw new InputMismatchException();
            if (curChar >= snumChars)
            {
                curChar = 0;
                try
                {
                    snumChars = stream.read(buf);
                }
                catch (IOException e)
                {
                    throw new InputMismatchException();
                }
                if (snumChars <= 0)
                    return -1;
            }
            return buf[curChar++];
        }
 
        public int nextInt()
        {
            int c = snext();
            while (isSpaceChar(c))
            {
                c = snext();
            }
            int sgn = 1;
            if (c == '-')
            {
                sgn = -1;
                c = snext();
            }
            int res = 0;
            do
            {
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = snext();
            } while (!isSpaceChar(c));
            return res * sgn;
        }
 
        public long nextLong()
        {
            int c = snext();
            while (isSpaceChar(c))
            {
                c = snext();
            }
            int sgn = 1;
            if (c == '-')
            {
                sgn = -1;
                c = snext();
            }
            long res = 0;
            do
            {
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = snext();
            } while (!isSpaceChar(c));
            return res * sgn;
        }
 
        public int[] nextIntArray(int n)
        {
            int a[] = new int[n];
            for (int i = 0; i < n; i++)
            {
                a[i] = nextInt();
            }
            return a;
        }
        public long[] nextlongArray(int n)
        {
            long a[] = new long[n];
            for (int i = 0; i < n; i++)
            {
                a[i] = nextLong();
            }
            return a;
        }
 
        public String readString()
        {
            int c = snext();
            while (isSpaceChar(c))
            {
                c = snext();
            }
            StringBuilder res = new StringBuilder();
            do
            {
                res.appendCodePoint(c);
                c = snext();
            } while (!isSpaceChar(c));
            return res.toString();
        }
 
        public String nextLine()
        {
            int c = snext();
            while (isSpaceChar(c))
                c = snext();
            StringBuilder res = new StringBuilder();
            do
            {
                res.appendCodePoint(c);
                c = snext();
            } while (!isEndOfLine(c));
            return res.toString();
        }
 
        public boolean isSpaceChar(int c)
        {
            if (filter != null)
                return filter.isSpaceChar(c);
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }
 
        private boolean isEndOfLine(int c)
        {
            return c == '\n' || c == '\r' || c == -1;
        }
 
        public interface SpaceCharFilter
        {
            public boolean isSpaceChar(int ch);
        }
    }
 
    public static long mod = 1000000007;
    public static int d;
    public static int p;
    public static int q;
 
    public static int[] suffle(int[] a,Random gen)
    {
        int n = a.length;
        for(int i=0;i<n;i++)
        {
            int ind = gen.nextInt(n-i)+i;
            int temp = a[ind];
            a[ind] = a[i];
            a[i] = temp;
        }
        return a;
    }
 
    public static void swap(int a, int b){
        int temp = a;
        a = b;
        b = temp;
    }
 
    public static HashSet<Integer> primeFactorization(int n)
    {
        HashSet<Integer> a =new HashSet<Integer>();
        for(int i=2;i*i<=n;i++)
        {
            while(n%i==0)
            {
                a.add(i);
                n/=i;
            }
        }
        if(n!=1)
            a.add(n);
        return a;
    }
 
    public static void sieve(boolean[] isPrime,int n)
    {
        for(int i=1;i<n;i++)
            isPrime[i] = true;
 
        isPrime[0] = false;
        isPrime[1] = false;
 
        for(int i=2;i*i<n;i++)
        {
            if(isPrime[i] == true)
            {
                for(int j=(2*i);j<n;j+=i)
                    isPrime[j] = false;
            }
        }
    }
 
    public static int GCD(int a,int b)
    {
        if(b==0)
            return a;
        else
            return GCD(b,a%b);
    }
 
    public static long GCD(long a,long b)
    {
        if(b==0)
            return a;
        else
            return GCD(b,a%b);
    }
 
    public static void extendedEuclid(int A,int B)
    {
        if(B==0)
        {
            d = A;
            p = 1 ;
            q = 0;
        }
        else
        {
            extendedEuclid(B, A%B);
            int temp = p;
            p = q;
            q = temp - (A/B)*q;
        }
    }
 
    public static long LCM(long a,long b)
    {
        return (a*b)/GCD(a,b);
    }
 
    public static int LCM(int a,int b)
    {
        return (a*b)/GCD(a,b);
    }
 
    public static int binaryExponentiation(int x,int n)
    {
        int result=1;
        while(n>0)
        {
            if(n % 2 ==1)
                result=result * x;
            x=x*x;
            n=n/2;
        }
        return result;
    }
    int binarySearch(int arr[], int l, int r, int x) 
    { 
        if (r >= l) { 
            int mid = l + (r - l) / 2; 
  
 
            if (arr[mid] == x) 
                return mid; 
  
 
            if (arr[mid] > x) 
                return binarySearch(arr, l, mid - 1, x); 
  
 
            return binarySearch(arr, mid + 1, r, x); 
        } 
  
 
        return -1; 
    } 
  
 
    public static long binaryExponentiation(long x,long n)
    {
        long result=1;
        while(n>0)
        {
            if(n % 2 ==1)
                result=result * x;
            x=x*x;
            n=n/2;
        }
        return result;
    }
 
    public static int modularExponentiation(int x,int n,int M)
    {
        int result=1;
        while(n>0)
        {
            if(n % 2 ==1)
                result=(result * x)%M;
            x=(x*x)%M;
            n=n/2;
        }
        return result;
    }
 
    public static long modularExponentiation(long x,long n,long M)
    {
        long result=1;
        while(n>0)
        {
            if(n % 2 ==1)
                result=(result * x)%M;
            x=(x*x)%M;
            n=n/2;
        }
        return result;
    }
 
    public static int modInverse(int A,int M)
    {
        return modularExponentiation(A,M-2,M);
    }
 
    public static long modInverse(long A,long M)
    {
        return modularExponentiation(A,M-2,M);
    }
 
    public static boolean isPrime(int n)
    {
 
        if (n <= 1)  return false;
        if (n <= 3)  return true;
 
        if (n%2 == 0 || n%3 == 0)
            return false;
 
        for (int i=5; i*i<=n; i=i+6)
        {
            if (n%i == 0 || n%(i+2) == 0)
                return false;
        }
 
        return true;
    }
    static class Pair
    {
        long  x;
        int  y;
    }
 
    static class pair implements Comparable<pair>
    {
        Integer x, y;
        pair(int x,int y)
        {
            this.x=x;
            this.y=y;
        }
 
        public int compareTo(pair o) {
            int result = x.compareTo(o.x);
            if(result==0)
                result = y.compareTo(o.y);
 
            return result;
        }
 
        public String toString()
        {
            return x+" "+y;
        }
 
        public boolean equals(Object o)
        {
            if (o instanceof pair)
            {
                pair p = (pair)o;
                return (Math.abs(p.x-x)==0 && Math.abs(p.y-y)==0);
            }
            return false;
        }
 
        public int hashCode()
        {
            return new Long(x).hashCode()*31 + new Long(y).hashCode();
        }
    }
}