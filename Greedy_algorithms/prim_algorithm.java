import java.util.*;

public class prim_algorithm {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n = 6;  // 정점의 개수
        int[][] graph = new int[n][n];  // 인접 행렬

        System.out.println("◎ Enter the edges ◎");
        for (int i = 0; i < 10; i++) {
            System.out.print("→  edge " + (i + 1) + ": ");
            char vertex1 = scanner.next().charAt(0); 
            char vertex2 = scanner.next().charAt(0);
            int weight = scanner.nextInt();  

            int v1 = vertex1 - 'a'; 
            int v2 = vertex2 - 'a';

            // 인접 행렬에 간선 저장
            graph[v1][v2] = weight;
            graph[v2][v1] = weight;
        }

        System.out.print("◎ Enter the starting vertex: ");
        char start_vertex_char = scanner.next().charAt(0);
        int start_vertex = start_vertex_char - 'a'; 

        System.err.println("\n◎ Prim Minimum Spanning Tree edges:");
        long start = System.nanoTime();
        prim(graph, n, start_vertex); 
        long end = System.nanoTime(); 

        long prim_running_time = end - start;
        System.out.println("\n◎ Prim running time: " + prim_running_time + " ns");
        scanner.close();
    }

    public static void prim(int[][] graph, int n, int start_vertex) {
        int[] D = new int[n];  // 각 정점에 연결된 최소 가중치 간선
        boolean[] inTree = new boolean[n];  // 트리에 속한 정점 여부
        int[] parent = new int[n];  // 최소 신장 트리에서 각 정점의 부모
        Arrays.fill(D, Integer.MAX_VALUE);  // D 배열을 무한대로 초기화
        D[start_vertex] = 0;  // 시작 정점의 가중치는 0으로 설정
        parent[start_vertex] = -1;  // 시작 정점은 부모가 없음

        for (int i = 0; i < n; i++) {
            // 트리에 속하지 않은 정점 중 최소 가중치를 가진 정점을 선택
            // 시작점을 제외한 D는 모두 무한대이므로 첫 루프는 시작 정점이 선택됨 c->( D=[∞,∞,0,∞,∞,∞] )
            int u = -1;
            for (int v = 0; v < n; v++) {
                if (!inTree[v] && (u == -1 || D[v] < D[u])) {
                    u = v;
                }
            }

            // 최소 가중치 간선을 트리에 추가
            inTree[u] = true;

            // 연결된 간선 출력
            if (parent[u] != -1) {
                System.out.println("→  (" + parent[u] + ", " + u + ", " + D[u] + ")");
            }

            // u에 연결된 다른 정점의 간선을 확인하고 최소 가중치 갱신
            for (int v = 0; v < n; v++) {
                if (graph[u][v] != 0 && !inTree[v] && graph[u][v] < D[v]) {
                    D[v] = graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }
}
