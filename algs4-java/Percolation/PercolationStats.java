public class PercolationStats {
   
   private static In in;
   private static boolean fileSource;
   private static int[] datas;
   
   private Percolation p;
   private int openCounter;
   private double[] thresholds;
   private int runTimes;
    
   // perform T independent computational experiments on an N-by-N grid
   public PercolationStats(int N, int T) {
       runTimes = T;
       thresholds = new double[T];
       
       if (N <= 0 || T <= 0) {
           throw new  java.lang.IllegalArgumentException("N <= 0 or T <= 0");
       }

       for (int t = 1; t <= T; t++) {
           
           p = new Percolation(N);
           openCounter = 0;
           
           int datasIndex = 1;   
           while (!p.percolates()) {
           
               int i = 0;
               int j = 0;
               
               if (fileSource) {
                   
                   if (datasIndex < datas.length) {
                      
                       i = datas[datasIndex];
                       j = datas[datasIndex + 1];
                       datasIndex += 2;
                    
                   }
                   
               } else {
                    i = (int) (Math.random() * N + 1);
                    j = (int) (Math.random() * N + 1); 
               }
              
           
               if (!p.isOpen(i, j)) {
                   
                   openCounter++;
                   // StdOut.println("open: " + i + ", " + j);
           
                   p.open(i, j);
               }
           }

           thresholds[t-1] = openCounter / (double) (N * N);
       }
   }
   
   // sample mean of percolation threshold
   public double mean() {
       double result = 0.0;
       for (int t = 0; t < runTimes; t++) {
           result += thresholds[t];
       }
       return result / (double) (runTimes);
   }
   
   // sample standard deviation of percolation threshold
   public double stddev() {
       if (runTimes == 1) {
           return Double.NaN;
       } 
              
       double miu = mean();
       double result = 0.0;
       for (int t = 0; t < runTimes; t++) {
           result += (thresholds[t] - miu) * (thresholds[t] - miu);
       }
       result = Math.sqrt(result / (double) (runTimes - 1));

       return result;
   }
   
   // returns lower bound of the 95% confidence interval
   public double confidenceLo() {
       double miu = mean();
       double sd = stddev();
       double result = miu - ((1.96 * sd) / (Math.sqrt(runTimes)));
       return result;
   }
   
   // returns upper bound of the 95% confidence interval
   public double confidenceHi() {
       double miu = mean();
       double sd = stddev();
       double result = miu + ((1.96 * sd) / (Math.sqrt(runTimes)));
       return result;
   }
   
   
   // test client, described below
   public static void main(String[] args) {
       
       Stopwatch watch = new Stopwatch();
       
       int N = 0;
       int T = 0;
       
       if (args.length == 1) {
           
           fileSource = true;
           in = new In(args[0]);
           datas = in.readAllInts();
           N = datas[0];
           T = 1;
       }
 
       if (args.length == 2) {
       
           fileSource = false;
           N = Integer.parseInt(args[0]);
           T = Integer.parseInt(args[1]);
       } 
       
       PercolationStats p = new PercolationStats(N, T);
       StdOut.println("mean                    = " + p.mean());
       StdOut.println("stddev                  = " + p.stddev());
       StdOut.println("mean                    = " + p.mean());
       StdOut.println("95% confidence interval = " + p.confidenceLo() 
                          + ", " + p.confidenceHi());
       
       StdOut.println(watch.elapsedTime());
   }
}