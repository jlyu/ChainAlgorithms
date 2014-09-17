// http://coursera.cs.princeton.edu/algs4/assignments/queues.html

import java.util.Iterator;
import java.util.NoSuchElementException;

public class Deque<Item> implements Iterable<Item> {
    
    private int N;
    private Node head;
    private Node tail;
    private class Node {
        Item item;
        Node prev; // left
        Node next; // right
    }

    // construct an empty deque
    public Deque() {
        //origin = new Node();
        head = new Node();
        tail = new Node();
        N = 0;
    }
   
    // is the deque empty?
    public boolean isEmpty() {
        return (N == 0);
    }
    
    // return the number of items on the deque
    public int size() {
        return N;
    }
    
    // insert the item at the front
    public void addFirst(Item item) {
        if (item == null) {
            throw new NullPointerException();
        }
        
        if (isEmpty()) {

            tail.item = item;
            tail.next = head;

            head.prev = tail;
            head.next = null;

        } else {
            Node oldNode = head;
            oldNode.item = item;
            
            head = new Node();
            head.next = null;
            head.prev = oldNode;
       
            oldNode.next = head;
        }
        N++;
    }
    
    // insert the item at the end
    public void addLast(Item item) {
        if (item == null) {
            throw new NullPointerException();
        }
                
        if (isEmpty()) {
            
            tail.item = item;
            tail.next = head;
            head.prev = tail;
            head.next = null;
        } else {
            Node oldNode = tail;
            tail = new Node();
            tail.item = item;
            tail.prev = null;
            tail.next = oldNode;
            oldNode.prev = tail;
        }
        N++;
    }
    
    // delete and return the item at the front
    public Item removeFirst() {
        if (isEmpty()) {
            StdOut.println("deque is empty now");
            throw new NoSuchElementException("deque underflow");
        }
        Item item = head.prev.item;
        head = head.prev;
        N--;
        
        if (isEmpty()) {
            tail = null;
            head = null;
        }
       
        return item;
    }
    
    // delete and return the item at the end
    public Item removeLast() {
        if (isEmpty()) {
            throw new NoSuchElementException("deque underflow");
        }
        
        Item item = tail.item;
        tail = tail.next;
        N--;
        
        if (isEmpty()) {
            tail = null;
            head = null;
        }
       
        return item;
    }
    
    // return an iterator over items in order from front to end
    public Iterator<Item> iterator() {
        return new ListIterator();
    }
    
    private class ListIterator implements Iterator<Item> {
        
        private Node current = tail;
        
        public void remove() { 
            throw new UnsupportedOperationException();  
        }
        
        public boolean hasNext() {
            return current != null && current.item != null;
        }
        
        public Item next() {
            if (!hasNext() && current != head) {
                throw new NoSuchElementException();
            }
            
            Item item = current.item;
            current = current.next; 
            return item;
        }
    }
    
    private void print() {
        for(Item s: this) {
            StdOut.print(s + " ");
        }
    }
    
   
    // unit testing 
    public static void main(String[] args) {
        Deque<String> q = new Deque<String>();
        //StdOut.println("(" + q.size() + " left on queue)");
        while (!StdIn.isEmpty()) {
            
            String item = StdIn.readString();
            
            if (!item.equals("-")) {
               
               //q.addFirst(item);
               q.addLast(item); 
               q.print();
            } else if (!q.isEmpty()) {
               //StdOut.print(q.removeFirst() + " "); // removeLast()
               StdOut.print(q.removeLast() + " "); // removeLast()
            }
        }
        StdOut.println("(" + q.size() + " left on queue)");
    }

}