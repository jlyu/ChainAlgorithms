/* Brute force. 
 * Write a program Brute.java that examines 4 points at a time and checks 
 * whether they all lie on the same line segment, printing out any such line 
 * segments to standard output and drawing them using standard drawing. 
 * 
 * To check whether the 4 points p, q, r, and s are collinear, check whether 
 * the slopes between p and q, between p and r, and between p and s are 
 * all equal.
 */
import java.util.Arrays;

public class Brute {
    
    private static void findCollinear(Point[] points, int N) {
        
        for (int i = 0; i < N - 3; i++) {
            for (int j = i + 1; j < N - 2; j++) {
                for (int k = j + 1; k < N - 1; k++) {
                     for (int l = k + 1; l < N; l++) {
                         
                         if (isCollinear(points[i], points[j], points[k], points[l])) {
                            print(points[i], points[j], points[k], points[l]);
                         }    
                         
                    }
                } // end for k
            } // end for j
        } // end for i
    }
    
    private static void print(Point p1, Point p2, Point p3, Point p4) {
        StdOut.printf("%s -> %s -> %s -> %s\n", 
                      p1.toString(), 
                      p2.toString(), 
                      p3.toString(), 
                      p4.toString());
        
        p1.drawTo(p4);
    }

    
    private static boolean isCollinear(Point p1, Point p2, Point p3, Point p4) {
  
        if (p1.slopeTo(p2) == p1.slopeTo(p3)) {
            return p1.slopeTo(p2) == p1.slopeTo(p4);
        } 
        return false;
    }
    
    private static Point[] readPoints(String fileName) {
        
        In in = new In(fileName);
        int N = in.readInt();  // the first element: the number of points
        
        Point[] points = new Point[N];
        
        for (int i = 0; i < N; i++) {
            int x = in.readInt();
            int y = in.readInt();
            Point p = new Point(x, y);
            
            points[i] = p;
            p.draw();
        }
        
        return points;
    }
    
    
    public static void main(String[] args) {
        
        if (args.length != 1) {
            throw new IllegalArgumentException("Wrong number of arguments");
        }
        
        // rescale coordinates and turn on animation mode
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        StdDraw.setPenRadius(0.005);  // make the points a bit larger
        
        Point[] points = readPoints(args[0]);
        int N = points.length;
        
        if (N >= 4) {
            Arrays.sort(points);
            Brute.findCollinear(points, N);
        }

        // display to screen all at once
        StdDraw.show(0);

    }
}