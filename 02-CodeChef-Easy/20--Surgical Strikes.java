import java.util.Scanner;
 class Codechef {
	
	  public static void main(String[] args){
		  Scanner Reader  = new Scanner(System.in);
				int N = Reader.nextInt() ;
		int M = Reader.nextInt();
		int T = Reader.nextInt();
		Pair[] s = new Pair[N];
		for(int i=0;i<N;i++){
		    s[i] = new Pair(Reader.nextInt(), Reader.nextInt(), Reader.nextInt());
		}
		Pair[] t = new Pair[M];
		for(int i=0;i<M;i++){
		    t[i] = new Pair(Reader.nextInt(), Reader.nextInt(), Reader.nextInt());
		}
		Pair main = new Pair(Reader.nextInt(), Reader.nextInt());
		Reader.close();
		
		int[][] arr = new int[N][M];
		int[] col = new int[M];
		int[] row = new int[N];
		
		for(int i=0;i<N;i++) {
			for(int j=0; j<M;j++) {
				int mdist=Math.abs(s[i].x-t[j].x)+ Math.abs(s[i].y - t[j].y);
				mdist=primeFactors(mdist, s[i].id);
				int mdist2=Math.abs(main.x-t[j].x)+ Math.abs(main.y - t[j].y);
				mdist2=primeFactors(mdist2, t[j].id);
				int dist=T-mdist-mdist2;
				if(dist>=0) {
					arr[i][j]=1;
					col[j]++;
					row[i]++;
					//System.out.println(i+" "+row[i]+" "+j+" "+col[j]);
				}
			}
		}
		int count=0;
		for(int i=0;i<N;i++) {
			int least=Integer.MAX_VALUE;
			int x=-1;
			int y=-1;
			for(int j=0; j<M;j++) {
				if(i!=0 && arr[i-1][j]==-1) {
		            arr[i][j] = -1;
		            continue;
		        }
				if(arr[i][j]==1) {
					int sum=row[i]+col[j]-1;
					if(least>sum) {
					//System.out.println("Sum of "+row[i]+" "+col[j]+"is : "+sum);
						least=sum;
						x=i;
						y=j;
					}
				}
			}
			if(x!=-1 && y!=-1) {
				count++;
				arr[x][y]=-1;
			}
		}
		System.out.println(count);
		
	}
	
	public static int primeFactors(int n, int id) { 
	    while (n%2==0) 
        { 
            if(2>id) return 2; 
            n /= 2; 
        }
        
        for (int i = 3; i <= Math.sqrt(n); i+=2) { 
            while (n%i == 0) { 
                if(i>id) return i;
                n /= i; 
            } 
        } 
  
        if (n > 2 && n > id) 
            return n; 
        else 
            return id;
    } 
	
	public static class Pair{
		int x;
		int y;
		int id;
		Pair(int x, int y, int id) {
			this.x=x;
			this.y=y;
			this.id=id;
		}
		Pair(int x, int y){
			this.x=x;
			this.y=y;
		}
	}
	
}
