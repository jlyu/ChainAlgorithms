public class Board {
    private final int[][] board;  
    private final int N;
    private int emptyRow;
    private int emptyCol;
    
    // construct a board from an N-by-N array of blocks
    // (where blocks[i][j] = block in row i, column j)
    public Board(int[][] blocks) {
        N = blocks.length;
        board = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (blocks[i][j] == 0) {
                    emptyRow = i;
                    emptyCol = j;
                }
                board[i][j] = blocks[i][j];
            }
        }
    }
    
    // board dimension N                                       
    public int dimension() {
        return N;
    }
    
    // number of blocks out of place
    public int hamming() {
        int total = 0;  
        for (int i = 0; i < N; i++) {  
            for (int j = 0; j < N && i + j < 2 * N - 2; j++) {  
                if (board[i][j] != i*N + j + 1) {  
                    total++;  
                }  
            }  
        }  
        return total;  
    }
    
    // sum of Manhattan distances between blocks and goal
    public int manhattan() {
        int total = 0;  
        for (int i = 0; i < N; i++) {  
            for (int j = 0; j < N; j++) {  
                if (board[i][j] != 0) {  
                    total += Math.abs((board[i][j] - 1) % N - j) 
                        + Math.abs((board[i][j] - 1) / N - i);  
                }  
            }  
        }  
        return total; 
    }
    
    // is this board the goal board?
    public boolean isGoal() {
        return this.hamming() == 0;
    }
    
    // a boadr that is obtained by exchanging two adjacent blocks in the same row
    public Board twin() {

        Board twinBoard = new Board(this.copy());
        // Switch row 1 if there's an empty block in first blocks of row 0
        if (board[0][0] == 0 || board[0][1] == 0) {
            twinBoard.swap(1, 0, 1, 1);
        }   
        // Switch row 0 if there's no empty block in first blocks of row 0
        else {
            twinBoard.swap(0, 0, 0, 1);
        }
        return twinBoard;
    }
    
    // does this board equal y?
    public boolean equals(Object y) {
        if (y == this) return true;
        if (y == null) return false;
        if (y.getClass() != this.getClass()) return false;
        Board that = (Board) y;
        if (that.N != this.N) return false;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (that.board[i][j] != this.board[i][j])
                    return false;
            }
        }
        return true;
    }
    
    // all neighboring boards
    public Iterable<Board> neighbors() {
        Queue<Board> q = new Queue<Board>();
        Board copy;
        // Swap with upper block (row-1)
        if (emptyRow > 0) {
            copy = new Board(this.copy());
            copy.swap(emptyRow, emptyCol, emptyRow-1, emptyCol);
            q.enqueue(copy);
        }
        // Swap with lower block (row+1)
        if (emptyRow < N-1) {
            copy = new Board(this.copy());
            copy.swap(emptyRow, emptyCol, emptyRow+1, emptyCol);
            q.enqueue(copy);
        }
        // Swap with left block (col-1)
        if (emptyCol > 0) {
            copy = new Board(this.copy());
            copy.swap(emptyRow, emptyCol, emptyRow, emptyCol-1);
            q.enqueue(copy);
        }
        // Swap with right block (col+1)
        if (emptyCol < N-1) {
            copy = new Board(this.copy());
            copy.swap(emptyRow, emptyCol, emptyRow, emptyCol+1);
            q.enqueue(copy);
        }
        return q;
    }
    
    // string representation of this board (in the output format specified below)
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(N + "\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                s.append(String.format("%2d ", board[i][j]));
            }
            s.append("\n");
        }
        return s.toString();
    }
    
    private int[][] copy() {
        int[][] copy = new int[N][N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                copy[i][j] = board[i][j];
        return copy;
    }

    private void swap(int r1, int c1, int r2, int c2) {
        int tmp = board[r1][c1];
        board[r1][c1] = board[r2][c2];
        board[r2][c2] = tmp;
        
        if (board[r1][c1] == 0) {
            emptyRow = r1;
            emptyCol = c1;
        }
        if (board[r2][c2] == 0) {
            emptyRow = r2;
            emptyCol = c2;
        }
    }
    
    // unit tests (not graded)
    public static void main(String[] args) {
    }
        
}