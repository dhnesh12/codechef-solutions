import java.io.* ;
import java.math.BigInteger;
import java.util.* ;

class Codeshefcode {
	final static int r = 1000000007 ;
	static FileInputStream in=null ;
	static FileOutputStream out=null ;
	static FasterScanner input = new FasterScanner() ;
	static FasterScanner infile ;
	static PrintWriter outfile  ;
	static PrintWriter output = new PrintWriter(System.out) ;
	public static void main(String[] args) throws IOException{
        int C[] = new int[200000] ;
        for(int i=0 ; i<200000 ; i++){
        	C[i]=0 ;
        }
        C[100000]=1 ; 
        long ans[] = new long[200000] ;
        int sum4=0 ;
        int sum7=0 ;
        for(int i=1 ; i<200000 ; i++){
        	sum4+=dig4(i) ;
        	sum7+=dig7(i) ;
        	ans[i]=ans[i-1]+C[sum4-sum7+100000] ;
        	C[sum4-sum7+100000]++ ;
        	
        }
        int T = input.nextInt() ;
        for(int i=0 ; i<T ; i++){
        	output.println(ans[input.nextInt()]) ;
        }
		Finish() ;
	}
	
	static int dig4(int i){
		int count=0 ;
		int j ;
		while(i!=0){
			j=i%10 ;
			i/=10 ;
			if(j==4)
				count++ ;
		}
		return count ;
	}
	static int dig7(int i){
		int count=0 ;
		int j ;
		while(i!=0){
			j=i%10 ;
			i/=10 ;
			if(j==7)
				count++ ;
		}
		return count ;
	}
	
	static void Start() throws IOException{
		out = new FileOutputStream("C:\\Users\\temporary\\Desktop\\output.txt") ; 
        outfile = new PrintWriter(out) ;
        String s = "C:\\Users\\temporary\\Desktop\\" ;
	    s += input.nextLine() ;
	    s+=".in" ;
	    in = new FileInputStream(s) ;
	    infile = new FasterScanner(in) ;
	}
	
	static void Finish(){
		output.flush();
		output.close();
		
	}
	static void FinishF(){
		outfile.flush();
		outfile.close();
	}
	

	static int RIntf(){
		return infile.nextInt() ;
	}
	static long RLongf(){
		return infile.nextLong() ;
	}
	static String RStringf(){
		return infile.nextString() ;
	}
	static void printf(Object i){
		outfile.print(i) ;
	}
	static void printlnf(Object i){
		outfile.println(i) ;
	}
		
}	


class ModOp{
	static private int k ;
	final static private int r=k ;
	ModOp(int i){
		k=i ;
	}
	static long D(long a , long b){
		return (a*ModInverse(b))%r ;
	}
	static long m(long a , long b){
		return (a*b)%r ;
	}
	static long ModInverse(long a ){
	return FastPowr(a,r-2) ;	
		
	}
	static long FastPowr(long a , long b){
		if(b==0)
		    return 1 ;
		if(b==1)
			return a ;
		long halfpow = FastPowr(a,b/2) ;
		if(b%2==0)
			return (halfpow*halfpow)%r ;
		else
			return (((halfpow*halfpow)%r)*a)%r ;
		
	}
	
}


class pair<E,F>{
	private E x  ;
	private F y  ;
	public void put(E a , F b){
		x=a ;
		y=b ;
	}
	public E getx(){
		return x ;
	}
	public F gety(){
		return y ;
	}
	pair(E a ,F b){
		x=a ;
		y=b ;
	}
}

class Triple{
	public int x ;
	public int y ;
	public int z ;
	Triple(int a , int b , int c){
		x=a ;
		y=b ;
		z=c ;
	}	
}


class FasterScanner {

    private InputStream mIs;
    private byte[] buf = new byte[1024];
    private int curChar;
    private int numChars;

    public FasterScanner() {
        this(System.in);
    }

    public FasterScanner(InputStream is) {
        mIs = is;
    }

    public int read() {
        if (numChars == -1) {
            throw new InputMismatchException();
    
    }
        if (curChar >= numChars) {
            curChar = 0;
            try {
                numChars = mIs.read(buf);
            } catch (IOException e) {
                throw new InputMismatchException();
            }
            if (numChars <= 0) {
                return -1;
            }
        }
        return buf[curChar++];
    }

    public String nextLine() {
        int c = read();
        while (isSpaceChar(c)) {
            c = read();
        }
        StringBuilder res = new StringBuilder();
        do {
            res.appendCodePoint(c);
            c = read();
        } while (!isEndOfLine(c));
        return res.toString();
    }

    public String nextString() {
        int c = read();
        while (isSpaceChar(c)) {
            c = read();
        }
        StringBuilder res = new StringBuilder();
        do {
            res.appendCodePoint(c);
            c = read();
        } while (!isSpaceChar(c));
        return res.toString();
    }

    public long nextLong() {
        int c = read();
        while (isSpaceChar(c)) {
            c = read();
        }
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = read();
        }
        long res = 0;
        do {
            if (c < '0' || c > '9') {
                throw new InputMismatchException();
            }
            res *= 10;
            res += c - '0';
            c = read();
        } while (!isSpaceChar(c));
        return res * sgn;
    }

    public int nextInt() {
        int c = read();
        while (isSpaceChar(c)) {
            c = read();
        }
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = read();
        }
        int res = 0;
        do {
            if (c < '0' || c > '9') {
                throw new InputMismatchException();
            }
            res *= 10;
            res += c - '0';
            c = read();
        } while (!isSpaceChar(c));
        return res * sgn;
    }

    public boolean isSpaceChar(int c) {
        return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
    }

    public boolean isEndOfLine(int c) {
        return c == '\n' || c == '\r' || c == -1;
    }

}
