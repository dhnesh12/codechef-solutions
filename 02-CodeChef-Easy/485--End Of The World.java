/* package codechef; // don't place package name! */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

class CHEFHACK 
{
    static class Scanner
    {
        BufferedReader br;
        StringTokenizer tk=new StringTokenizer("");
        public Scanner(InputStream is) 
        {
            br=new BufferedReader(new InputStreamReader(is));
        }
        public int nextInt() throws IOException
        {
            if(tk.hasMoreTokens())
                return Integer.parseInt(tk.nextToken());
            tk=new StringTokenizer(br.readLine());
            return Integer.parseInt(tk.nextToken());
        }
        public long nextLong() throws IOException
        {
            if(tk.hasMoreTokens())
                return Long.parseLong(tk.nextToken());
            tk=new StringTokenizer(br.readLine());
            return Long.parseLong(tk.nextToken());
        }
        public String next() throws IOException
        {
            if(tk.hasMoreTokens())return (tk.nextToken());
            tk=new StringTokenizer(br.readLine());
            return (tk.nextToken());
        }
        public String nextLine() throws IOException
        {
            tk=new StringTokenizer("");
            return br.readLine();
        }
        public double nextDouble() throws IOException
        {
            if(tk.hasMoreTokens())
                return Double.parseDouble(tk.nextToken());
            tk=new StringTokenizer(br.readLine());
            return Double.parseDouble(tk.nextToken());
        }
        public char nextChar() throws IOException
        {
            if(tk.hasMoreTokens())
                return (tk.nextToken().charAt(0));
            tk=new StringTokenizer(br.readLine());
            return (tk.nextToken().charAt(0));
        }
    
    
    
    }
    static void dfs(int i,int j,int n,int a[][],int p[],int w)
    {
        if(i<0||i>=n||j<0||j>=n||a[i][j]==-1||p[a[i][j]]>0||a[i][j]%2!=w)
            return;
        a[i][j]=-1;
        dfs(i-1,j,n,a,p,w);
        dfs(i+1,j,n,a,p,w);
        dfs(i,j-1,n,a,p,w); dfs(i,j+1,n,a,p,w);
    }
    public static void main(String args[]) throws IOException
    {
        Scanner in=new Scanner(System.in);
        boolean prime[]=new boolean[10000000];
        int p[]=new int[10000000];
        int k=1;
        Arrays.fill(prime, true);
        prime[0]=false;
        prime[1]=false;
        
        for(int i=2;i<10000000;i++)
        {
            if(!prime[i])
                continue;
            p[i]=k;
            k++;
            for(long j=(long)i*i;j<10000000;j+=i)
                prime[(int)j]=false;
            
        }
        
        
        int t=in.nextInt();
        while(t--!=0)
        {
            int n=in.nextInt();
            int a[][]=new int[n][n];
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                    a[i][j]=in.nextInt();
            long ans=0;
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++){
                    if(a[i][j]==-1)
                        continue;
                    if(p[a[i][j]]>0)
                    {
                        ans+=(p[a[i][j]]-1);
                        
                    }
                    else
                    {
                        if(a[i][j]%2==0)
                            ans+=(a[i][j]/2);
                        else
                            ans+=(a[i][j]+3)/2;
                        dfs(i,j,n,a,p,a[i][j]%2);
                        
                    }
                }
            System.out.println(ans);
        }
    }

}
