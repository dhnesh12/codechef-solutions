import java.io.*;
import java.util.*;
import java.math.*;
class ceilmenu
{
    public static void main(String args[])throws IOException
    {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        String s=br.readLine().trim();
        if(s.length()==1)
        {
            if(Integer.parseInt(s)%8==0)
            System.out.println("1");
            else
            System.out.println(0);
        }
        else if(s.length()<3)
        {
            int ans=0;
            if(s.charAt(0)=='0' && s.charAt(1)=='0')
            {
                ans+=2;
            }
            else
            {
                int c1=s.charAt(0)-48;
                int c2=s.charAt(1)-48;
                if(s.charAt(0)!='0')
                {
                    if(Integer.parseInt(s)%8==0)
                    {
                        ans++;
                    }
                    if(c1%8==0)
                    ans++;
                    if(c2%8==0)
                    ans++;
                }
                else
                {
                    if(c1%8==0)
                    ans++;
                    if(c2%8==0)
                    ans++;
                }
            }
            System.out.println(ans);
        }
        else
        {
            long ans=0;
            int n=s.length();
            int arr[]=new int[n+1];
            s=" "+s;
            for(int i=1;i<=n;i++)
            {
                if(s.charAt(i)=='0')
                arr[i]=arr[i-1]+1;
                else
                arr[i]=arr[i-1];
            }
            for(int i=1;i<=3;i++)
            {
                for(int j=1;j<=n-i+1;j++)
                {
                    if(i==1)
                    {
                        int ch=s.charAt(j)-48;
                        if(ch%8==0)
                        ans++;
                        //System.out.println(ch+" "+ans);
                    }
                    else if(i==2)
                    {
                        if(s.charAt(j)!='0')
                        {
                            int ch=Integer.parseInt(s.substring(j,j+2));
                            if(ch%8==0)
                            ans++;
                            //System.out.println(ch+" "+ans);
                        }
                    }
                    else
                    {
                        int ch=Integer.parseInt(s.substring(j,j+3));
                        if(s.charAt(j)=='0' && ch%8==0)
                        {
                            ans=ans+j-arr[j];
                        }
                        else
                        {
                            if(s.charAt(j)!='0' && ch%8==0)
                            ans=ans+j-arr[j];
                        }
                        //System.out.println(ch+" "+ans);
                    }
                }
            }
            System.out.println(ans);
        }
    }
}