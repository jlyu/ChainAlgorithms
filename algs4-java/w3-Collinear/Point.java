import java.util.Arrays;
import java.util.Comparator;


public class Point implements Comparable<Point> {

    // compare points by slope
    public final Comparator<Point> SLOPE_ORDER = new BySlopeOrder();

    private final int x; // x coordinate
    private final int y; // y coordinate

        
    // create the point (x, y)
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    // plot this point to standard drawing
    public void draw() {
        StdDraw.point(x, y);
    }

    // draw line between this point and that point to standard drawing
    public void drawTo(Point that) {
        StdDraw.line(this.x, this.y, that.x, that.y);
    }
    
    public boolean isHorizontal(Point that) {
        if ((this.y == that.y) && (this.x != that.x)) {
            return true;
        }
        return false;
    }
    
    public boolean isVertical(Point that) {
        if ((this.x == that.x) && (this.y != that.y)) {
            return true;
        }
        return false;
    }

    // slope between this point and that point
    public double slopeTo(Point that) {
        if (this.x == that.x) {
            if (this.y > that.y) { return Double.POSITIVE_INFINITY; }
            if (this.y < that.y) { return Double.NEGATIVE_INFINITY; }
        }
        
        if (this.y == that.y) {
            if (this.x > that.x) { return +0.0; }
            if (this.x < that.x) { return -0.0; }
        }
        
        return (double) (that.y - this.y) / (double) (that.x - this.x);
    }

    // is this point lexicographically smaller than that one?
    // comparing y-coordinates and breaking ties by x-coordinates
    public int compareTo(Point that) {
        if (this.y > that.y) { return +1; }
        if (this.y == that.y) {
            if (this.x > that.x) { return +1; } 
            if (this.x == this.y) { return 0; }
        }
        return -1;
    }

    // return string representation of this point
    public String toString() {
        return "(" + x + ", " + y + ")";
    }
    

    
    private static void show(Comparable[] a) {
        for (int i = 0; i < a.length; i++) {
            StdOut.print(a[i] + " ");
        }
        StdOut.println();
    }
    
    private static void exch(Object[] a, int i, int j) {
        Object t = a[i]; a[i] = a[j]; a[j] = t;
    }
        

    
    public class BySlopeOrder implements Comparator<Point> {
        
        public int compare(Point p1, Point p2) { // TODO
            if (Point.this.slopeTo(p1) > Point.this.slopeTo(p2)) { return +1; }
            if (Point.this.slopeTo(p1) < Point.this.slopeTo(p2)) { return -1; }
           // StdOut.println(p1.toString() + "|" + p2.toString());
            return 0;
        }
    }
    

    
    // unit test
    public static void main(String[] args) {
        // rescale coordinates and turn on animation mode
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        StdDraw.show(0);
        StdDraw.setPenRadius(0.005);  // make the points a bit larger
        // read
        String filename = args[0];
        In in = new In(filename);
        int N = in.readInt();
        
        Point[] points = new Point[N];
        //Array<Point> points = new Array<Point>();
        
        for (int i = 0; i < N; i++) {
            int x = in.readInt();
            int y = in.readInt();
            Point p = new Point(x, y);
            points[i] = p;
            p.draw();
        }
        
       
        //Arrays.sort(points, new BySlopeOrder());
        
        
        show(points);
        
        StdDraw.show(0);
    }
}