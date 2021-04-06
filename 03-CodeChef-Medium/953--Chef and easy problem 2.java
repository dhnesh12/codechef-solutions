

import java.util.*;

class Gcd {
	
	public static List<Integer> primes = new ArrayList<>();
	static {
		int max=1001;
		boolean sieve[]=new boolean[max];
		for(int i=2;i<=Math.sqrt(max);i++) {
			if(sieve[i]) continue;
			for(int j=i*i;j<max;j+=i) sieve[j]=true;
		}
		
		for(int i=2;i<max;i++) if(!sieve[i]) primes.add(i);
		//System.out.println(primes.size());
		
	}
	

	public static void main(String[] args){
		Scanner sc=new Scanner(System.in);
		int t=sc.nextInt();
		while(t-->0) {
			int n=sc.nextInt();
			int a[]=new int[n];
			for(int i=0;i<n;i++) a[i]=sc.nextInt();
			System.out.println(getSteps(a, n));
			
		}
		sc.close();
	}

	private static int getSteps(int[] a, int n) {
		int count=0;
		
		for(int i=0;i<primes.size();i++) {
			int div = primes.get(i);
			int max = 0;
			for(int j=0;j<n;j++) {
				if(a[j]%div!=0 || a[j]<div) continue;
				int exp=0;
				while(a[j]%div==0) {
					a[j]/=div;
					exp++;
				}
				max=Math.max(exp, max);
			}
			count+=max;
			max=0;
		}
		
		for(int i=0;i<n;i++) if(a[i]>1) count++;
		
		return count;
	}
}

