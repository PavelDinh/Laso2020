package day2;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;
import java.util.NoSuchElementException;

public class Task16b {

    public static void main(String[] args) throws IOException {
//        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // won't work with this file, because it contains duplicates
        BufferedReader br = Files.newBufferedReader(Paths.get("seq.txt"));
//        System.setOut(new PrintStream(Files.newOutputStream(Paths.get("task16b.out"),
//                StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING,
//                StandardOpenOption.CREATE)));
        System.err.println("task 16b");

        Heap2 pqueue = new Heap2(1000);

        String line;
        while ((line = br.readLine()) != null) {
            if (line.equals("remove")) {
                System.out.println(pqueue.extractMin());
            } else if (line.startsWith("insert")) {
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
final class Heap2 {

    /**
     * Here we will store values that user will add to the heap.
     */
    public final int[] heap;
    /**
     * Here we will store locations of heap elements.
     */
    private final Map<Integer, Integer> position;
    /**
     * The number of elements in the heap.
     */
    int length;

    /**
     * Constructs a new heap that will be capable of storing up to {@code n}
     * elements.
     *
     * @param n The maximum number of elements.
     */
    public Heap2(int n) {
        this.heap = new int[n + 1];
        position = new HashMap<>(n);
        length = 0;
    }

    /**
     * Adds a new element to the heap. If {@code node} is already in the heap,
     * we do nothing.
     *
     * @param node New walue to add.
     */
    public void add(int node) {
        if (position.containsKey(node)) {
            return;
        }

        length++;
        heap[length] = node;
        position.put(node, length);
        bubbleUp(length);
    }

    /**
     * Tests whether this heap is empty.
     *
     * @return {@code true} if there are no elements in the heap.
     */
    public boolean isEmpty() {
        return length == 0;
    }

    /**
     * Obtains the minimum from the heap.
     *
     * @return The minimum.
     */
    public int extractMin() {
        if (isEmpty()) {
            throw new NoSuchElementException("Cannot remove from an empty heap.");
        }

        int retval = heap[1];
        position.remove(retval);
        heap[1] = heap[length];
        position.put(heap[length], 1);
        length--;
        bubbleDown(1);
        return retval;
    }

    /**
     * Finds node {@code node} and replaces it with the new value. This method
     * can be used for decreasing key.
     *
     * @param node The original value.
     * @param newValue Its replacement.
     */
    public void replace(int node, int newValue) {
        if (!position.containsKey(node)) {
            return;
        }

        int pos = position.get(node);
        position.remove(heap[pos]);
        heap[pos] = newValue;
        position.put(newValue, pos);
        
        bubbleUp(pos);
        bubbleDown(pos);
    }

    // you will probably need those private methods
    // however you do not need to strictly follow them, you can design the code
    // yourself
    /**
     * Swaps two values at two particular positions.
     *
     * @param a The first index to swap.
     * @param b The second index.
     */
    private void swap(int a, int b) {
        position.put(heap[a], b);
        position.put(heap[b], a);
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
     *
     * @param pos The position where we should move the node upwards in order to
     * fix the heap property.
     */
    private void bubbleUp(int pos) {
        while (pos > 1 && heap[parent(pos)] > heap[pos]) {
            swap(pos, parent(pos));
            pos = parent(pos);
        }
    }

    /**
     * Bubble up node from a position {@code pos}.
     *
     * @param pos The position where we should move the node downwards in order
     * to fix the heap property.
     */
    private void bubbleDown(int pos) {
        // we don't have a left child
        if (leftChild(pos) > length) {
            return;
        }

        int smallerChild = leftChild(pos);
        // if right child exists and is smaller than the left one
        if (leftChild(pos) + 1 <= length && heap[leftChild(pos) + 1] < heap[smallerChild]) {
            smallerChild = leftChild(pos) + 1;
        }

        // swap if necessary
        if (heap[smallerChild] < heap[pos]) {
            swap(pos, smallerChild);
            bubbleDown(smallerChild);
        }
    }
}
