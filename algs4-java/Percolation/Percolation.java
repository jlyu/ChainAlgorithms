public class Percolation {
    
   private WeightedQuickUnionUF sites;
   private boolean[] openSites;
   private int N;
    
   // create N-by-N grid, with all sites blocked
   public Percolation(int N) {
       if (N <= 0) {
           throw new  java.lang.IllegalArgumentException("N cannot <= 0");
       }
       
       this.N = N;
       sites = new WeightedQuickUnionUF(N * N);
       openSites = new boolean[N * N];
       for (int i = 0; i < N * N; i++) {
            openSites[i] = false;
       }
   }
       
   // open site (row i, column j) if it is not already
   public void open(int i, int j) { // range of i and j: [1, N]
       if ((i < 1 || i > this.N) || (j < 1 || j > this.N)) {
           throw new IndexOutOfBoundsException("index i or j out of bounds");
       }
       
       int offsetI = i - 1;
       int offsetJ = j - 1;
       
       int p = offsetI * this.N + offsetJ;
       
       if (!isOpen(i, j)) {
           openSites[p] = true;
       }
       
       // up
       if (offsetI > 0) {
           if (isOpen(i - 1, j)) {
               int q = (offsetI - 1) * this.N + offsetJ;
               sites.union(p, q);
           }
       }
       
       // down
       if (offsetI < this.N - 1) {
           int q = (offsetI + 1) * this.N + offsetJ;
           if (isOpen(i + 1, j)) {
               sites.union(p, q);
           }
       }
       
       // left
       if (offsetJ > 0) {
           int q = offsetI * this.N + offsetJ - 1;
           if (isOpen(i, j - 1)) {
               sites.union(p, q);
           }
       }
       
       // right
       if (offsetJ < this.N - 1) {
           int q = offsetI * this.N + offsetJ + 1;
           if (isOpen(i, j + 1)) {
               sites.union(p, q);
           }
       }
   }
   
   // is site (row i, column j) open?
   public boolean isOpen(int i, int j) { // range of i and j: [1, N] 
       if ((i < 1 || i > this.N) || (j < 1 || j > this.N)) {
           throw new IndexOutOfBoundsException("index i or j out of bounds");
       }
       return openSites[(i - 1) * this.N + (j - 1)];
   }
   
   // is site (row i, column j) full?
   public boolean isFull(int i, int j) {
       if ((i < 1 || i > this.N) || (j < 1 || j > this.N)) {
           throw new IndexOutOfBoundsException("index i or j out of bounds");
       }
       
       if (i == 1 && j == 1) {
           return false;
       }
       
       int p = (i-1) * this.N + (j-1);
       for (int q = 0; q < this.N; q++) {
           if (sites.connected(p, q)) {
               return true;
           }
       }
       return false;
   }
   
   // does the system percolate?
   public boolean percolates() {
       for (int t = 1; t <= this.N; t++) { // top
           for (int b = 1; b <= this.N; b++) { //bottom
               int p = t - 1;
               int q = (this.N - 1) * this.N + b - 1;
               if (sites.connected(p, q)) {
                   return true;
               }
           }
       }
       return false;
   }
   
   // test client, optional
   public static void main(String[] args) {
       
       int N = 0;
       int[] datas = new int[1];
       boolean fileSource = false;
       
       if (args.length == 1) {
           boolean isNum = args[0].matches("[0-9]+");
           if (isNum) { 
               N = Integer.parseInt(args[0]);
           } else {
               In in = new In(args[0]);
               datas = in.readAllInts();
               N = datas[0];
               fileSource = true;
           }
       } else {
           N = 20;   
       }
       
       Percolation p = new Percolation(N);
       
       int openCounter = 0;
       int i = 0;
       int j = 0;
       int datasIndex = 1;
       while (!p.percolates()) {
           
           if (fileSource) {
               if (datasIndex < datas.length) {
                     
                       i = datas[datasIndex];
                       j = datas[datasIndex + 1];
                       datasIndex += 2;
               } else {
                   
                   StdOut.println("does not percolation");
                   return;
               }
           } else {
               i = (int) (Math.random() * N + 1);
               j = (int) (Math.random() * N + 1); 
           }
           
           
           if (!p.isOpen(i, j)) {
               openCounter++;
               StdOut.println("open: " + i + ", " + j);
           
               p.open(i, j);
              
           }
       }
       
       
       
       StdOut.println("open sites: " + openCounter);
       double threshold = openCounter / (double) (N *N);
       StdOut.println(threshold);
   }
       
}