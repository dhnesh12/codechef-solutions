import java.util.Arrays;
import java.util.Scanner;
class Test
{
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt();
        while(t-- >0)
        {
            int n=sc.nextInt();
            long q=sc.nextLong();
            long p=sc.nextLong();

            long ar[]=new long[n];
            for(int i=0;i<n;i++)
            {
                ar[i]=sc.nextLong();
            }
            Arrays.sort(ar);
            int count=0;
            for(int i=0;i<n;i++)
            {
                q=q-ar[i]%2;
                p=p-ar[i]/2;
                if(p<0){
                    q=q+2*p;
                    p=0;
                }
                if(q>=0 && p>=0){
                    count++;
                }
                if(q<0) {
                    p=p+ar[i]/2;
                    q=q+ar[i]%2;
                }
            }
            System.out.println(count);
        }
    }
}