import java.io.*;
import java.math.BigInteger;
class Sol{
public static void main(String args[])throws IOException
{
BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
int t=Integer.parseInt(br.readLine());
BigInteger b1=new BigInteger("1000000007");
BigInteger b2=new BigInteger("1000000009");
while(t-->0)
{
BigInteger n=new BigInteger(br.readLine());
if(n.equals(new BigInteger("1"))){
System.out.println(0+" "+0);}
else if(n.equals(new BigInteger("2"))){
System.out.println(1+" "+1);
}
else{
n=n.subtract(new BigInteger("2"));
BigInteger p=n.add(new BigInteger("2")).multiply(n.add(new BigInteger("1")));
BigInteger q=new BigInteger("2").multiply(new BigInteger("2").multiply(n).add(new BigInteger("1")));
BigInteger d=p.gcd(q);
p.divide(d);
q.divide(d);
BigInteger a1=(p.mod(b1).multiply(q.modInverse(b1).mod(b1))).mod(b1); 
BigInteger a2=(p.mod(b2).multiply(q.modInverse(b2).mod(b2))).mod(b2);
System.out.println(a1+" "+a2);
}}}}