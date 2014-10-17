public class Solver {
    private MinPQ<SearchNode> initPQ;
    private MinPQ<SearchNode> twinPQ;
    private boolean solvable;
    private SearchNode finalBoard;
    private class SearchNode implements Comparable<SearchNode> {
        private Board board;
        private int moves;
        private SearchNode prev;

        public SearchNode(Board b, int m, SearchNode sn) {
            board = b;
            moves = m;
            prev = sn;
        }

        public int compareTo(SearchNode other) {
            int thisManhattan = this.board.manhattan() + this.moves;
            int otherManhattan = other.board.manhattan() + other.moves;
            return thisManhattan - otherManhattan;
        }
    }
    
    // find a solution to the initial board (using the A* algorithm)
    public Solver(Board initial) {
        initPQ = new MinPQ<SearchNode>();
        twinPQ = new MinPQ<SearchNode>();
        initPQ.insert(new SearchNode(initial, 0, null));
        twinPQ.insert(new SearchNode(initial.twin(), 0, null));
        SearchNode initSN;
        SearchNode twinSN;
        while (true) {
            initSN = initPQ.delMin();
            twinSN = twinPQ.delMin();

            if (initSN.board.isGoal()) {
                finalBoard = initSN;
                solvable = true;
                break;
            }
            if (twinSN.board.isGoal()) {
                finalBoard = twinSN;
                solvable = false;
                break;
            }
            for (Board initBoard : initSN.board.neighbors()) {
                if (initSN.prev == null || !initBoard.equals(initSN.prev.board))
                    initPQ.insert(new SearchNode(initBoard, initSN.moves + 1, 
                    initSN));
            }
            for (Board twinBoard : twinSN.board.neighbors()) {
                if (twinSN.prev == null || !twinBoard.equals(twinSN.prev.board))
                    twinPQ.insert(new SearchNode(twinBoard, twinSN.moves + 1, 
                    twinSN));
            }
        }
    }
    
    // is the initial board solvable?
    public boolean isSolvable() {
        return solvable;
    }
    
    // min number of moves to solve initial board; -1 if unsolvable
    public int moves() {
        if (this.solvable)
            return finalBoard.moves;
        return -1;
    }
    
    // sequence of boards in a shortest solution; null if unsolvable
    public Iterable<Board> solution() {
        if (this.solvable) {
            
            Stack<Board> s = new Stack<Board>();
            SearchNode curr = finalBoard;
            while (curr != null) {
                s.push(curr.board);
                curr = curr.prev;
            }
            return s;
        }
        return null;
    }
        
    
    // solve a slider puzzle (given below)
    public static void main(String[] args) { // unit tests (not graded)

        // create initial board from file
        In in = new In(args[0]);
        int N = in.readInt();
        int[][] blocks = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
            
                blocks[i][j] = in.readInt();
            }
        }
        
        Board initial = new Board(blocks);

        // solve the puzzle
        Solver solver = new Solver(initial);

        // print solution to standard output
        if (!solver.isSolvable())
            StdOut.println("No solution possible");
        else {
            StdOut.println("Minimum number of moves = " + solver.moves());
            for (Board board : solver.solution())
                StdOut.println(board);
        }
    }
}