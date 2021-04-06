import java.math.BigInteger;
import java.util.*;
import java.io.*;

public class Main
{
	static BigInteger RA[] = new BigInteger[160];
	static BigInteger RB[] = new BigInteger[160];
	static void add(int i,BigInteger x,BigInteger y){
		BigInteger g = RB[i].gcd(y);
		y = y.divide(g);
		RA[i] = RA[i].multiply(y).add(x.multiply(RB[i].divide(g)));
		RB[i] = RB[i].multiply(y);
	}
        public static void main(String[] args) throws IOException {
		Scanner cin = new Scanner(System.in);
		int tCase = cin.nextInt();
		int cN = 2;
		BigInteger rm[] = new BigInteger[160];
		RA[1] = BigInteger.ZERO;
		RB[1] = BigInteger.ONE;
		RA[2] = BigInteger.valueOf(2);
		RB[2] = BigInteger.ONE;
		rm[1] = rm[0] = BigInteger.ONE;
		rm[2] = BigInteger.valueOf(2);
		for (int t = 1;t <= tCase;t++){
			int n = cin.nextInt();
			if (n > cN){
				for (int i = cN+1;i <= n;i++){
					rm[i] = rm[i-1].multiply(BigInteger.valueOf(i));
					RA[i] = BigInteger.ZERO;
					RB[i] = BigInteger.ONE;
					BigInteger sp = BigInteger.ONE;
					BigInteger cd;
					for (int j = 2;j < i;j++){
						cd = BigInteger.valueOf((i-j+1)*(j*(j-3)+3)).multiply(rm[j-2]);
						add(i,RA[j].multiply(cd),RB[j]);
						sp = sp.add(cd);
					}
					RA[i] = RA[i].add(RB[i].multiply(rm[i]));
					RB[i] = RB[i].multiply(sp);
					cd = RA[i].gcd(RB[i]);
					RA[i] = RA[i].divide(cd);
					RB[i] = RB[i].divide(cd);
				}
				cN = n;
			}
			System.out.print(RA[n]);
			if (RB[n].compareTo(BigInteger.ONE) != 0)
				System.out.print("/"+RB[n]);
			System.out.println();
		}
        }
}