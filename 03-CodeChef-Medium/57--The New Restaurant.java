import java.io.*;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.*;



class CircleQ2 {
  static void printA(double[][] x){
    for(double[] y : x)
      System.out.println(Arrays.toString(y));
  }
  
  
  static class CumulArray {

    private double[][] arrs;

    public CumulArray(int n) {
      List<double[]> larrs = new ArrayList<>();
      while(n > 0){
        larrs.add(new double[n+1]);
        n >>= 1;
      }
      arrs = larrs.toArray(new double[0][]);
    }

    public double getValue(int k){
      return arrs[0][k];
    }

    public void setValue(int k, double x){
      insert(k,x- arrs[0][k]);
    }

    public void insert(int k, double delta){
      for(double[] z : arrs){
        z[k] += delta;
        k >>= 1;
      }    
    }
    
    // sum of values in [0,k)
    public double getSum(int k){
      double ret = 0;
      for(double[] z : arrs){
        if((k&1) != 0)
          ret += z[k-1];
        k >>= 1;
      }
      return ret;

    }
    
  }
  static int max = 50001;
  
  static final NumberFormat format = new DecimalFormat("#.########");
  static boolean silent = false;
  
  static double getCellFill(int x, int y, int r){
    if(x>y)
      return getCellFill(y,x,r);
    if(x==0 && y == 0 && r == 1){
      if(r == 1)
        return Math.PI/4;
      else
        return 1;
    }
    
    int r2 = r*r;    
    int x2 = x*x;
    int y2 = y*y;
    if(x2+y2>=r2)
      return 0;

    int x12 = (x+1)*(x+1);
    int y12 = (y+1)*(y+1);
    
    if(x12+y12<=r2)
      return 1;

    double x0 = x;
    double x1 = x+1;

    if(x2+ y12 < r2){
      x0 = Math.sqrt(r2-y12);
    }

    if(x12+ y2 > r2){
      x1 = Math.sqrt(r2-y2);
    }

    double ret = x0-x;    
    double q = Math.sqrt(r2-x0*x0);
    ret -= 0.5*(x0*q+ r2*Math.atan2(x0,q));
    q = Math.sqrt(r2-x1*x1);
    ret += 0.5*(x1*q+ r2*Math.atan2(x1,q));
    ret -= (x1-x0)*y;
    return ret;
    
  }

  static double[][] getLocalGrid(int r0){
    double[][] ret = new double[2*r0][2*r0];
    int r = r0;
    for(int x=0; x<r0; ++x)
      for(int y=x; y<r0; ++y){
        double v = getCellFill(x,y,r0);
        ret[r+x][r+y] = v;
        ret[r+y][r+x] = v;
        ret[r-x-1][r+y] = v;
        ret[r-y-1][r+x] = v;
        ret[r-x-1][r-y-1] = v;
        ret[r-y-1][r-x-1] = v;
        ret[r+x][r-y-1] = v;
        ret[r+y][r-x-1] = v;
      }
    return ret;
  }

  
  static class Point implements Comparable<Point>{
    int x,y,r;
    public Point(int x, int y, int r) {
      this.x = x;
      this.y = y;
      this.r = r;
    }
    
    public Point(int[] z){
      this(z[0],z[1],z[2]);
    }
    
    public int minX(){
      return x-r;
    }
    public int minY(){
      return y-r;
    }

    public boolean fill(int x0, CumulArray arr){
      double[][] gg = grids.get(r);
      int i = x0-minX();
      if(i >= 2*r)
        return false;
      int y0 = minY();
      int j = 0;
      if(y0 < 0)
        j = -y0;
      int mxj = 2*r;
      if(y0 + mxj > max){
        
        mxj = max-y0;
      }
      for(;j<mxj; ++j){
        if(gg[i][j]>0)
          arr.insert(y0+j, gg[i][j]);
      }
      return true;
    }
    
    public boolean fill(int x0, double[] arr){
      double[][] gg = grids.get(r);
      int i = x0-minX();
      if(i >= 2*r)
        return false;
      int y0 = minY();
      int j = 0;
      if(y0 < 0)
        j = -y0;
      int mxj = 2*r;
      if(y0 + mxj > max){
        mxj = max-y0;
      }
      for(;j<mxj; ++j){
        arr[y0+j] += gg[i][j];
      }
      return true;
    }
    
    @Override
    public int compareTo(Point o) {
      int ret = Integer.compare(minX(), o.minX());
      if(ret == 0)
        ret = Integer.compare(y,o.y);
      return ret;
    }

  }
  

