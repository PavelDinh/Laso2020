package day2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.NoSuchElementException;

public class Task16 {
    public static void main(String[] args) throws IOException {
//        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedReader br = Files.newBufferedReader(Paths.get("seq.txt"));
        System.setOut(new PrintStream(Files.newOutputStream(Paths.get("task16.out"),
                StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING,
                StandardOpenOption.CREATE)));
        System.err.println("task 16");
        
        Heap pqueue = new Heap(1000);
        
        String line;
        while((line = br.readLine()) != null) {
            if(line.equals("remove")) {
                System.out.println(pqueue.extractMin());
            } else if(line.startsWith("insert")) {
                // do operation insert
                final int value = Integer.parseInt(line.substring(7));
                pqueue.add(value);
            }
        }
    }
}


/**
 * This class template should be used to implement heap.
 *
 * @author Petr RyĹˇavĂ˝ <petr.rysavy@fel.cvut.cz>
 */
final class Heap {

    /** Here we will store values that user will add to the heap. */
    public final int[] heap;
    /** The number of elements in the heap. */
    int length;

    /**
     * Constructs a new heap that will be capable of storing up to {@code n}
     * elements.
     * @param n The maximum number of elements.
     */
    public Heap(int n) {
        this.heap = new int[n + 1];
        length = 0;
    }

    /**
     * Adds a new element to the heap.
     * @param node New walue to add.
     */
    public void add(int node) {
        length++;
        heap[length] = node;
        bubbleUp(length);
    }

    /**
     * Tests whether this heap is empty.
     * @return {@code true} if there are no elements in the heap.
     */
    public boolean isEmpty() {
        return length == 0;
    }

    /**
     * Obtains the minimum from the heap.
     * @return The minimum.
     */
    public int extractMin() {
        if(isEmpty())
            throw new NoSuchElementException("Cannot remove from an empty heap.");
        
        int retval = heap[1];
        heap[1] = heap[length];
        length--;
        bubbleDown(1);
        return retval;
    }

    /**
     * Finds node {@code node} and replaces it with the new value. This method
     * can be used for decreasing key.
     * @param node The original value.
     * @param newValue Its replacement.
     */
    public void replace(int node, int newValue) {
        throw new UnsupportedOperationException("Implement yourself.");
    }

    // you will probably need those private methods
    // however you do not need to strictly follow them, you can design the code
    // yourself
    /**
     * Swaps two values at two particular positions.
     * @param a The first index to swap.
     * @param b The second index.
     */
    private void swap(int a, int b) {
        int tmp = heap[a];
        heap[a] = heap[b];
        heap[b] = tmp;
    }
    
    private final int parent(int pos) {
        return pos / 2;
    }
    
    private final int leftChild(int pos) {
        return pos * 2;
    }

    /**
     * Bubble up node from a position {@code pos}.
     * @param pos The position where we should move the node upwards in order to
     * fix the heap property.
     */
    private void bubbleUp(int pos) {
        while(pos > 1 && heap[parent(pos)] > heap[pos]) {
            swap(pos, parent(pos));
            pos = parent(pos);
        }
    }

    /**
     * Bubble up node from a position {@code pos}.
     * @param pos The position where we should move the node downwards in order
     * to fix the heap property.
     */
    private void bubbleDown(int pos) {
        // we don't have a left child
        if(leftChild(pos) > length)
            return;
        
        int smallerChild = leftChild(pos);
        // if right child exists and is smaller than the left one
        if(leftChild(pos) + 1 <= length && heap[leftChild(pos) + 1] < heap[smallerChild])
            smallerChild = leftChild(pos) + 1;
        
        // swap if necessary
        if(heap[smallerChild] < heap[pos]) {
            swap(pos, smallerChild);
            bubbleDown(smallerChild);
        }
    }
}

