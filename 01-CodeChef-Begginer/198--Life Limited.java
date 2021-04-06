import java.util.*;
class codechef{
    public static void main(String args[])
    {
        Scanner sc=new Scanner(System.in);
        int t=sc.nextInt();
        while(t-->0)
        {
            String a=sc.next();
            String b=sc.next();
            String c=sc.next();
            if((a.charAt(0)=='l'&&b.charAt(0)=='l'&&b.charAt(1)=='l')||
               (a.charAt(1)=='l'&&b.charAt(1)=='l'&&b.charAt(2)=='l')||
               (b.charAt(0)=='l'&&c.charAt(0)=='l'&&c.charAt(1)=='l')||
               (b.charAt(1)=='l'&&c.charAt(1)=='l'&&c.charAt(2)=='l')  )
               {
                  System.out.println("yes");
               }
            else
            System.out.println("no");
        }
    }
    
}