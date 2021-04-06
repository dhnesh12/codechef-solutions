import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.OutputStream;


public class Main {

    public static void solve(Kattio io) {
        double a = io.getInt();
        double r1 = io.getInt();
        double r2 = io.getInt();
        double r3 = io.getInt();
        Path2D.Double p = new Path2D.Double();
        p.moveTo(-a,0); p.lineTo(a,0); p.lineTo(0,Math.sqrt(3)*a);
        p.closePath();
        Area triangle = new Area(p);
        Ellipse2D.Double e1 = new Ellipse2D.Double(-r1,-r1,2*r1,2*r1);
        Area l1 = new Area(e1);

        Ellipse2D.Double e2 = new Ellipse2D.Double(a*0.5-r2,Math.sqrt(3)*a*0.5-r2,2*r2,2*r2);
        Area l2 = new Area(e2);
        Ellipse2D.Double e3 = new Ellipse2D.Double(-a*0.5-r3,0.5*Math.sqrt(3)*a-r3,2*r3,2*r3);
        Area l3 = new Area(e3);

        triangle.intersect(l1);
        triangle.intersect(l2);
        triangle.intersect(l3);

        RectangularShape sample = triangle.getBounds2D();
        double w = sample.getWidth();
        double h = sample.getHeight();
        double mx = sample.getMinX();
        double my = sample.getMinY();
        int cnt = 0;
        int total = 0;
        do {
            double x1 = mx+Math.random()*w;
            double y1 = my+Math.random()*h;
            if (triangle.contains(new Point2D.Double(x1,y1))) cnt++;
            total++;
        } while (total<=100000);
        io.print(w*h*(double) cnt / (double) total+"\n");

    }
    public static void main(String[] args) {
	    Kattio io = new Kattio(System.in, System.out);
	    int t = io.getInt();
	    for (int i=0; i<t; ++i) solve(io);
	    io.close();
    }
}

/** Simple yet moderately fast I/O routines.
 *
 * Example usage:
 *
 * com.company.Kattio io = new com.company.Kattio(System.in, System.out);
 *
 * while (io.hasMoreTokens()) {
 *    int n = io.getInt();
 *    double d = io.getDouble();
 *    double ans = d*n;
 *
 *    io.println("Answer: " + ans);
 * }
 *
 * io.close();
 *
 *
 * Some notes:
 *
 * - When done, you should always do io.close() or io.flush() on the
 *   com.company.Kattio-instance, otherwise, you may lose output.
 *
 * - The getInt(), getDouble(), and getLong() methods will throw an
 *   exception if there is no more data in the input, so it is generally
 *   a good idea to use hasMoreTokens() to check for end-of-file.
 *
 * @author: Kattis
 */


class Kattio extends PrintWriter {
    public Kattio(InputStream i) {
        super(new BufferedOutputStream(System.out));
        r = new BufferedReader(new InputStreamReader(i));
    }
    public Kattio(InputStream i, OutputStream o) {
        super(new BufferedOutputStream(o));
        r = new BufferedReader(new InputStreamReader(i));
    }

    public boolean hasMoreTokens() {
        return peekToken() != null;
    }

    public int getInt() {
        return Integer.parseInt(nextToken());
    }

    public double getDouble() {
        return Double.parseDouble(nextToken());
    }

    public long getLong() {
        return Long.parseLong(nextToken());
    }

    public String getWord() {
        return nextToken();
    }



    private BufferedReader r;
    private String line;
    private StringTokenizer st;
    private String token;

    private String peekToken() {
        if (token == null)
            try {
                while (st == null || !st.hasMoreTokens()) {
                    line = r.readLine();
                    if (line == null) return null;
                    st = new StringTokenizer(line);
                }
                token = st.nextToken();
            } catch (IOException e) { }
        return token;
    }

    private String nextToken() {
        String ans = peekToken();
        token = null;
        return ans;
    }
}
