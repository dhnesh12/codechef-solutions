import java.io.*;
import java.util.*;


public class Main {
  static List<int[]> hands;
  static boolean[] lastHands;
  static boolean[][] cross;
  static int[][] sums;
  static int N;
  static int totalSum = 18*19/2;

  static int compare(int[] a, int[] b){
    for(int i=0; i<3; ++i){
      int ret = Integer.compare(a[i], b[i]);
      if(ret != 0) return ret;
    }
    return 0;
  }
  
  static void init(){
    List<Integer> ss = new ArrayList<>();
    List<int[]> hands0 = new ArrayList<>();
    for(int i=1; i<=18; ++i)
      for(int j=i+1; j<=18; ++j)
        for(int k=j+1; k<=18; ++k){
          ss.add(i+j+k);
          hands0.add(new int[]{i,j,k});
        }
    N = hands0.size();
    hands = hands0;
    int[] count = new int[16+17+18+1];
//    trace(0,count.length);
    for(int i : ss){
      count[i]++;
    }
    
    sums = new int[count.length][];
    for(int i=0; i<count.length; ++i){
      sums[i] = new int[count[i]];
    }
    Arrays.fill(count, 0);
    for(int i=0; i<N; ++i){
      int s = ss.get(i);
      sums[s][count[s]++]=i;
    }

    cross = new boolean[N][N];
    lastHands = new boolean[N];
    for(int i=0; i<N; ++i){
      int[] x = hands.get(i);
//      trace(0,i,Arrays.toString(x));
      if(x[0]<=6 && x[1]>6 && x[1]<=12 && x[2]>12){
        lastHands[i] = true;
      }
      cross[i][i] = true;
      for(int j=i+1; j<N; ++j){
        int[] y = hands.get(j);
        boolean b = (y[0] != x[0]) && (y[1] != x[0]) && (y[2] != x[0]) &&
            (y[0] != x[1]) && (y[1] != x[1]) && (y[2] != x[1])&&
            (y[0] != x[2]) && (y[1] != x[2]) && (y[2] != x[2]);
        cross[i][j] = cross[j][i] = !b;
      }
    }
//    trace(0,Arrays.toString(lastHands));
  }

  
  static int sum(int[] is) {
    int ret = 0;
    for(int i : is) ret += i;
    return ret;
  }


  
  
  static int[] getOrder(int i) {
    int[] ret = new int[4];
    int k=0;
    for(int j=0; j<5; ++j){
      if(j != i) ret[k++] = j;
    }
    return ret;
  }

  
  
  private static boolean isPossible(int[] stack, Arr[] possible, int d, int[] ord) {
    if(d == 6) return true;
    int q = ord[d-2];
    outer:
    for(int j=0; j<possible[q].len; ++j){
      int x = possible[q].x[j];
      for(int i=0; i<d; ++i){
        if(cross[stack[i]][x]) continue outer;
      }
      stack[d] = x;
      if(isPossible(stack,possible,d+1,ord))
        return true;
    }
    return false;
  }

  static class Arr{
    int[] x;
    int len;
    Arr(int[] x) {
      this.x = x;
      len = x.length;
    }

    void rem(int i){
      x[i] = x[len-1];
      len--;
    }
    
  }
  
  
  static int solve(int[][] deal) {
    
    for(int i=0; i<5; ++i){
      Arrays.sort(deal[i]);
    }
    int[] s = new int[6];
    int[] u = new int[5];
    for(int i=0; i<5; ++i){
      s[i] = sum(deal[i]);
      u[i] = Collections.binarySearch(hands, deal[i], (x,y)->compare(x,y));
    }
    s[5] = totalSum - sum(s);
    
    int lasti = 4;
    
    Arr[] possible = new Arr[6];
    for(int i=0; i<5; ++i){
      possible[i] = new Arr(Arrays.copyOf(sums[s[i]], sums[s[i]].length));
    }
    
    for(int i=0;;i=(i+1)%5){
      int[] stack = new int[6];
      int[] ord = getOrder(i);
      boolean b = false;
      
      for(int j=0; j<possible[i].len; ++j){
        int x = possible[i].x[j];
        if(x < 0) break;
        stack[0] = x;
        int n = 0;
        
        for(int y : sums[s[5]]){
          
          if(cross[x][y] || !lastHands[y]) continue;
          stack[1] = y;
          if(isPossible(stack,possible,2, ord)){
            n++;
          }
          if(n == 2)
            break;
        }
        if(n==2) continue; 
        if(u[i] == x) return i+1;
        possible[i].rem(j);
        j--;
        b = true;
      }
      if(b){
        lasti = i;
      }else{
        if(lasti==i) return -1;
      }
    }
  }


  static int[][] randomDeal(){
    Random r = new Random();
    int[][] ret = new int[5][3];
    int[] lastHand = new int[3];
    lastHand[0] = r.nextInt(6);
    lastHand[1] = r.nextInt(6)+6;
    lastHand[2] = r.nextInt(6)+12;
    int[] ii = new int[15];
    int j = 0;
    outer:
      for(int i=0; i<18; ++i){
        for(int x : lastHand)
          if(x == i) continue outer;
        ii[j++]=i;
      }
    for(int i=0; i<15; ++i){
      int k = r.nextInt(15-i)+i;
      int t = ii[k];
      ii[k] = ii[i];
      ii[i] = t;
    }
    for(int i=0; i<15; ++i){
      ret[i/3][i%3] = ii[i]+1;
    }

    for(int i=0; i<5; ++i){
      Arrays.sort(ret[i]);
    }

    return ret;
  }
  
  static int[] getInts(BufferedReader br) throws IOException{
    String[] ss = new String[0];
    while(ss.length==0 || "".equals(ss[0])) ss =  br.readLine().split(" ");
    int[] ret = new int[ss.length];
    for(int i=0; i<ss.length; ++i){
      ret[i] = Integer.parseInt(ss[i]);
    }
    return ret;
  }

  static void goFile(String s) throws NumberFormatException, FileNotFoundException, IOException{
    go(new FileReader(new File(s)));
  }

  static void go() throws NumberFormatException, IOException{
    go(new InputStreamReader(System.in));
  }

  static void go(Reader r) throws IOException{
    BufferedReader br = new BufferedReader(r);
    int n = getInts(br)[0];
    for(int i=0; i<n; ++i){
      int[][] D = readHand(br);
      System.out.println(solve(D));
    }

  }


  private static int[][] readHand(BufferedReader br) throws IOException {
    int[][] ret = new int[5][];
    for(int i = 0; i<5; ++i)
      ret[i] = getInts(br);
    return ret;
  }
  
  
  public static void main(String[] args) throws NumberFormatException, FileNotFoundException, IOException {
    init();
    go();
//  Stopwatch s = new Stopwatch();
//    s.printElapsed();
//    goFile("input/clue.txt");
  }
  
}
