public class Quick {
    
    private Quick() { }
    
    private static boolean less(Comparable v, Comparable w) {
        return (v.compareTo(w) < 0);
    }
    
    private static void exch(Object[] a, int i, int j) {
        Object t = a[i]; a[i] = a[j]; a[j] = t;
    }
    
    private static void show(Comparable[] a) {
        for (int i = 0; i < a.length; i++) {
            StdOut.print(a[i] + " ");
        }
        StdOut.println();
    }
    
    public static int partition(Comparable[] a, int lo, int hi) {
        int i = lo, j = hi + 1;
        Comparable v = a[lo];
        while (true) {
            while (less(a[++i], v)) if (i == hi) break;
            while (less(v, a[--j])) if (j == lo) break;
            if (i >= j) break;
            exch(a, i, j);
        }
        exch(a, lo, j);
        return j;
    }
        
    // 3-way quicksort
    private void quicksort(Comparable[] a, int lo, int hi) {
        if (hi <= lo) return;
        int lt = lo, i = lo + 1, gt = hi;
        Comparable v = a[lo];
        while (i <= gt) {
            int cmp = a[i].compareTo(v);
            if (cmp < 0) exch(a, lt++, i++);
            else if (cmp > 0) exch(a, i, gt--);
            else i++;
        }
        
        quicksort(a, lo, lt - 1);
        quicksort(a, gt + 1, hi);
    }
    
    public static void main(String[] args) {
        //String[] a = {"A", "A", "B", "A", "B", "A", "B", "A", "A", "A", "A", "B"};
        
        String[] a = {"86", "14", "37", "23", "81", "97", "92", "43", "69", "21", "28", "83"};
        show(a);
        int lo = 0, hi = a.length - 1;
        int k = partition(a, lo, hi);
        show(a);
    }
}