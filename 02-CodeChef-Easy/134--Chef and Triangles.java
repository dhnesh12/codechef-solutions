import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;
 
public class Main {
	
	static class Tuple {
		int a;
		int b;
		int c;
		
		public Tuple(int a, int b, int c) {
			this.a = a;
			this.b = b;
			this.c = c;
		}
		
		@Override
		public int hashCode() {
			int result = (int) (a ^ (a >>> 32));
	        result = 31 * result + (int) (b ^ (b >>> 32));
	        result = 31 * result + (int) (c ^ (c >>> 32));
	        return result;
		}
		
		@Override
		public boolean equals(Object obj) {
			if (obj instanceof Tuple) {
				Tuple t = (Tuple) obj;
				return t.a == a && t.b == b && t.c == c;
			}
			return false;
		}
	}
	
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int r = in.nextInt();
		int sqR = r * r;
		int upperBound = 3 * sqR;
		Set<Tuple> triangles = new HashSet<>();
		
		// a = x + y, b = y + z; c = z + x
		for (int x = 1; x <= upperBound; x++) {
			for (int y = x; y <= upperBound / x; y++) {
				//int a = x + y;
				// let's find z:			
				int dividend = sqR * x + sqR * y;
				int divisor = x * y - sqR;
				if (divisor > 0 && dividend % divisor == 0) {
					int z = dividend / divisor;
					int[] edges = new int[3]; 
					if (z < x) {
						edges [0] = z + x;
						edges [1] = z + y;
						edges [2] = x + y;
					} else if (z > y) {
						edges [0] = x + y;
						edges [1] = x + z;
						edges [2] = y + z;
					} else {
						edges [0] = x + z;
						edges [1] = x + y;
						edges [2] = y + z;
					}
					triangles.add(new Tuple(edges[0], edges[1], edges[2]));
				}
			}
		}
 
		ArrayList<Tuple> list = new ArrayList<>(triangles);
		list.sort(new Comparator<Tuple>() {
 
			@Override
			public int compare(Tuple o1, Tuple o2) {
				if (o1.a == o2.a) {
					if (o1.b == o2.b) {
						return o1.c - o2.c;
					} else {
						return o1.b - o2.b;
					}
				} else {
					return o1.a - o2.a;
				}
			}
		});
		
		System.out.println(list.size());
		for (Tuple t : list) {
			System.out.println("" + t.a + ' ' + t.b + ' ' + t.c);
		}
	}
}   