package day2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Deque;
import java.util.LinkedList;

public class Task8 {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//        System.setOut(new PrintStream(Files.newOutputStream(Paths.get("task8.out"),
//                StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING,
//                StandardOpenOption.CREATE)));
        Graph g = Graph.load("graph.txt");
        System.err.println("task8");
        
        System.out.println("Vertices 0 and 7 are "+bfs(g, 0, 7)+" edges apart.");

    }
    
    public static int bfs(Graph g, int s, int target) {
        Deque<Integer> q = new LinkedList<>();
        boolean[] visited = new boolean[g.N];
        q.addLast(s);
        visited[s] = true;
        int[] dist = new int[g.N];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[s] = 0;
        
        while(!q.isEmpty()) {
            final int v = q.removeFirst();
            for(int w : g.edges.get(v)) {
                if(!visited[w]) {
                    visited[w] = true;
                    q.addLast(w);
                    dist[w] = dist[v] + 1;
                    
                    if(w == target)
                        return dist[w];
                }
            }
        }
        return -1;
    }
}
