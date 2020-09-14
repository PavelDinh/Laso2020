package counttriangles;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

/**
 * @author rysavpe1
 */
public class Counttriangles {

    // solution to the problem number 6
    public static void main(String[] args) {
        Graph g = Graph.load("g4_2.in");
        
        // build the adjacency matrix
        final boolean[][] adjMatrix = new boolean[g.N][g.N];
        for(int i = 0; i < g.N; i++)
            for(int j : g.edges.get(i))
                adjMatrix[i][j] = true;
        
        int triangleCount = 0;
        // iterate over all edges
        for(int i = 0; i < g.N; i++)
            for(int j : g.edges.get(i))
                // we have edge from i to j
                // now compare the rows in the adjacency matrix
                if(i < j) // do not count the edge twice
                    for(int k = 0; k < g.N; k++)
                        if(adjMatrix[i][k] && adjMatrix[j][k]) { // we found a triangle i-j-k
                            triangleCount++;
//                            if(j < k) // this makes the triangle visible just once i < j < k
//                                System.err.println("i : "+(i)+" j "+(j) + " k "+(k));
                        }
        
        // we registered each triangle 3-times
        System.out.println(Integer.toString(triangleCount / 3));
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
