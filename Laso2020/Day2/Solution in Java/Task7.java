package day2;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class Task7 {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.setOut(new PrintStream(Files.newOutputStream(Paths.get("task7.out"),
                StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING,
                StandardOpenOption.CREATE)));
        Graph g = Graph.load("graph.txt");
        System.err.println("task7");
        
        System.out.println("We can visit "+bfs(g, 0)+" vertices.");

    }
    
    public static int bfs(Graph g, int s) {
        int count = 0;
        Deque<Integer> q = new LinkedList<>();
        boolean[] visited = new boolean[g.N];
        q.addLast(s);
        visited[s] = true;
        while(!q.isEmpty()) {
            final int v = q.removeFirst();
            System.out.println(Integer.toString(v));
            count++;
            for(int w : g.edges.get(v)) {
                if(!visited[w]) {
                    visited[w] = true;
                    q.addLast(w);
                }
            }
        }
        return count;
    }
}

class Graph {
// ----------------------------------------------------------------------------
//                           M  A  I  N                                      
// ----------------------------------------------------------------------------

// ------------------------- G R A P H   I T S E L F --------------------------  
    int N, E;                                    // # of nodes,  # of edges
    ArrayList< ArrayList<Integer>> edges;       // linked list representation

// ------------------------- C O N S T R U C T O R ----------------------------  
// creates a graph with n nodes and no edges (so called empty graph) 
    public Graph(int n) {
        N = n;
        edges = new ArrayList< ArrayList<Integer>>();
        for (int i = 0; i < n; i++) {
            edges.add(new ArrayList<Integer>());
        }
    }

// ------------------------- A D D   E D G E  ---------------------------------
// mainly for input reading  
    void addedge(int a, int b) {
        edges.get(a).add(b);
        edges.get(b).add(a);
        E++;
    }

// ----------------------------------------------------------------------------
//                              P R I N T
//                     useful for debug purposes 
    void print() {
        for (int node = 0; node < N; node++) {
            System.out.printf("%2d__", node);
            for (int neigh : edges.get(node)) {
                System.out.printf(" %2d", neigh);
            }
            System.out.printf("\n");
        }
        System.out.printf("-------------------- \n");
    }

// ----------------------------------------------------------------------------
//                          L O A D E R
// ----------------------------------------------------------------------------
    static Graph load(String fileName) {
        try {
            BufferedReader br;
            if (fileName == null || fileName.isEmpty()) {
                br = new BufferedReader(new InputStreamReader(System.in));
            } else {
                br = new BufferedReader(new FileReader(fileName));
            }

            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.valueOf(st.nextToken()); // # of nodes
            int m = Integer.valueOf(st.nextToken()); // # of edges

            Graph g = new Graph(n);

            int n1, n2;
            for (int i = 0; i < m; i++) {
                st = new StringTokenizer(br.readLine());
                n1 = Integer.valueOf(st.nextToken());
                n2 = Integer.valueOf(st.nextToken());
                g.addedge(n1, n2);
            }

            br.close();

            return g;
        } catch (IOException eee) {
            System.out.printf(" Excepcion in graph read.\n");
            return null;
        }
    }

// ----------------------------------------------------------------------------
//           D E B U G       U T I L I T I E S
// ----------------------------------------------------------------------------
    public static <T> void list(ArrayList<T> a) {
        for (T x : a) {
            System.out.printf(" %s", x);
        }
        System.out.printf("\n-------------------\n");
    }

    public static void list(int[] a) {
        for (int x : a) {
            System.out.printf(" %s", x);
        }
        System.out.printf("\n-------------------\n");
    }

}