  static class XY implements Comparable<XY>{
    
    final int x;
    final int y;
    public XY(int x, int y) {
      this.x = x;
      this.y = y;
    }
    
    
    
    @Override
    public String toString() {
      return "XY [x=" + x + ", y=" + y + "]";
    }



    @Override
    public int hashCode() {
      final int prime = 31;
      int result = 1;
      result = prime * result + x;
      result = prime * result + y;
      return result;
    }
    @Override
    public boolean equals(Object obj) {
      if (this == obj)
        return true;
      if (obj == null)
        return false;
      if (getClass() != obj.getClass())
        return false;
      XY other = (XY) obj;
      if (x != other.x)
        return false;
      if (y != other.y)
        return false;
      return true;
    }



    @Override
    public int compareTo(XY o) {
      int ret = Integer.compare(x, o.x);
      if(ret == 0)
        ret = Integer.compare(y, o.y);
      return ret;
    }
  }
  
  
  static List<double[][]> grids;
  static List<XY> clist = new ArrayList<>();
  static Map<XY,Double> cmap = new HashMap<>();
  
  static void init(){
    grids = new ArrayList<>();
    grids.add(null);
    for(int i=1; i<=50; ++i){
      grids.add(getLocalGrid(i));
//      double s = 0;
//      double[][] gg = grids.get(i);
//      for(int x = 0; x<gg.length; ++x)
//        for(int y = 0; y<gg.length; ++y)
//          s += gg[x][y];

    }
    
  }

  
  private static void solve(List<Point> pp, List<int[]> qq) {
    init();
    for(int[] q : qq){
      int x0 = q[0];
      int x1 = q[2];
      int y0 = q[1];
      int y1 = q[3];
      clist.add(new XY(x0,y0));
      clist.add(new XY(x0,y1));
      clist.add(new XY(x1,y0));
      clist.add(new XY(x1,y1));
    }
    Collections.sort(clist);
    fillMap(pp);
    for(int[] q : qq){
      int x0 = q[0];
      int x1 = q[2];
      int y0 = q[1];
      int y1 = q[3];
      double d = cmap.get(new XY(x1,y1));
      d -= cmap.get(new XY(x1,y0));
      d -= cmap.get(new XY(x0,y1));
      d += cmap.get(new XY(x0,y0));
      if(d < 0)
        d = 0;
      if(!silent)
        System.out.println(format.format(d));
    }
  }

  private static void solve2(List<Point> pp, List<int[]> qq) {
    init();
    for(int[] q : qq){
      int x0 = q[0];
      int x1 = q[2];
      int y0 = q[1];
      int y1 = q[3];
      clist.add(new XY(x0,y0));
      clist.add(new XY(x0,y1));
      clist.add(new XY(x1,y0));
      clist.add(new XY(x1,y1));
    }
    Collections.sort(clist);
    fillMap2(pp);
    for(int[] q : qq){
      int x0 = q[0];
      int x1 = q[2];
      int y0 = q[1];
      int y1 = q[3];
      double d = cmap.get(new XY(x1,y1));
      d -= cmap.get(new XY(x1,y0));
      d -= cmap.get(new XY(x0,y1));
      d += cmap.get(new XY(x0,y0));
      if(d < 0)
        d = 0;
      if(!silent)
        System.out.println(format.format(d));
    }
  }


  private static void fillMap(List<Point> pp) {
    Collections.sort(pp);
//    pp.sort((a,b)->Integer.compare(a.minX(), b.minX()));

    CumulArray carr = new CumulArray(max);
    int pi = 0;
    int ci = 0;
    Set<Point> current = new HashSet<>();
    for(int x=0; x<max; ++x){
      while(ci<clist.size() && clist.get(ci).x == x){
        XY xy = clist.get(ci++);
        cmap.put(xy, carr.getSum(xy.y));
      }
      if(x == max-1)
        break;
      List<Point> toRemove = new ArrayList<>();
      while(pi<pp.size() && pp.get(pi).minX() <= x){
        Point p = pp.get(pi++);
        current.add(p);
      }
      for(Point p : current){
        if(!p.fill(x, carr)){
          toRemove.add(p);
        }
      }
      current.removeAll(toRemove);
      
    }
    
  }

