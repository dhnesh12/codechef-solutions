/* package codechef; // don't place package name! */

import java.io.*;
import java.util.*;
 
 
 
class ChefSpag {
  static void printA(double[][] x){
    for(double[] y : x)
      System.out.println(Arrays.toString(y));
  }
  static void print(Object...x){
    for(Object y : x)
      if(y instanceof boolean[]){
        System.out.print(Arrays.toString((boolean[])y)+",");
      }
      else if(y instanceof long[]){
        System.out.print(Arrays.toString((long[])y)+",");
      }
      else if(y instanceof long[][]){
        System.out.println();
        for(long[] z : (long[][])y){
          System.out.println(Arrays.toString(z));
        }
      }else if(y instanceof int[]){
        System.out.print(Arrays.toString((int[])y)+",");
      }else{
        System.out.print(y + ",");
      }
    System.out.println();
  }
 
  static final long mod = 1_000_000_009;
  static int DIM = 4;
  static long[] fff;
 
  static long minv(long a){
    long b = mod;
    long t, q;
    long x0 = 0, x1 = 1;
    while (a > 1) {
      q = a / b;
      t = b; b = a % b; a = t;
      t = x0; x0 = x1 - q * x0; x1 = t;
    }
    x1 %= mod;
    if (x1 < 0) x1 += mod;
    return x1;
  }
 
  static long gcd(long a, long b){
    while(b != 0){
      long c = a%b;
      a = b;
      b = c;
    }
    return a;
  }
 
  static Matrix identity(){
    Matrix ret = new Matrix();
    for(int i=0; i<DIM; ++i)
      ret.x[i][i]=1;
    return ret;
  }
 
  static class Matrix{
    long[][] x;
 
    public Matrix(){
      x = new long[DIM][DIM];
    }
 
    public Matrix(long[][] x) {
      this.x = x;
    }
 
    Matrix copy(){
      long[][] z = new long[DIM][];
      for(int i=0; i<DIM; ++i)
        z[i] = Arrays.copyOf(x[i], DIM);
      return new Matrix(z);
    }
 
    public Matrix add(Matrix o){
      for(int i=0; i<DIM; ++i)
        for(int j=0; j<DIM; ++j)
          x[i][j] = (x[i][j]+o.x[i][j]) % mod;
      return this;
    }
 
    public Matrix add(Matrix o, long c){
      for(int i=0; i<DIM; ++i)
        for(int j=0; j<DIM; ++j)
          x[i][j] = (x[i][j]+o.x[i][j]*c) % mod;
      return this;
    }
 
    public Matrix subtract(Matrix o){
      for(int i=0; i<DIM; ++i)
        for(int j=0; j<DIM; ++j)
          x[i][j] = (mod + x[i][j]-o.x[i][j]) % mod;
      return this;
    }
 
    public Matrix addProduct(Matrix a, Matrix b){
      for(int i=0; i<DIM; ++i)
        for(int j=0; j<DIM; ++j)
          for(int k=0; k<DIM; ++k){
            x[i][j] += a.x[i][k]*b.x[k][j];
            x[i][j] %= mod;
          }
      return this;
 
    }
 
    public Matrix mult(Matrix o){
      return new Matrix().addProduct(this, o);
    }
 
    public Matrix mult(long c){
      for(int i=0; i<DIM; ++i)
        for(int j=0; j<DIM; ++j)
          x[i][j] = x[i][j]*c % mod;
      return this;
    }
 
    long[] mult(long[] z){
      long[] ret = new long[DIM];
      for(int i=0; i<DIM; ++i)
        for(int j=0; j<DIM; ++j)
          ret[i] = (ret[i] + x[i][j]*z[j]) % mod;
      return ret;
    }
 
    void rowSwap(int i, int j){
      long[] temp = x[j];
      x[j] = x[i];
      x[i] = temp;		
    }
 
    void rowAdd(int source, int targ, long mul){
      for(int i=0; i<DIM; ++i){
        x[targ][i] = (x[targ][i] + x[source][i]*mul)%mod;
      }
    }
 
    void rowMult(int k, long mul){
      for(int i=0; i<DIM; ++i){
        x[k][i] = (x[k][i]*mul)%mod;
      }
    }
 
