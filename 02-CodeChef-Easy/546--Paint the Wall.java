import java.util.HashSet;
import java.util.Scanner;

class PaintWall {
    public static void main(String[] args) {
        Scanner sc= new Scanner(System.in);
        int t,n,m;
        t=sc.nextInt();
        int[] h;
        int[] c;
        for(int i=0;i<t;i++)
        {
            HashSet<Integer> hs= new HashSet<>();
            n=sc.nextInt();
            m=sc.nextInt();
            h=new int[n];
            c=new int[n];
            for(int j=0;j<n;j++)
            {
                h[j]=sc.nextInt();
            }
            for(int j=0;j<n;j++)
            {
                c[j]=sc.nextInt();
            }
            int maxSoFar=Integer.MIN_VALUE;
            for(int j=n-1;j>=0;j--)
            {
                if(maxSoFar<h[j])
                {
                    maxSoFar= h[j];
                    hs.add(c[j]);
                }
            }
            System.out.println(hs.size());
        }
    }
}
