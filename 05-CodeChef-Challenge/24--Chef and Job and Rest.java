import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.InputMismatchException;

class ChefandJobandRest {
	
	static void add(int arr[],int rat[],int a,int ra,int f,int l){
		int i;
		for(i=l-1;i>=f;i--){
			if(rat[i]>=ra){
				arr[i+1]=a;rat[i+1]=ra;break;
			}
			arr[i+1]=arr[i];rat[i+1]=rat[i];
		}
		arr[i+1]=a;rat[i+1]=ra;
	}
	
	static int remove(int arr[],int rat[],int l){
		int i,c=0;
		for(i=0;i<l;i++){
			if(arr[i]==-1){
				c++;continue;
			}
			arr[i-c]=arr[i];rat[i-c]=rat[i];arr[i]=-1;rat[i]=-1;
		}
		return l-c;
	}
	
	static void append(int arr[][],int blen[],int maxlen[],int ind, int a){
		if(maxlen[ind]==0){
			arr[ind]=new int[100];arr[ind][blen[ind]++]=a;maxlen[ind]=100;
		}
		else{
			maxlen[ind]*=3;int ary[]=new int[maxlen[ind]];
			for(int i=0;i<blen[ind];i++){
				ary[i]=arr[ind][i];
			}
			ary[blen[ind]++]=a;arr[ind]=ary;
		}
	}
	
	
	
	public static void main(String[] args) throws Exception {
		PrintWriter pr = new PrintWriter(System.out, true);
		InputReader in = new InputReader(System.in);
		int n, m, k, i, j, p, c,r, a, b, ind, min, rest[], admin, flen[], blen[], maxlen[], bdarr[][], que1[], ql1, type[], rating[],page[], que2[],f,ql2;
		int que1rat[],que2rat[];
		boolean ch;
		StringBuilder sb;
		n=in.readInt();m=in.readInt();k=in.readInt();
		rest=new int[n];type=new int[m+1];flen=new int[m+1];blen=new int[m+1];rating=new int[m+1];page=new int[m+1];que1=new int[m+1];que2=new int[m+1];que1rat=new int[m+1];que2rat=new int[m+1];
		bdarr=new int[m+1][];maxlen=new int[m+1];
		for(i=0;i<n;i++) rest[i]=in.readInt();
		for(i=1;i<=m;i++){
			type[i]=in.readInt();page[i]=in.readInt();rating[i]=in.readInt();
		}
		while(k-->0){
			a=in.readInt();b=in.readInt();
			if(blen[a]<maxlen[a]) bdarr[a][blen[a]++]=b;else append(bdarr,blen,maxlen,a,b);
			flen[b]++;
		}
		for(i=1,ql1=0,ql2=0,f=0,min=10000000;i<=m;i++){
			if(flen[i]==0){
				if(type[i]==1){
					add(que1,que1rat,i,rating[i]/page[i],0,ql1++);if(page[i]<min) min=page[i];
				}
				else add(que2,que2rat,i,rating[i]/page[i],0,ql2++);
			}
		}
		for(i=0;i<n;i++){
			admin=0;r=rest[i];sb=new StringBuilder("");ch=false;
			for(j=0,c=0;j<ql1;j++){
				ind=que1[j];
				if(ind==-1){
					c++;if(c>8000) ch=true;continue;
				}
				if(page[ind]<=r){
					admin++;sb.append(" "+ind+" "+page[ind]);r-=page[ind];que1[j]=-1;que1rat[j]=-1;c++;
					for(k=0;k<blen[ind];k++){
						p=bdarr[ind][k];
						if(--flen[p]==0){
							if(type[p]==1){
								add(que1,que1rat,p,(int)(((float)rating[p]/page[p])*1000),0,ql1++);if(page[p]<min) min=page[p];
							}
							else add(que2,que2rat,p,(int)(((float)rating[p]/page[p])*1000),f,ql2++);
						}
					}
				}
				if(r<min) break;
			}
			if(ch==true) ql1=remove(que1,que1rat,ql1);
			if(r>0){
				for(j=f;j<ql2;j++){ 												
					if(page[que2[j]]<=r){
						admin++;sb.append(" "+que2[j]+" "+page[que2[j]]);r-=page[que2[j]];f++;
						for(k=0;k<blen[que2[j]];k++){
							p=bdarr[que2[j]][k];
							if(--flen[p]==0){
								if(type[p]==1){
									add(que1,que1rat,p,(int)(((float)rating[p]/page[p])*1000),0,ql1++);if(page[p]<min) min=page[p];
								}
								else add(que2,que2rat,p,(int)(((float)rating[p]/page[p])*1000),f,ql2++);
							}
						}
						if(r==0) break;
					}
					else{
						admin++;sb.append(" "+que2[j]+" "+r);page[que2[j]]-=r;que2rat[j]=(int)(((float)rating[que2[j]]/page[que2[j]])*1000);break;
					}
				}
			}
			if(admin==0) pr.println(0);
			else pr.println(admin+""+sb);
		}
	}
}

class InputReader {
	private InputStream stream;
	private byte[] buf = new byte[102400];
	private int curChar;
	private int numChars;

	public InputReader(InputStream stream) {
		this.stream = stream;
	}

	public final int read() {
		if (numChars == -1)
			throw new InputMismatchException();
		if (curChar >= numChars) {
			curChar = 0;
			try {
				numChars = stream.read(buf);
			} catch (IOException e) {
				throw new InputMismatchException();
			}
			if (numChars <= 0)
				return -1;
		}
		return buf[curChar++];
	}

	public final int readInt() {
		int c = read();
		while (isSpaceChar(c))
			c = read();
		int sgn = 1;
		if (c == '-') {
			sgn = -1;
			c = read();
		}
		int res = 0;
		do {
			if (c < '0' || c > '9')
				throw new InputMismatchException();
			res *= 10;
			res += c - '0';
			c = read();
		} while (!isSpaceChar(c));
		return res * sgn;
	}

	public final long readLong() {
		int c = read();
		while (isSpaceChar(c))
			c = read();
		int sgn = 1;
		if (c == '-') {
			sgn = -1;
			c = read();
		}
		long res = 0;
		do {
			if (c < '0' || c > '9')
				throw new InputMismatchException();
			res *= 10;
			res += c - '0';
			c = read();
		} while (!isSpaceChar(c));
		return res * sgn;
	}

	public final String readString() {
		int c = read();
		while (isSpaceChar(c))
			c = read();
		StringBuilder res = new StringBuilder();
		do {
			res.appendCodePoint(c);
			c = read();
		} while (!isSpaceChar(c));
		return res.toString();
	}

	public final static boolean isSpaceChar(int c) {
		return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
	}

	public final String next() {
		return readString();
	}
}