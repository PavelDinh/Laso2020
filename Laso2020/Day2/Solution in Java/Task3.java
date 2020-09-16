package day2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;

public class Task3 {
    public static void main(String[] args) throws IOException {
//        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedReader br = Files.newBufferedReader(Paths.get("seq.txt"));
        System.setOut(new PrintStream(Files.newOutputStream(Paths.get("task3.out"),
                StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING,
                StandardOpenOption.CREATE)));
        
        Stack stack = new Stack(4);
        System.err.println("task 3");
        
        String line;
        while((line = br.readLine()) != null) {
            if(line.equals("remove")) {
                System.out.println(stack.remove());
            } else if(line.startsWith("insert")) {
                // do operation insert
                final int value = Integer.parseInt(line.substring(7));
                stack.insert(value);
            }
        }
    }
}

class Stack {
    private int[] array;
    private int size;
    
    public Stack(int initialCapacity) {
        initialCapacity = Math.max(initialCapacity, 4);
        array = new int[initialCapacity];
        size = 0;
    }
    
    public void insert(int n) {
        // ensure that we have enough space
        if(array.length <= size) {
            int[] tmp = new int[array.length * 2];
            System.arraycopy(array, 0, tmp, 0, array.length);
            array = tmp;
        }
        
        // add the element
        array[size] = n;
        size++;
    }
    
    public int remove() {
        size--;
        return array[size];
    }
}