  private static void fillMap2(List<Point> pp) {
    Collections.sort(pp);

    
    double[] arr = new double[max];
    int pi = 0;
    int ci = 0;
    Set<Point> current = new HashSet<>();
    List<Point> toRemove = new ArrayList<>();
    for(int x=0; x<max; ++x){
      double sum = 0;
      int si = 0;
      while(ci<clist.size() && clist.get(ci).x == x){
        XY xy = clist.get(ci++);
        while(si < xy.y)
          sum += arr[si++];
        cmap.put(xy, sum);
      }
      if(x == max-1)
        break;
      toRemove.clear();
      while(pi<pp.size() && pp.get(pi).minX() <= x){
        Point p = pp.get(pi++);
        current.add(p);
      }
      for(Point p : current){
        if(!p.fill(x, arr)){
          toRemove.add(p);
        }
      }
      current.removeAll(toRemove);
      
    }
    
  }

  
  
  static int[] getInts(BufferedReader br) throws IOException{
    String[] ss = new String[0];
    while(ss.length==0 || "".equals(ss[0])) ss = br.readLine().split(" ");
    int[] ret = new int[ss.length];
    for(int i=0; i<ss.length; ++i){
      ret[i] = Integer.parseInt(ss[i]);
    }
    return ret;
  }

  static long[] getLongs(BufferedReader br) throws IOException{
    String[] ss = new String[0];
    while(ss.length==0 || "".equals(ss[0])) ss =  br.readLine().split(" ");
    long[] ret = new long[ss.length];
    for(int i=0; i<ss.length; ++i){
      ret[i] = Long.parseLong(ss[i]);
    }
    return ret;
  }

  static void goFile(String s) throws Exception{
    go(new FileReader(new File(s)));
  }

  static void go() throws NumberFormatException, Exception{
    go(new InputStreamReader(System.in));
  }

  static void goRandom(int n, int q, long seed){
    Random r = new Random(seed);
    List<Point> pp = new ArrayList<>();
    for(int i=0; i<n; ++i){
      pp.add(new Point(r.nextInt(max),r.nextInt(max),r.nextInt(50)+1));
    }
    List<int[]> qq = new ArrayList<>();
    for(int i=0; i<q; ++i){
      int x0 = r.nextInt(max);
      int x1 = r.nextInt(max);
      if(x0 > x1){
        int temp = x0;
        x0 = x1;
        x1 = temp;
      }
      int y0 = r.nextInt(max);
      int y1 = r.nextInt(max);
      if(y0 > y1){
        int temp = y0;
        y0 = y1;
        y1 = temp;
      }
      
      qq.add(new int[]{x0,y0,x1,y1});
    }
    solve(pp,qq);
    
  }
  
  
  static void goRandom2(int n, int q, long seed){
    Random r = new Random(seed);
    List<Point> pp = new ArrayList<>();
    for(int i=0; i<n; ++i){
      pp.add(new Point(r.nextInt(max),r.nextInt(max),r.nextInt(50)+1));
    }
    List<int[]> qq = new ArrayList<>();
    for(int i=0; i<q; ++i){
      int x0 = r.nextInt(max);
      int x1 = r.nextInt(max);
      if(x0 > x1){
        int temp = x0;
        x0 = x1;
        x1 = temp;
      }
      int y0 = r.nextInt(max);
      int y1 = r.nextInt(max);
      if(y0 > y1){
        int temp = y0;
        y0 = y1;
        y1 = temp;
      }
      
      qq.add(new int[]{x0,y0,x1,y1});
    }
    solve2(pp,qq);
    
  }
  
  static void go(Reader r) throws Exception{
    BufferedReader br = new BufferedReader(r);
    int[] nq = getInts(br);
    int n = nq[0], q = nq[1];
    
    List<Point> pp = new ArrayList<>();
    for(int i=0; i<n; ++i){
      pp.add(new Point(getInts(br)));
    }
    List<int[]> qq = new ArrayList<>();
    for(int i=0; i<q; ++i){
      qq.add(getInts(br));
    }
    solve2(pp,qq);
  }

  public static void main(String[] args) throws Exception{
    go();
//    silent = true;
//    long tt = System.currentTimeMillis();
////    max = 1000;
//    goRandom2(50000, 100_000, 12333);
//  System.out.println(System.currentTimeMillis()-tt);
//  tt = System.currentTimeMillis();
////    System.out.println();
//    goRandom(50000, 100_000, 12333);
//    System.out.println(System.currentTimeMillis()-tt);
//
//    tt = System.currentTimeMillis();
////  System.out.println();
//  goRandom(50000, 10, 12333);
//  System.out.println(System.currentTimeMillis()-tt);

    
//    silent = false;
//    goFile("input/temp.txt");
  }

}