    Matrix inv(){
      Matrix t = copy();
      Matrix ret = identity();
      for(int i=0; i<DIM; ++i){
        if(t.x[i][i]==0){
          for(int j=i+1;j<DIM; ++j){
            if(t.x[j][i]!=0){
              t.rowSwap(i, j);
              ret.rowSwap(i,j);
              break;
            }
          }
        }
        long ii = minv(t.x[i][i]);
        t.rowMult(i,ii);
        ret.rowMult(i,ii);
        for(int j = i+1; j<DIM; ++j){
          if(t.x[j][i] == 0)
            continue;
          ret.rowAdd(i,j,mod-t.x[j][i]);
          t.rowAdd(i,j,mod-t.x[j][i]);
        }			
      }
      for(int i = DIM-1; i>=0; --i){
        for(int j=0; j<i; ++j){
          if(t.x[j][i] == 0)
            continue;
          ret.rowAdd(i,j,mod-t.x[j][i]);
          t.rowAdd(i,j,mod-t.x[j][i]);
        }
      }			
 
 
      return ret;			
    }
 
    Matrix pow(long k){
      if(k < 0)
        return inv().pow(-k);
      Matrix pp = copy();
      Matrix ret = identity();
      while(k > 0){
        if((k&1L)!=0){
          ret = ret.mult(pp);
        }
        pp = pp.mult(pp);
        k >>=1;
      }
      return ret;
    }
 
 
 
    // sum x^i for i<=k
    Matrix powSum(long k){
      if(k < 0)
        return new Matrix();
      Matrix p = copy();
      Matrix c = identity();
 
      Matrix ret = identity();
      while (k > 0){
        if((k&1L)!=0){
          ret = ret.mult(p);
          ret.add(c);
        }
 
        c.addProduct(p,c.copy());
        p = p.mult(p);
        k >>= 1;
      }
 
      return ret;
    }
 
 
    Matrix powSumBrute(int k){
      Matrix ret = identity();
      Matrix p = identity();
      for(int i=0; i<k; ++i){
        p = p.mult(this);
        ret.add(p);
      }
      return ret;
    }
 
 
    @Override
    public String toString() {
      StringBuilder sb = new StringBuilder();
      for(int i=0; i<DIM; ++i){
        sb.append(Arrays.toString(x[i]));
        sb.append("\n");
      }
      sb.append(mult(fff)[0] + "\n");
      return sb.toString();
    }
 
  }
 
  // sum a^ib^j for 0 <= i+j <= k
  static Matrix wedgeSum(Matrix a, Matrix b, long k){
    if(k < 0)
      return new Matrix();
    Matrix swedge = identity();
    Matrix sblock = identity();
 
    Matrix ret = identity();
    Matrix block = identity();
    Matrix bcum = b.copy();
    while(k > 0){
      if((k & 1L)!= 0){
        ret = ret.mult(a);
        ret.add(block);
        ret.addProduct(bcum, swedge);
 
        block = block.mult(b);
        block.add(sblock);
        bcum = bcum.mult(b);
 
      }
      block.add(block.mult(a));
 
      swedge = a.mult(swedge).add(b.mult(swedge)).add(sblock);
      sblock.add(sblock.mult(b));      
      sblock.add(sblock.mult(a));
      a = a.mult(a);
      b = b.mult(b);
      k >>= 1;
    }
    return ret;
  }
 
 
  static Matrix wedgeSumBrute(Matrix a, Matrix b, long k){
    Matrix ret = new Matrix();
    for(int i=0; i<=k; ++i)
      for(int j=0; j+i<=k; ++j){
        ret.add(a.pow(i).mult(b.pow(j)));
      }
    return ret;
  }
 
 
  // sum a^ib^j for 0 <= [i/c]+j <= k
  static Matrix wedgeSumOffset(Matrix a, Matrix b, long k, long c){
 
    Matrix block0 = a.powSum(c-1);
    a = a.pow(c);
 
    Matrix swedge = block0.copy();
    Matrix sblock = block0.copy();
 
    Matrix ret = block0.copy();
    Matrix block = block0.copy();
    Matrix bcum = b.copy();
    while(k > 0){
      if((k & 1L)!= 0){
        ret = ret.mult(a);
        ret.add(block);
        ret.addProduct(bcum, swedge);
 
        block = block.mult(b);
        block.add(sblock);
        bcum = bcum.mult(b);
 
      }
      block.add(block.mult(a));
 
      swedge = a.mult(swedge).add(b.mult(swedge)).add(sblock);
      sblock.add(sblock.mult(b));      
      sblock.add(sblock.mult(a));
      a = a.mult(a);
      b = b.mult(b);
      k >>= 1;
    }
    return ret;
  }
 
 
  static Matrix wedgeSumOffsetBrute(Matrix a, Matrix b, long k, long c){
    Matrix ret = new Matrix();
    for(long i=0; i/c<=k; ++i)
      for(long j=0; j+i/c<=k; ++j){
        ret.add(a.pow(i).mult(b.pow(j)));
      }
    return ret;
  }
 
