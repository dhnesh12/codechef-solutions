import java.io.*;
import java.util.*;
import static java.lang.System.out;

class PostTree
{
    public static ArrayList<ArrayList<Integer>> adj;
    public static final int K=17;
    public static long[][] minCost;
    public static int[] p, par[]; 
    public static long[] A, depth, dp;

    public static void main(String args[]) throws IOException
    {
        Input inp=new Input(System.in);
        int n=inp.i();

        depth=new long[n+1];
        dp=new long[n+1];
        A=new long[n+1];
        p=new int[n+1];
        par=new int[n+1][K];
        minCost=new long[n+1][K];
        adj=new ArrayList<ArrayList<Integer>>(n+1);
        
        for(int i=0;i<=n;i++)
        {
            adj.add(new ArrayList<Integer>());
        }

        for(int[] i : par)
        {
            Arrays.fill(i, -1);
        }

        p[1]=1;
        for(int i=2;i<=n;i++)
        {
            int j=inp.i();
            adj.get(j).add(i);
            p[i]=j;
        }
        adj.get(0).add(1);
        
        for(int i=1;i<=n;i++)
        {
            A[i]=inp.i();
        }
        
        for(int i=1;i<=n;i++)
        {
            par[i][0]=p[i];
            minCost[i][0]=Math.min(A[i], A[p[i]]);
        }

        for(int k=1;k<K;k++)
        {
            for(int i=1;i<=n;i++) if(par[i][k-1] != -1)
            {
                par[i][k]=par[par[i][k-1]][k-1];
                minCost[i][k]=Math.min(minCost[i][k-1], minCost[par[i][k-1]][k-1]);
            }
        }

        depth[1]=1;
        p[1]=0;
        dfs(1);

        for(int i=1;i<=n;i++)
        {
            out.print(dp[i]+" ");
        }
        out.println();
    }

    public static void dfs(int i)
    {
        int j=i;
        for(int k=K-1;k>=0;k--) if(par[j][k] != -1 && minCost[j][k] >= A[i])
        {
            j=par[j][k];
        }

        dp[i]=dp[p[j]] + (depth[i] - depth[p[j]]) * A[i];

        for(int to : adj.get(i))
        {
            depth[to]=depth[i]+1;
            dfs(to);
        }
    }

    public static class Input
    {
        private StreamTokenizer stok;

        Input(InputStream inputStream)
        {
            stok=new StreamTokenizer(new BufferedReader(new InputStreamReader(inputStream)));
        }

        public int i() throws IOException
        {
            stok.nextToken();
            return (int)stok.nval;
        }

        public String s() throws IOException
        {
            stok.nextToken();
            return stok.sval;
        }
    }
}