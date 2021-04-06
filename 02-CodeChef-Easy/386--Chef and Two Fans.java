import java.util.Scanner;

class ChefFans {

	public static void main(String ar[]) {
		Scanner getData = new Scanner(System.in);
		int cases = getData.nextInt();
		for(int i = 0;i<cases;i++) {
			long sp1 = getData.nextLong();
			long sp2 = getData.nextLong();
			long temp = gcd(Math.abs(sp1),Math.abs(sp2));
			System.out.println(Math.abs(sp1-sp2)/temp);
		}
		
	}

	private static long gcd(long x, long y) {
		if(x == 0)
			return y;
		return gcd(y%x,x);
	}
}