  // sum a^ib^j for i/amax + j/bmax < 1 (i.e. i*bmax+ j*amax < amax*bmax)
  static Matrix wedgeSumGeneral(Matrix a, Matrix b, long amax, long bmax){
    if(amax == bmax)
      return wedgeSum(a,b,amax-1);
    if(amax <=0 || bmax <= 0)
      return new Matrix();		
    if(amax < bmax)
      return wedgeSumGeneral(b,a,bmax,amax);
 
    long c = amax/bmax;
    Matrix ret = wedgeSumOffset(a,b,bmax-1,c);
    long am0 = amax - c*bmax;
    Matrix base = a.pow(c*bmax);
    Matrix b0 = b.mult(a.pow(-c));
 
    return ret.add(base.mult(wedgeSumGeneral(a,b0,am0,bmax)));
  }
 
 
  static Matrix wedgeSumGeneralBrute(Matrix a, Matrix b, long amax, long bmax){
    Matrix ret = new Matrix();
    long ab = amax*bmax;
    for(int i=0; i*bmax < ab; ++i)
      for(int j=0; j*amax + i*bmax < ab; ++j){
        ret.add(a.pow(i).mult(b.pow(j)));
      }
    return ret;
  }
 
 
  static enum Dir{
    RIGHT,
    LEFT,
    UP,
    DOWN
  }
 
  static Dir getDirection(long[] a, long[] b) {
    if(a[0]<b[0])
      return Dir.RIGHT;
    if(a[0]>b[0])
      return Dir.LEFT;
    if(a[1]<b[1])
      return Dir.UP;
    return Dir.DOWN;
  }
 
  static class Solver{
    long[] ff;
    final long[] ff0;
    final long[] aa;
    Matrix M;
 
    List<long[]> points;
    int nn;
 
    public Solver(long[] aa, long[] ff1, List<long[]> points) {
      nn = points.size();
      List<long[]> zz0 = new ArrayList<>();
      for(int i=nn-1; i>=0; --i){
        zz0.add(points.get(i));
      }
      this.points = zz0;
 
 
      DIM = 4;
      this.ff = ff1;
      ff0 = ff1;
      this.aa = aa;
 
 
      while(aa[DIM-1]==0){
        ff = Arrays.copyOfRange(ff,1,ff.length);
        DIM--;
        if(DIM == 0)
          return;
        //          throw new RuntimeException();
        //          return;
      }
 
 
 
 
      M = new Matrix();
      for(int i=1; i<DIM; ++i){
        M.x[i-1][i] = 1;
      }
      for(int i=0; i<DIM; ++i){
        M.x[DIM-1][i] = aa[DIM-1-i];
      }
 
      //      print(ff);
      for(int i=4; i>DIM; --i){
        ff = M.inv().mult(ff);
      }
      fff = ff;
      //      print(ff);
 
      //      if(DIM <=3)
      //        throw new RuntimeException();
      //      
      //      for(int i=0; i<4; ++i){
      //        long v = M.pow(i).mult(ff)[0];
      //        if(v != ff0[i])
      //          throw new RuntimeException("Invalid input");
      //      }
 
    }
 
    public long solve() {
      if(DIM == 0)
        return solve0();
 
 
 
      Matrix m = new Matrix();
      long val = 0;
      for(int i=0; i<nn; ++i){
        long[] a = points.get(i);
        long[] b = points.get((i+1)%nn);
        long[] c = points.get((i+2)%nn);
        print(a,b,c);
        m.add(getEdgeBelow(a,b));
        long val2 = m.mult(ff)[0]; 
        print("Edge Below",val2-val,val);
        val = val2;
        m.add(getBelowPointAdjustment(a,b,c));
        val2 = m.mult(ff)[0]; 
        print("Point Below",val2-val,val);
        val = val2;
        if(getDirection(a, b) == Dir.RIGHT)
          m.add(getLatticeSum(a, b));
        val2 = m.mult(ff)[0]; 
        print("Lattice edge",val2-val,val);
        val = val2;
        m.subtract(getPointAdjustment(a,b,c));
        val2 = m.mult(ff)[0]; 
        print("Point adjust",val2-val,val);
        val = val2;
      }
      return m.mult(ff)[0];
    }
 
