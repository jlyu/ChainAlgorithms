public class PercolationStats {
    
   private Percolation _p;
   private int _openCounter;
   private double[] _thresholds;
   private int _T;
    
   // perform T independent computational experiments on an N-by-N grid
   public PercolationStats(int N, int T) {
       
       _T = T;
       _thresholds = new double[T];
       
       if (N <=0 || T<=0) {
           throw new  java.lang.IllegalArgumentException("N <= 0 or T <= 0");
       }

       for(int t = 1; t<=T; t++) {
           
           StdOut.println("start [" + t + "] times");
           _p = new Percolation(N);
           _openCounter = 0;
           
           while(!_p.percolates()) {
           
               int i = (int)(Math.random() * N + 1);
               int j = (int)(Math.random() * N + 1); 
           
               if (!_p.isOpen(i-1, j-1)) {
                   _openCounter++;
                   //StdOut.println("open: " + i + ", " + j);
           
                   _p.open(i, j);
               }
           }

           _thresholds[t-1] = _openCounter / (double)(N * N);
       }
   }
   
   // sample mean of percolation threshold
   public double mean() {
       double result = 0.0;
       for(int t=0; t<_T; t++) {
           result += _thresholds[t];
       }
       return result / (double)(_T);
   }
   
   // sample standard deviation of percolation threshold
   public double stddev() {
       double miu = mean();
       double result = 0.0;
       for(int t=1; t<_T; t++){
           result += (_thresholds[t] - miu)*(_thresholds[t] - miu);
       }
       result = Math.sqrt( result / (double)(_T-1) );
       if(result == 1) {
           return Double.NaN;
       } 
       return result;
   }
   
   // returns lower bound of the 95% confidence interval
   public double confidenceLo() {
       double miu = mean();
       double sd = stddev();
       double result = miu - ((1.96 * sd) / (Math.sqrt(_T)));
       return result;
   }
   
   // returns upper bound of the 95% confidence interval
   public double confidenceHi() {
       double miu = mean();
       double sd = stddev();
       double result = miu + ((1.96 * sd) / (Math.sqrt(_T)));
       return result;
   }
   
   
   // test client, described below
   public static void main(String[] args) {
       
       Stopwatch watch = new Stopwatch();
 
       if(args.length == 2) {
       
           int N = Integer.parseInt(args[0]);
           int T = Integer.parseInt(args[1]);

           PercolationStats p = new PercolationStats(N, T);
           StdOut.println("mean                    = " + p.mean());
           StdOut.println("stddev                  = " + p.stddev());
           StdOut.println("mean                    = " + p.mean());
           StdOut.println("95% confidence interval = " + p.confidenceLo() + 
                          ", " + p.confidenceHi());   
           
       } 
       
       
       StdOut.println(watch.elapsedTime());
   }
}