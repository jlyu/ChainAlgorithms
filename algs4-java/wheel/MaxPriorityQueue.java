public class MaxPriorityQueue<Key extends Comparable<Key>> {
    
    private Key[] pq;
    private int N;
    
    public MaxPriorityQueue(int maxN) {
        pq = (Key[]) new Comparable[maxN + 1];
        N = 0;
    }
    
    private void resize(int capacity) {
        assert capacity > N;
        Key[] temp = (Key[]) new Object[capacity];
        for (int i = 1; i <= N; i++) temp[i] = pq[i];
        pq = temp;
    }
    
    public boolean isEmpty() { return N == 0; }
    public int size() { return N; }
    
    private boolean less(int i, int j) {
        return ((Comparable<Key>) pq[i]).compareTo(pq[j]) < 0;
    }
    
    private void exch(int i, int j) {
        Key swap = pq[i]; pq[i] = pq[j]; pq[j] = swap;
    }
    
    private void swim(int k) {
        while (k > 1 && less(k/2, k)) {
            exch(k, k/2);
            k = k/2;
        }
    }
        
    private void sink(int k) {
        while (2*k <= N) {
            int j = 2 * k;
            if (j < N && less(j, j+1)) { j++; }
            if (!less(k, j)) { break; }
            exch(k, j);
            k = j;
        }
    }
    
    public void insert(Key v) {
        
        if (N >= pq.length - 1) resize(2 * pq.length);
        
        pq[++N] = v;
        swim(N);
    }
    
    public Key delMax() {
        Key max = pq[1];
        exch(1, N--);
        pq[N+1] = null;
        sink(1);
        return max;
    }
    
    public void show() {
        for (int i=1; i <= N; i++) {
            StdOut.print(pq[i] + " ");
        }
        StdOut.println();
    }
    
    
    public static void main(String[] args) {
        // unit test

        Integer[] a = {98,68,87,42,58,14,33,35,36,12}; 
        
        MaxPriorityQueue<Integer> pq = new MaxPriorityQueue<Integer>(a.length + 4);
        for (int i=0; i<a.length; i++) {
            pq.insert(a[i]);
        }
        
        
        pq.delMax();pq.delMax();pq.delMax();
        
        pq.show();
        
    }
    
}