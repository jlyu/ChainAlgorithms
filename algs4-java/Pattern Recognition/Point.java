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

    // slope between this point and that point
    public double slopeTo(Point that) {
        if (this.x == that.x) {
            if (this.y > that.y) { return Double.POSITIVE_INFINITY; }
            if (this.y < that.y) { return Double.NEGATIVE_INFINITY; }
            //return Double.INFINITY;
        }
        
        if (this.y == that.y) {
            if (this.x > that.x) { return +0.0; }
            if (this.x < that.x) { return -0.0; }
        }
        
        return (this.y - that.y) / (this.x - that.x);
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
    
    private class BySlopeOrder implements Comparator<Point> {
        public int compare(Point p1, Point p2) { // TODO
            if (Point.this.slopeTo(p1) > Point.this.slopeTo(p2)) { return +1; }
            if (Point.this.slopeTo(p1) < Point.this.slopeTo(p2)) { return -1; }
            return 0;
    }
    
    // unit test
    public static void main(String[] args) {
        /* YOUR CODE HERE */
    }
}