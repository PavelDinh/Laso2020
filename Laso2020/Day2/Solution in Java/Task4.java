package day2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Deque;
import java.util.LinkedList;

public class Task4 {

    public static void main(String[] args) throws IOException {
//        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedReader br = Files.newBufferedReader(Paths.get("seq.txt"));
        System.setOut(new PrintStream(Files.newOutputStream(Paths.get("task4.out"),
                StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING,
                StandardOpenOption.CREATE)));

        Deque<Integer> queue = new LinkedList<>();

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