    private long solve0() {
      long ret = 0;
      for(int x = 0; x<4; ++x)
        for(int y = 0; x+y<4; ++y)
          if(isInPoly(x, y)){
            ret += ff0[x+y];
          }
      return ret % mod;
    }
 
    public long solve2() {
      if(DIM == 0)
        return solve0();
 
 
 
      Matrix m = new Matrix();
      for(int i=0; i<nn; ++i){
        long[] a = points.get(i);
        long[] b = points.get((i+1)%nn);
        long[] c = points.get((i+2)%nn);
 
        m.add(getEdgeBelow(a,b));
        m.add(getBelowPointAdjustment(a,b,c));
        if(getDirection(a, b) == Dir.RIGHT)
          m.add(getLatticeSum(a, b));
        m.subtract(getPointAdjustment(a,b,c));
      }
      long ret = m.mult(ff)[0];
      ret += smallAdjust();
      ret %= mod;
      if(ret < 0)
        ret += mod;
      return ret;
    }
 
 
    private long smallAdjust() {
      long ret = 0;
      for(int x = 0; x<4; ++x)
        for(int y = 0; x+y<4; ++y)
          if(isInPoly(x, y)){
            ret += ff0[x+y];
            ret -= M.pow(x+y).mult(ff)[0];
          }
      return ret;
    }
 
    boolean isInPoly(long x, long y){
      for(long[] z : points){
        if(z[0]==x && z[1]==y)
          return true;
      }
 
      int count = 0;
      for(int i=0; i<nn; ++i){
        long[] a = points.get(i);
        long[] b = points.get((i+1)%nn);
        long x0 = a[0], y0 = a[1], x1 = b[0], y1 = b[1];
        if(y0 < y && y1 < y)
          continue;
        if(y0 > y && y1 > y)
          continue;
        if(x0>x && x1 > x)
          continue;
 
        if(y0 == y1){
          if(x1 >x || x0 > x)
            return true;
          continue;
        }
        if(y0 == y){          
          if(x0 < x && y1>y)
            count++;
          continue;
        }
        if(y1 == y){
          if(x1 < x && y0>y)
            count++;
          continue;
        }
 
        long dx = x1-x0;
        long dy = y1 - y0;
        if(dx == 0){
          if(x == x0)
            return true;
          count++;
          continue;
        }
 
        long cy = y - y0;
        long disc = (x-x0)*dy - cy*dx;
        if(dy < 0)
          disc = -disc;
        if(disc == 0)
          return true;
        if(disc > 0)
          count++;
 
      }
 
 
      return count % 2 == 1;
    }
 
    List<long[]> getPolyPoints(){
      List<long[]> ret = new ArrayList<>();
      long maxx=0, maxy = 0, minx = Long.MAX_VALUE, miny = Long.MAX_VALUE;
      for(long[] p : points){
        minx = Math.min(minx, p[0]);
        miny = Math.min(miny, p[1]);
        maxx = Math.max(maxx, p[0]);
        maxy = Math.max(maxy, p[1]);
      }
 
      for(long x = minx; x<=maxx; ++x)
        for(long y = miny; y<=maxy; ++y)
          if(isInPoly(x, y))
            ret.add(new long[]{x,y});
 
      return ret;
    }
 
 
    long solveBrute(){
      //      Matrix ret = new Matrix();
      long maxx=0, maxy = 0, minx = Long.MAX_VALUE, miny = Long.MAX_VALUE;
      for(long[] p : points){
        minx = Math.min(minx, p[0]);
        miny = Math.min(miny, p[1]);
        maxx = Math.max(maxx, p[0]);
        maxy = Math.max(maxy, p[1]);
      }
      if(maxy>100 || maxx > 100)
        return 0;
      long[] qq = new long[(int)(maxx+maxy)+1];
      for(int i=0; i<4; ++i){
        if(i == qq.length)
          break;
        qq[i] = ff0[i];
      }
      //      if(true)
      //        return 0;
      for(int i=4; i<qq.length; ++i){
        long val = 0;
        for(int j=0; j<4; ++j)
          //val += qq[i-j-1] % mod;
          val += qq[i-j-1]*aa[j] % mod;
        val %= mod;
        qq[i] = val;
      }
      long ret = 0;
      for(long[] xy : getPolyPoints()){
        print(xy,qq[(int)(xy[0] + xy[1])]);
        ret += qq[(int)(xy[0] + xy[1])];
        ret %= mod;
      }
      return ret % mod;
    }
 
