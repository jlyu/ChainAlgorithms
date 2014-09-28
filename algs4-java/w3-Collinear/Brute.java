/* Brute force. 
 * Write a program Brute.java that examines 4 points at a time and checks 
 * whether they all lie on the same line segment, printing out any such line 
 * segments to standard output and drawing them using standard drawing. 
 * 
 * To check whether the 4 points p, q, r, and s are collinear, check whether 
 * the slopes between p and q, between p and r, and between p and s are 
 * all equal.
 */


public class Brute {
    
    private static void printLine(Point p1, Point p2, Point p3, Point p4) {
        p1.drawTo(p2);
        p2.drawTo(p3);
        p3.drawTo(p4);
    }
    
    private static void printString(Point p1, Point p2, Point p3, Point p4) {
                    
        StdOut.println(p1.toString() 
                           + " -> " + p2.toString() 
                           + " -> " + p3.toString() 
                           + " -> " + p4.toString());
    }
    
    private static void print(Point p1, Point p2, Point p3, Point p4) {
        printLine(p1, p2, p3, p4);
        printString(p1, p2, p3, p4);
    }
    
    private static boolean testHorizontal(Point p1, Point p2, Point p3, Point p4) {
        if (p1.isHorizontal(p2)) {
            if (p1.isHorizontal(p3)) {
                if (p1.isHorizontal(p4)) {
              
                    return true;
            
                }
            }
        }
            
        return false;
    }
    
    private static boolean testVertical(Point p1, Point p2, Point p3, Point p4) {
        if (p1.isVertical(p2)) {
            if (p1.isVertical(p3)) {
                if (p1.isVertical(p4)) {
              
                    return true;
            
                }
            }
        }
            
        return false;
    }
    
    private static boolean testDegenerate(Point p1, Point p2, Point p3) {
  
        double k12 = p1.slopeTo(p2);
        double k13 = p1.slopeTo(p3);      
        
        if (k12 == k13) {
            return true;
        }
        
        return false;
    }
    
    private static boolean testDegenerate(Point p1, Point p2, Point p3, Point p4) {
  
        double k12 = p1.slopeTo(p2);
        double k13 = p1.slopeTo(p3);
        double k14 = p1.slopeTo(p4);        
        
        if ((k12 == k13) && (k12 == k14) && (k13 == k14)) {
            return true;
        }
        
        return false;
    }
    
    
    
    public static void main(String[] args) {
        if (args.length != 1) {
            throw new IllegalArgumentException("Wrong number of arguments");
        }
        
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
        
        for (int i = 0; i < N; i++) {
            
            for (int j = i + 1; j < N; j++) {
                
                for (int k = j + 1; k < N; k++) {
                    
                    Point p1 = points[i];
                    Point p2 = points[j];
                    Point p3 = points[k];
                                    
                    if (!testDegenerate(p1, p2, p3)) {
                         continue;
                    }    
                    
                     for (int l = k + 1; l < N; l++) {
 
                         Point p4 = points[l];
         
                         if (testHorizontal(p1, p2, p3, p4)) {
                             print(p1, p2, p3, p4);
                             continue;
                         }
                             

                         if (testVertical(p1, p2, p3, p4)) {
                             print(p1, p2, p3, p4);
                             continue;
                         }
                         
                         if (testDegenerate(p1, p2, p3, p4)) {
                            print(p1, p2, p3, p4);
                         }     
                    }
                } // end for k
            } // end for j
        } // end for i
   
       
        // display to screen all at once
        StdDraw.show(0);

        // reset the pen radius
        StdDraw.setPenRadius();
    
    }
}