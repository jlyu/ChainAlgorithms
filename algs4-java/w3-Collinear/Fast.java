public class Fast {
    
    public static void main(String[] args) {
        
        // rescale coordinates and turn on animation mode
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        StdDraw.show(0);
        StdDraw.setPenRadius(0.005);  // make the points a bit larger
        
        // read
        String filename = args[0];
        In in = new In(filename);
        int N = in.readInt();  // the first element: the number of points
        
        Point[] points = new Point[N];
        
        for (int i = 0; i < N; i++) {
            int x = in.readInt();
            int y = in.readInt();
            Point p = new Point(x, y);
            
            points[i] = p;
            p.draw();
        }
        StdDraw.show(0);
        
        for (int i = 0; i < N; i++) {
            
        }
    }
    
}