    long solveBrute2(){
      Matrix ret = new Matrix();
      long r0 = 0;
      for(long[] xy : getPolyPoints()){
        Matrix pm = getPoint(xy[0],xy[1]);
        ////        print(ret);
        ////        print(pm);
        //        print(ret.mult(ff));
        //        print(pm.mult(ff));
        ret.add(pm);
        //        print(ret.mult(ff));
        //        
        ////        print(ret);
 
        long val = getPoint(xy[0], xy[1]).mult(ff)[0];
        r0 += val;
        r0 %= mod;
        //        print(r0,ret.mult(ff)[0]);
        if(r0 != ret.mult(ff)[0])
          System.exit(0);
      }
      return ret.mult(ff)[0];
    }
 
    long solveBrute3(){
      long ret = 0;
      for(long[] xy : getPolyPoints()){
        ret += getPoint(xy[0], xy[1]).mult(ff)[0];
        ret %= mod;
      }
      return ret;
    }
 
 
    // sum x0<=i<x1, j<y0
    Matrix getBox(long x0, long x1, long y){
      if(y == 0)
        return new Matrix();
      Matrix ret = M.powSum(x1-x0).mult(M.pow(x0));
      return ret.mult(M.powSum(y-1));
    }
 
    // sum x,j, j<y0
    Matrix getBelowPoint(long x, long y){
      if(y == 0)
        return new Matrix();
      return M.pow(x).mult(M.powSum(y-1));
    }
 
    Matrix getPoint(long x, long y){
      return M.pow(x+y);
    }
 
    Matrix getLatticeSum(long[]a, long[] b){
      long x0 = a[0], y0 = a[1];
      long x1 = b[0], y1 = b[1];
      long dx = x1-x0;
      long dy = y1-y0;
      long g = gcd(Math.abs(dx),Math.abs(dy));
      dx /= g;
      dy /= g;
      Matrix ret = getPoint(x0,y0);
      Matrix dm = M.pow(dx+dy);
      return ret.mult(dm.powSum(g));
    }
 
    private Matrix getEdgeBelow(long[] a, long[] b) {
      long x0 = a[0], y0 = a[1];
      long x1 = b[0], y1 = b[1];
      if(Math.abs(x0-x1)<=1)
        return new Matrix();
      if(x1 < x0)
        return getEdgeBelow(b,a).mult(mod-1);
 
      long dx = x1-x0;
      long dy = y1-y0;
      if(dy == 0){
        return getBox(x0+1,x1-1,y0);
      }
      Matrix ret = getBox(x0,x1,Math.min(y0,y1));
      long x=0,y=0;
      Matrix dm = null;
      if(dy > 0){
        x = x1;
        y = y0;
        dm = M.inv();
      }else{
        x = x0;
        y = y1;
        dm = M;
      }
      Matrix base = getPoint(x,y);
      Matrix wedge = wedgeSumGeneral(dm, M, dx, Math.abs(dy));
 
      ret.addProduct(base, wedge);
      ret.subtract(getBelowPoint(x0,y0));
      ret.subtract(getBelowPoint(x1,y1));
      return ret;
    }
 
    private Matrix getPointAdjustment(long[] a, long[] b, long[] c) {
      Dir d0 = getDirection(a, b);
      Dir d1 = getDirection(b, c);      
      
      long dx0 = a[0]-b[0];
      long dx1 = c[0]-b[0];
      long dy0 = a[1]-b[1];
      long dy1 = c[1]-b[1];
      dy0 *= Math.abs(dx1);
      dy1 *= Math.abs(dx0);
      boolean ychigher = (dy1>dy0);
//      boolean ychigher = (c[1]>a[1]);
 
      boolean remPoint = false;
      switch(d0){
      case DOWN:        
        remPoint = (d1 == Dir.RIGHT); 
        break;
      case LEFT:
        remPoint = (d1 == Dir.RIGHT) && !ychigher; 
        break;
      case RIGHT:
        switch(d1){
        case DOWN:          
          break;
        case LEFT:
          remPoint = ychigher;
          break;
        case RIGHT:
        case UP:
          remPoint = true;
          break;
        }
        break;
      case UP:
        break;
      }
 
      return remPoint ? getPoint(b[0], b[1]) : new Matrix();
    }
 
 
 
