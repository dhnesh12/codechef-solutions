
import java.io.*;
import java.util.*;
class E
{
    private static long calc(int[] a, int N)
    {
        long ans=0;
        long cb=0,cg=0,b=0,g=0;

        for(int i=0;i<N;i++)
        {
            if(a[i]==0)
            {
                cg++; ans+=b;
            }
            else
            {
                cb++; ans+=g;
            }
            g+=cg; b+=cb;
        }

        return ans;
    }
    public static void main(String[] args) throws Exception
    {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));

        int i,N;

        int T=Integer.parseInt(br.readLine().trim());
        StringBuilder sb=new StringBuilder();

        while (T-->0)
        {
            char[] str=br.readLine().trim().toCharArray();
            int b=0; N=str.length;

            for(char c:str) if(c=='b') b++;
            b=Math.min(b,N-b); int g=N-b;

            int[] a=new int[N];

            int tmp=g-b;
            int k=(tmp+1)/2;

            while (b>0&&g>0)
            {
                b--; g--;
                a[k++]=1; a[k++]=0;
            }
            while (b-->0) a[k++]=1;

            sb.append(calc(a,N)).append("\n");
        }
        System.out.println(sb);
    }
}