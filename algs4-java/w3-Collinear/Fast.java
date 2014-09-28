import java.util.Arrays;

public class Fast {
    
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
    
    private static void drawCollinear(Point[] points, int lo, int hi) {

        StdOut.printf("%s -> ", points[0].toString());
        Arrays.sort(points, lo, hi);
        for (int k = 0; k < hi-lo; k++) {
            StdOut.printf("%s", points[lo+k].toString());
            if (k != hi-lo-1)
                StdOut.printf(" -> ");
            else
                StdOut.printf("\n");
        }
        points[0].drawTo(points[hi-1]);
    }

    
    private static void findCollinear(Point[] points, int N) {
        Point[] copy = new Point[N];
        for (int j = 0; j < N; j++) {
            copy[j] = points[j];
        }
        
        for (int i = 0; i < N; i++) {
            Point origin = copy[i];
            Arrays.sort(points, 0, N, origin.SLOPE_ORDER);
            
            int lo = 1;
            int hi = 2;
            boolean flag = false;
            if (origin.compareTo(points[lo]) < 0) {
                flag = true;
            }
            
            while (hi < N) {
                 if (points[hi].slopeTo(origin) == points[lo].slopeTo(origin)) {
                     if (points[hi].compareTo(origin) < 0) {
                        flag = false;
                     }
                 } else {
                     
                     if (flag && hi - lo >= 3) {
                        Fast.drawCollinear(points, lo, hi); 
                     }
                     lo = hi;
                     if (origin.compareTo(points[lo]) < 0) {
                         flag = true; 
                     } else { 
                         flag = false;
                     }
                 }
                 hi++;
            }
            if (points[N-1].slopeTo(origin) == points[lo].slopeTo(origin)) {
                if (flag && hi - lo >= 3) {
                    Fast.drawCollinear(points, lo, hi);
                }
            }
        }
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
        
        int numPoints = points.length;
        if (numPoints >= 4) {
            Fast.findCollinear(points, numPoints);
        }
        StdDraw.show(0);
    }
}