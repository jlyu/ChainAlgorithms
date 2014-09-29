import java.util.Comparator;


public class Point implements Comparable<Point> {

    // compare points by slope
    public final Comparator<Point> SLOPE_ORDER = new SlopeComparator();
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

    // return string representation of this point
    public String toString() {
        return "(" + x + ", " + y + ")";
    }
    
    
    // slope between this point and that point
    public double slopeTo(Point that) {
        
        if (this.x == that.x && this.y == that.y) {
            return Double.NEGATIVE_INFINITY;
        }
        else if (this.y == that.y) {
            //if (this.x < that.x) { return +0.0; }
            //if (this.x > that.x) { return -0.0; }
            return 0.0;
        }
        else if (this.x == that.x) {
            //if (this.y < that.y) { return Double.POSITIVE_INFINITY; }
            //if (this.y > that.y) { return Double.NEGATIVE_INFINITY; }
            return Double.POSITIVE_INFINITY;
        }

        
        return (double) (that.y - this.y) / (double) (that.x - this.x);
    }

    
    // is this point lexicographically smaller than that one?
    // comparing y-coordinates and breaking ties by x-coordinates
    @Override
    public int compareTo(Point that) {
        int xCoordDiff = this.x - that.x;
        int yCoordDiff = this.y - that.y;
        
        if (yCoordDiff < 0) {  return -1; }
        else if (yCoordDiff > 0) { return 1; }
        else {
            if (xCoordDiff < 0)  { return -1; }
            else if (xCoordDiff > 0) { return 1; }
            else { return 0; }
        }
    }
    
    
    private class SlopeComparator implements Comparator<Point> {
        
        @Override
        public int compare(Point p1, Point p2) {
            
            double slope1 = Point.this.slopeTo(p1);
            double slope2 = Point.this.slopeTo(p2);
            
            if (slope1 == slope2) {
                return 0;
            } else if (slope1 < slope2) {
                return -1;
            } else {
                return 1;
            }
        }
    }
    

    
    // unit test
    public static void main(String[] args) {
        Point p = new Point(1, 5);
        Point q = new Point(1, 5);
        StdOut.println(p.compareTo(q));
    }
}