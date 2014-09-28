// http://coursera.cs.princeton.edu/algs4/assignments/queues.html

import java.util.Iterator;
import java.util.NoSuchElementException;

public class RandomizedQueue<Item> implements Iterable<Item> {
    
    private int N;
    private Node tail;
    private Node head;
    private class Node {
        private Item item;
        private Node next;
    }
    
    // construct an empty randomized queue
    public RandomizedQueue() {
        head = new Node();
        tail = new Node();
        N = 0;
    }       
    
    // is the queue empty?
    public boolean isEmpty() { 
        return (N == 0); 
    }         
    
    // return the number of items on the queue
    public int size() { 
        return N; 
    }                  
    
    // add the item
    public void enqueue(Item item) {
        
        if (item == null) {
            throw new NullPointerException();
        }
        
        //Node oldNode = head;
        //head = new Node();
        //head.item = item;
        //head.next = null;
        
        if (isEmpty()) {
            //head = oldNode;
            //tail = head; // set start pointer
            tail.item = item;
            tail.next = head;
        } else {
            //oldNode.next = head;
            Node oldNode = head;
            oldNode.item = item;
            
            head = new Node();
            head.next = null;
            //head.prev = oldNode;
       
            oldNode.next = head;
        }
        
        N++;
        
    }     
    
    // delete and return a random item
    public Item dequeue() { 
        
        if (isEmpty()) {
            StdOut.println("deque is empty now");
            throw new NoSuchElementException("deque underflow");
        }
        
        
        if (N == 1) {
            Item item = tail.item;
            head = null;
            tail = null;
            N--;
            return item;
        }
        
        int randomDequeN = (int) (Math.random() * N); // range: 0 ~ N - 1
        Node findDequePointer = tail;
        for (int i = 0; i < randomDequeN - 1; i++) { // range: (1 ~ N-1)
            findDequePointer = findDequePointer.next;
        }
        Node dequeueNode = findDequePointer.next;
        Item dequeueItem = dequeueNode.item;
        findDequePointer.next = dequeueNode.next;
        dequeueNode = null;
        N--;
        
        return dequeueItem;
    }                
    
    // return (but do not delete) a random item
    public Item sample() { 
        
        if (isEmpty()) {
            throw new NoSuchElementException("deque underflow");
        } 
        
        int randomDequeN = (int) (Math.random() * N + 1); // range: 1 ~ N
        Node findDequePointer = tail;
        for (int i = 1; i < randomDequeN - 1; i++) { // range: (1 ~ N-1)
            findDequePointer = findDequePointer.next;
        }
        Node dequeueNode = findDequePointer.next;
        return dequeueNode.item;
    }                     
    
    // return an independent iterator over items in random order
    public Iterator<Item> iterator() {
        return new ListIterator();
    }         
    
    private class ListIterator implements Iterator<Item> {
        
        private int counter = N;
        
        public void remove() { 
            throw new UnsupportedOperationException();  
        }
        
        public boolean hasNext() {
            return counter == 0;
        }
        
        public Item next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
                
            }
            counter--;
            //Item item = current.item;
            //current = current.next; 
            return sample();
        }
    }
    
    // unit testing
    public static void main(String[] args) {
    
    }   
}