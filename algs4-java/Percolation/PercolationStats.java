public class PercolationStats {
   
   private static In _in;
   private static boolean _fileSource;
   private static int[] _datas;
   
   private Percolation _p;
   private int _openCounter;
   private double[] _thresholds;
   private int _T;
    
   // perform T independent computational experiments on an N-by-N grid
   public PercolationStats(int N, int T) {
       _T = T;
       _thresholds = new double[T];
       
       if (N <= 0 || T <= 0) {
           throw new  java.lang.IllegalArgumentException("N <= 0 or T <= 0");
       }

       for (int t = 1; t <= T; t++) {
           
           _p = new Percolation(N);
           _openCounter = 0;
           
           int datasIndex = 1;   
           while (!_p.percolates()) {
           
               int i = 0;
               int j = 0;
               
               if (_fileSource) {
                   
                   if (datasIndex < _datas.length) {
                      
                       i = _datas[datasIndex];
                       j = _datas[datasIndex + 1];
                       datasIndex += 2;
                    
                   }
                   
               } else {
                    i = (int) (Math.random() * N + 1);
                    j = (int) (Math.random() * N + 1); 
               }
              
           
               if (!_p.isOpen(i, j)) {
                   
                   _openCounter++;
                   // StdOut.println("open: " + i + ", " + j);
           
                   _p.open(i, j);
               }
           }

           _thresholds[t-1] = _openCounter / (double) (N * N);
       }
   }
   
   // sample mean of percolation threshold
   public double mean() {
       double result = 0.0;
       for (int t = 0; t < _T; t++) {
           result += _thresholds[t];
       }
       return result / (double) (_T);
   }
   
   // sample standard deviation of percolation threshold
   public double stddev() {
       if (_T == 1) {
           return Double.NaN;
       } 
              
       double miu = mean();
       double result = 0.0;
       for (int t = 0; t < _T; t++) {
           result += (_thresholds[t] - miu) * (_thresholds[t] - miu);
       }
       result = Math.sqrt(result / (double) (_T-1));

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
       
       int N = 0;
       int T = 0;
       
       if (args.length == 1) {
           
           _fileSource = true;
           _in = new In(args[0]);
           _datas = _in.readAllInts();
           N = _datas[0];
           T = 1;
       }
 
       if (args.length == 2) {
       
           _fileSource = false;
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