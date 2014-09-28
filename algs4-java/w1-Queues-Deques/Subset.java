public class Subset {
    
    public static void main(String[] args) {
        RandomizedQueue<String> rq = new RandomizedQueue<String>();
        
        while (!StdIn.isEmpty()) {
            String item = StdIn.readString();
            rq.enqueue(item);
        }
        
        int k = 0;
        if (args.length == 1) {
           boolean isNum = args[0].matches("[0-9]+");
           if (isNum) {
               k = Integer.parseInt(args[0]);
           } else {
               k = rq.size(); 
           }
        }
        
        for (int i = 0; i < k; i++) {
            StdOut.println(rq.dequeue());
        }
    }
}