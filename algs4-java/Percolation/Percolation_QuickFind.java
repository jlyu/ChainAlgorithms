/*
start [100] times 
mean                    = 0.5931160000000001 
stddev                  = 0.009698662236711727 
mean                    = 0.5931160000000001 
95% confidence interval = 0.5912150622016046, 0.5950169377983956 
177.28 s
 */

public class Percolation {
    
   private QuickFindUF _sites;
   private boolean[] _openSites;
   private int _N;
    
   // create N-by-N grid, with all sites blocked
   public Percolation(int N) {
       _N = N;
       _sites = new QuickFindUF(N * N);
       _openSites = new boolean[N * N];
       for (int i = 0; i < N * N; i++) {
            _openSites[i] = false;
       }
   }
       
   // open site (row i, column j) if it is not already
   public void open(int i, int j) { // i,j both 1~N
       
       int i_ = i - 1;
       int j_ = j - 1;
       
       int p = i_ * _N + j_;
       
       if (!isOpen(i_, j_)) {
           _openSites[p] = true;
       }
       
       // up
       if(i_ > 0) {
           if(isOpen(i_ - 1, j_)) {
               int q = (i_ - 1) * _N + j_;
               _sites.union(p, q);
           }
       }
       
       // down
       if(i_ < _N - 1) {
           int q = (i_ + 1) * _N + j_;
           if(isOpen(i_ + 1, j_)) {
               _sites.union(p, q);
           }
       }
       
       // left
       if(j_ > 0) {
           int q = i_ * _N + j_ - 1;
           if(isOpen(i_, j_ - 1)) {
               _sites.union(p, q);
           }
       }
       
       // right
       if(j_ < _N - 1) {
           int q = i_ * _N + j_ + 1;
           if(isOpen(i_, j_ + 1)) {
               _sites.union(p, q);
           }
       }
   }
   
   // is site (row i, column j) open?
   public boolean isOpen(int i, int j) {
       return _openSites[i * _N + j];
   }
   
   // is site (row i, column j) full?
   public boolean isFull(int i, int j) {
       int p = i * _N + j;
       for(int q=0; q<_N; q++) {
           if(_sites.connected(p, q)) {
               return true;
           }
       }
       return false;
   }
   
   // does the system percolate?
   public boolean percolates() {
       for(int t=1; t<=_N; t++) { // top
           for(int b=1; b<=_N; b++) { //bottom
               int p = t - 1;
               int q = (_N - 1) * _N + b - 1;
               if(_sites.connected(p, q)) {
                   return true;
               }
           }
       }
       return false;
   }
   
   // test client, optional
   public static void main(String[] args) {
       StdOut.println("start testing.."); 
        
       int N = 20;
       Percolation p = new Percolation(N);
       
       int openCounter = 0;
       while(true) {
           
           int i = (int)(Math.random() * N + 1);
           int j = (int)(Math.random() * N + 1); 
           
           if (!p.isOpen(i-1, j-1)) {
               openCounter++;
               StdOut.println("open: " + i + ", " + j);
           
               p.open(i, j);
               
               if(p.percolates()){
                   break;
               }
           }
       }
       
       StdOut.println("open counter: " + openCounter);
       double threshold = openCounter / (double)(N *N);
       StdOut.println(threshold);
   }
       
}