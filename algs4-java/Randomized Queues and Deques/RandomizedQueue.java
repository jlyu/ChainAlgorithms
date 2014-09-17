// http://coursera.cs.princeton.edu/algs4/assignments/queues.html

import java.util.Iterator;
import java.util.NoSuchElementException;

public class RandomizedQueue<Item> implements Iterable<Item> {
    
    private int N;
    private Node head;
    private class Node {
        Item item;
        Node next;
    }
    
    // construct an empty randomized queue
    public RandomizedQueue() {
        head = new Node();
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
    public void enqueue(Item item){}     
    
    // delete and return a random item
    public Item dequeue(){ return head.item; }                
    
    // return (but do not delete) a random item
    public Item sample(){ return head.item; }                     
    
    // return an independent iterator over items in random order
    public Iterator<Item> iterator() {
        return new ListIterator();
    }         
    
    // unit testing
    public static void main(String[] args){}   
}