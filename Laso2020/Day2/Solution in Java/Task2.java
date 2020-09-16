package day2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;

public class Task2 {
    public static void main(String[] args) throws IOException {
//        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedReader br = Files.newBufferedReader(Paths.get("seq.txt"));
        System.setOut(new PrintStream(Files.newOutputStream(Paths.get("task2.out"),
                StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING,
                StandardOpenOption.CREATE)));
        
        ArrayList<Integer> stack = new ArrayList<>();
        
        String line;
        while((line = br.readLine()) != null) {
            if(line.equals("remove")) {
                System.out.println(stack.remove(stack.size() - 1));
            } else if(line.startsWith("insert")) {
                // do operation insert
                final int value = Integer.parseInt(line.substring(7));
                stack.add(value);
            }
        }
    }
}
