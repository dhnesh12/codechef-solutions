import java.util.*;
import java.math.BigDecimal;
import java.math.BigInteger;
class NEWSCH
{
    public static void main(String args[])
    {
        Scanner sc= new Scanner(System.in);
        int t=sc.nextInt();
        while(t-->0)
        {
            int n=sc.nextInt();
            BigInteger l=BigInteger.valueOf(n);
            BigInteger m=new BigInteger("3");
            BigInteger a=new BigInteger("3");
            BigInteger c= new BigInteger("1");
            BigInteger e=new BigInteger("1000000007");
           
           
            m=m.modPow(l,e);
            
            if(n%2==0)
            m=m.add(a);
            else
            m=m.subtract(a);
            System.out.println(m);
            
            /*BigDecimal s=new BigDecimal("12");
             BigDecimal a=new BigDecimal("0.75");
            BigDecimal b=new BigDecimal("4");
            BigDecimal c=new BigDecimal("-3");
            
            BigDecimal o=new BigDecimal("
            
            if(n==1)
                System.out.println("4");
            else if(n==2)
                System.out.println("12");
                
            else
            {
            c=c.pow(n-2);
            c=c.multiply(b);
            a=a.d(c);
            BigDecimal m=new BigDecimal("3")
            m=m.pow(n-2);
            s=s.multiply(m);
            BigInteger e=BigInteger.valueOf((int)Math.pow(10,9));
            BigInteger f= new BigInteger("7");
            BigInteger g=s.toBigInteger();
            e=e.add(f);
            g=g.mod(e);
            System.out.println(g);*/
        
        }
    }
}
            
                
            