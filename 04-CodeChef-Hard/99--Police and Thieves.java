import java.util.Scanner;


class ConvexHull_Codechef_POLICE {

	static class Point {
		long x;
		long y;
		char c;
		public Point(long x, long y, char c) {
			this.x = x;
			this.y = y;
			this.c = c;
		}
	}

	public static void main(String[] args) {
		int t, n, m, i, x, y, top;
		Point points[], stack[];
		boolean flag, isCollinear;
		
		Scanner sc = new Scanner(System.in);
		
		t = sc.nextInt();
		while(t-->0) {
			
			n = sc.nextInt(); m = sc.nextInt();
			points = new Point[n+m];
			stack = new Point[n+m]; 
			top = -1;
			for(i = 0; i < n; i++) {
				x = sc.nextInt(); y = sc.nextInt();
				points[i] = new Point(x, y, 'P');
			}
			for(; i < m+n; i++) {
				x = sc.nextInt(); y = sc.nextInt();
				points[i] = new Point(x, y, 'T');
			}
			for(i = 1; i < n+m; i++) {
				if(points[i].y < points[0].y) {
					swap(points, i, 0);
				} else if(points[i].y == points[0].y && points[i].x < points[0].x) {
					swap(points, i, 0);
				}
			}
			mergeSort(points, 1, n+m-1); // sort the points in ASC order of polar angle then in ASC order of x coordinate.
			for(i = m+n-2; i > 0; i--) { // sort the points with highest polar angle in descending order so that they can be covered in Hull.
				if(orientation(points[i+1], points[i], points[0]) != 0) {
					int ll = i+1, rr = m+n-1;
					while(ll < rr) swap(points, ll++, rr--);
					break;
				}
			}
			
			// build convex hull
			stack[++top] = points[0];
			for(i = 1; i < n+m; i++) {
				if(top == 0) { // stack must have atleast 2 elements.(we need this code only when collinear points on convex Hull are not considered.
					stack[++top] = points[i];
				} else if(orientation(stack[top-1], stack[top], points[i]) != 1) {
					stack[++top] = points[i];
				} else {
					top--; i--; // if clockwise then pop. do i-- to check with same point again.
				}
			}
			
			
			// CASE 1. when all the vertex on convex hull are police officers only.
			flag = true;
			for(i = 0; i <= top; i++) {
				if(stack[i].c == 'T') {
					flag = false; break;
				}
			}
			if(flag == true) {
				System.out.println(0); continue;
			}
			
			// CASE 2. when any two straight lines with angle less than 180 can cover all the thieves on one side. we need one extra police officer
			// because  two existing police officers will project the line with angle less than 180.
			isCollinear = true; // is all the points are collinear it is not case of one extra officer.
			for(i = 1; i < top; i++) {
				if(orientation(stack[i-1], stack[i], stack[i+1]) != 0) {
					isCollinear = false; break;
				}
			}
			flag = false;
			if(isCollinear == false) {
				for(i = 0; i <= top; i++) {
					if(stack[i].c == 'P' && stack[(i+top)%(top+1)].c == 'T') {
						int lthief = (i+top) % (top+1), j, rthief;
						for(j = i; stack[(j+1) % (top+1)].c == 'P'; j++);
						j %= top+1;
						rthief = (j+1) % (top+1);
						if(i != j && isConvergent(stack[i], stack[lthief], stack[j], stack[rthief])) {
							flag = true; break;
						}
						if(j < i) break;
						else i = j;
					}
				}
			}
			
			if(flag == true) {
				System.out.println(1); continue;
			}
			
			// CASE 3. when at least one police officer form angle less than 180 in convex hull so we need two extra officer to form triangle.
			flag = false;
			
			if(isCollinear == true) {
				if(stack[0].c == 'P' || stack[top].c == 'P') flag = true;
			} else {
				for(i = 0; i <= top; i++) {
					int l = (i+top) % (top+1), r = (i+1) % (top+1);
					if(stack[i].c == 'P') {
						if(orientation(stack[l], stack[i], stack[r]) != 0) {
							flag = true; break;
						}
					}
				}
			}
			
			if(flag == true) {
				System.out.println(2); continue;
			}
			
			// CASE 4. no police officer is in any corner hence we need 3 police offices to form triangle in worst case.
			System.out.println(3);
		}
	}
	
	
	
	
	
	
	
	
	
	
	static int orientation(Point p, Point q, Point r) { 
		Point pq = new Point(q.x - p.x, q.y - p.y, 'X');
		Point rq = new Point(q.x - r.x, q.y - r.y, 'X');
		long pq_X_rq = pq.x * rq.y - pq.y * rq.x;
		
		if(pq_X_rq == 0) return 0;
		return pq_X_rq > 0 ? 1 : 2;
		// 0 means point 'r' is on/along the line PQ (p,q,r are collinear )
		// 1 means point 'r' is on clockwise direction from line PQ
		// 2 means point 'r' is on anti-clockwise direction from line PQ
	}
	
	static void mergeSort(Point points[], int l, int r) {
		if(l < r) {
			int m = l + r >> 1;
			mergeSort(points, l, m);
			mergeSort(points, m+1, r);
			merge(points, l, m, r);
		}
		
	}
	static void merge(Point points[], int l, int m, int r) {
		int i, j, k;
		Point temp[] = new Point[r-l+1];
		i = l; j = m+1; k = 0;
		while(i <= m && j <= r) temp[k++] = compare(points[0], points[i], points[j]) == true ? points[j++] : points[i++];
		while(i <= m) temp[k++] = points[i++];
		while(j <= r) temp[k++] = points[j++];
		for(i = 0; i < k; i++) points[l+i] = temp[i];
	}
	static boolean compare(Point p, Point a, Point b) { // true means a > b hence swap
		int orientation = orientation(p, a, b);
		if(orientation == 1) return true;
		if(orientation == 0 && distance2(p, b) < distance2(p, a)) return true;
		return false;
	}
	static long distance2(Point a, Point b) {
		return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	}
	static boolean isConvergent(Point a, Point b, Point x, Point y) {
		Point ab = new Point(b.x-a.x, b.y-a.y, 'X');
		Point xy = new Point(y.x-x.x, y.y-x.y, 'X');
		long ab_X_xy = ab.x * xy.y - ab.y * xy.x;
		long ab_DOT_xy = ab.x * xy.x + ab.y * xy.y;
		if(ab_X_xy == 0) {
			if(ab_DOT_xy > 0) return false;
			if(distance2(a, x) < distance2(b, y)) return false;
		}
		if(ab_X_xy >= 0) return true;
		return false;
	}
	static void swap(Point points[], int a, int b) {
		Point t = points[a];
		points[a] = points[b];
		points[b] = t;
	}
}