    private Matrix getBelowPointAdjustment(long[] a, long[] b, long[] c) {
      long x=b[0], y=b[1];
      Dir d0 = getDirection(a, b);
      Dir d1 = getDirection(b, c);
 
      switch(d0){
      case DOWN:
        switch(d1){
        case DOWN:
        case RIGHT:
        case UP:
          return new Matrix();
        case LEFT:
          return getBelowPoint(x, y).mult(mod-1);
        }
      case LEFT:
        switch(d1){
        case DOWN:
        case RIGHT:
          return new Matrix();
        case UP:
        case LEFT:
          return getBelowPoint(x, y).mult(mod-1);
        }
      case RIGHT:
        switch(d1){
        case UP:
        case LEFT:
          return new Matrix();
        case DOWN:
        case RIGHT:
          return getBelowPoint(x, y);
        }
      case UP:
        switch(d1){
        case DOWN:
        case LEFT:
        case UP:
          return new Matrix();
        case RIGHT:
          return getBelowPoint(x, y);
        }
      }
      return null;
    }
 
 
 
  }
 
  static class Point implements Comparable<Point>{
    long x, y;
 
    public Point(long x, long y) {
      this.x = x;
      this.y = y;
    }
 
    @Override
    public int hashCode() {
      final int prime = 31;
      int result = 1;
      result = prime * result + (int) (x ^ (x >>> 32));
      result = prime * result + (int) (y ^ (y >>> 32));
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
      Point other = (Point) obj;
      if (x != other.x)
        return false;
      if (y != other.y)
        return false;
      return true;
    }
 
    void add(Point q){
      x += q.x;
      y += q.y;
    }
 
    void subtract(Point q){
      x -= q.x;
      y -= q.y;
    }
 
    @Override
    public int compareTo(Point o) {
      double tan = Math.atan2(y, x);
      double otan = Math.atan2(o.y, o.x);
      int ret = Double.compare(tan, otan);
      if(ret == 0)
        ret = Long.compare(x+y, o.x + o.y);
      return ret;
    }
 
    public double atan() {
      return Math.atan2(y,x);
    }    
 
    @Override
    public String toString() {
      return "[" + x + "," + y + "]";
    }
 
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
 
 
  static void go(Reader r) throws Exception{
    BufferedReader br = new BufferedReader(r);
    int t = getInts(br)[0];
    for(int i = 0; i<t; ++i){
      long[] vals = getLongs(br);
      int n = (int) vals[0];
      long aa[] = Arrays.copyOfRange(vals, 1,5);
      long ff[] = Arrays.copyOfRange(vals, 5,9);
      List<long[]> zz = new ArrayList<>();
      for(int j=0; j<n; ++j){
        long[] z = getLongs(br);
        zz.add(z);
      }
      Solver s = new Solver(aa,ff,zz);
      //      for(long[] xy : s.getPolyPoints())
      //        print(xy,s.getPoint(xy[0], xy[1]).mult(s.ff)[0]);
      System.out.println(s.solve2());
//      System.out.println(s.solveBrute());
      //      System.out.println(s.solveBrute2());
      //      System.out.println(s.solveBrute3());
      //      s = new Solver(aa,ff,zz);
    }
  }
 
  static boolean goRandom(int n, int mx, long seed){
    Random r = new Random(seed);
    long[] aa = new long[4];
    long[] bb = new long[4];
    for(int i=0; i<4; ++i){
      aa[i] = r.nextInt(mx);
      bb[i] = r.nextInt(mx);
    }
    Set<Point> ss = new HashSet<>();
    while(ss.size() < n)
      ss.add(new Point(r.nextInt(mx),r.nextInt(mx)));
    Point cc = new Point(0,0);
    for(Point p : ss){
      cc.add(p);
    }
    cc.x/= n;
    cc.y/= n;
    List<Point> pp = new ArrayList<>(ss);
    for(Point p : pp)
      p.subtract(cc);
    Collections.sort(pp);
    for(Point p : pp){
      print(p,p.atan());
      p.add(cc);
    }
    print(cc);
    pp.add(cc);
    
    List<long[]> xy = new ArrayList<>();
    for(Point p : pp)
      xy.add(new long[]{p.x,p.y});
    Solver s = new Solver(aa,bb,xy);
    long r0 = s.solve2();
    long r1 = s.solveBrute();
    if(r0 != r1){
      print(r0);
      print(r1);
      for(long[] z : xy)
        System.out.println(Arrays.toString(z)+",");
    }
    return r0==r1;
    
  }
 
 
 
  public static void main(String[] args) throws Exception{
    go();
//    goFile("input/temp.txt");
//    for(int i=100;;++i){
//      print(i);
//      if(!goRandom(3,50,i))
//        break;
//    }
  }
 
} 