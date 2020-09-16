package day2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Deque;
import java.util.LinkedList;

public class Task5 {

    public static void main(String[] args) throws IOException {
//        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedReader br = Files.newBufferedReader(Paths.get("seq.txt"));
        System.setOut(new PrintStream(Files.newOutputStream(Paths.get("task5.out"),
                StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING,
                StandardOpenOption.CREATE)));

        Deque<Integer> queue = new LinkedList<>();
        System.err.println("task 5");

        String line;
        while ((line = br.readLine()) != null) {
            if (line.equals("remove")) {
                System.out.println(queue.removeLast());
            } else if (line.startsWith("insert")) {
                // do operation insert
                final int value = Integer.parseInt(line.substring(7));
                queue.addFirst(value);
            }
        }
    }
}

class Queue {

    private Node head = null;
    private Node tail = null;

    public void insert(int n) {
        final Node newNode = new Node(n);

        if (tail != null) { // queue is not empty
            tail.next = newNode;
        } else // queue is empty
        {
            head = newNode;
        }

        tail = newNode;
    }

    public int remove() {
        final int retval = head.value;

        head = head.next;
        if (head == null) // we emptied the queue
        {
            tail = null;
        }
        return retval;
    }
}

class Node {

    final int value;
    Node next;

    public Node(int value) {
        this.value = value;
    }
}
