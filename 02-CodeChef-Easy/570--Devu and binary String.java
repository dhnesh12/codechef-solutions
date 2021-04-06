/* package codechef; // don't place package name! */

import java.io.*;
import java.util.*;
class devstr
{
    public static void main(String args[])throws IOException
    {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        int t=Integer.parseInt(br.readLine());
        for(int z=1;z<=t;z++)
        {
            String s[]=br.readLine().trim().split(" ");
            int n=Integer.parseInt(s[0]);
            int k=Integer.parseInt(s[1]);
            String str=br.readLine().trim();
            if(k==1)
            {
                StringBuffer sb1=new StringBuffer("");
                StringBuffer sb2=new StringBuffer("");
                int c1=0,c2=0;
                for(int i=0;i<n;i++)
                {
                    if(i%2==0)
                 
                    {
                        sb1.append('0');
                        sb2.append('1');
                    }
                    else
                    {
                        sb1.append('1');
                        sb2.append('0');
                    }
                    
                } String s1=sb1.toString(),s2=sb2.toString();
                for(int i=0;i<n;i++)
                {
                    if(s1.charAt(i)!=str.charAt(i))
                    c1++;
                    if(s2.charAt(i)!=str.charAt(i))
                    c2++;
                }
                if(c1<c2)
                {
                    System.out.println(c1);
                    System.out.println(sb1);
                }
                else
                {
                    System.out.println(c2);
                    System.out.println(sb2);
                }
            }
            else
            {
                char ch[]=str.toCharArray();
                int st=-1,cou=1,tot=0;
                for(int i=1;i<n;i++)
                {
                    if(ch[i]==ch[i-1])
                    {
                        cou++;
                    }
                    else
                    {
                        if(cou>k)
                        { while(true)
                            {
                                if(cou<=k)
                                {
                                    break;
                                }
                                else
                                {
                                   if(cou==(k+1))
                                   {
                                       if(ch[st+k]=='0')
                                       {
                                           ch[st+k]='1';
                                        }
                                        else
                                        {
                                            ch[st+k]='0';
                                        }
                                        tot++;
                                        break;
                                    }
                                    else
                                    {
                                        if(ch[st+k+1]=='0')
                                       {
                                           ch[st+k+1]='1';
                                        }
                                        else
                                        {
                                            ch[st+k+1]='0';
                                        }
                                        tot++;
                                        cou=cou-(k+1);
                                        st+=k+1;}
                                }
                            }
                        }
                        st=i-1;
                        cou=1;
                    }
                }
                if(cou>k)
                {
                    while((st+k+1)<n)
                    {
                        if(ch[st+k+1]=='0')
                        {
                            ch[st+k+1]='1';
                            st+=k+1;
                            tot++;
                        }
                        else
                        {
                            ch[st+k+1]='0';
                            st+=k+1;
                            tot++;
                        }
                    }
                }
                System.out.println(tot);
                for(int i=0;i<n;i++)
                {
                    System.out.print(ch[i]);
                }
                System.out.println();
            }
        }
    }
}
