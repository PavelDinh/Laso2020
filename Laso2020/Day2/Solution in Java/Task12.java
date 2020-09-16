package day2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.PriorityQueue;

public class Task12 {
    public static void main(String[] args) throws IOException {
//        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedReader br = Files.newBufferedReader(Paths.get("seq.txt"));
        System.setOut(new PrintStream(Files.newOutputStream(Paths.get("task12.out"),
                StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING,
                StandardOpenOption.CREATE)));
        System.err.println("task 12");
        
        PriorityQueue<Integer> pqueue = new PriorityQueue<>();
        
        String line;
        while((line = br.readLine()) != null) {
            if(line.equals("remove")) {
                System.out.println(pqueue.remove());
            } else if(line.startsWith("insert")) {
                // do operation insert
                final int value = Integer.parseInt(line.substring(7));
                pqueue.add(value);
            }
        }
    }
}
