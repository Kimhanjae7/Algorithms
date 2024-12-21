import java.util.*;

public class branch_and_bound_algorithm {
    private static final int NUM_VERTEX = 5;

    // 그래프 (정점별 거리)
    private static final int[][] graph = {
        {0, 2, 7, 3, 10},
        {2, 0, 3, 5, 4},
        {7, 3, 0, 6, 1},
        {3, 5, 6, 0, 9},
        {10, 4, 1, 9, 0}
    };

    // 최적 거리와 경로 저장
    private static int best_value = Integer.MAX_VALUE;
    private static List<Integer> best_solution = new ArrayList<>();

    private static class State {
        int cost; // 현재까지의 거리
        List<Integer> path; // 방문 경로 저장
        boolean[] visited; // 방문 여부

        State(int cost, List<Integer> path, boolean[] visited) {
            this.cost = cost;
            this.path = new ArrayList<>(path);
            this.visited = Arrays.copyOf(visited, visited.length);
        }
    }

    // 한정값 계산 
    private static int calculate_bound(State state) {
        int bound = state.cost;

        // 미방문 정점의 최소 비용 합산
        for (int i = 0; i < NUM_VERTEX; i++) {
            if (!state.visited[i]) {
                int min_cost = Integer.MAX_VALUE;
                for (int j = 0; j < NUM_VERTEX; j++) {
                    if (i != j && !state.visited[j] && graph[i][j] < min_cost) {
                        min_cost = graph[i][j];
                    }
                }
                if (min_cost != Integer.MAX_VALUE) {
                    bound += min_cost;
                }
            }
        }

        return (int) Math.ceil(bound / 2.0);
    }

    // Branch and Bound Algorithm
    private static void branch_and_bound() {
        PriorityQueue<State> active_nodes = new PriorityQueue<>(Comparator.comparingInt(s -> s.cost));

        // 초기 상태 S 생성
        List<Integer> initial_path = new ArrayList<>();
        initial_path.add(0); // 시작점 추가
        boolean[] initial_visited = new boolean[NUM_VERTEX];
        initial_visited[0] = true;
        active_nodes.add(new State(0, initial_path, initial_visited));

        // 탐색
        while (!active_nodes.isEmpty()) {
            // active_nodes 중 가장 작은 상태 선택
            State current_state = active_nodes.poll();

            // 현재 상태가 완전한 해인지 확인
            if (current_state.path.size() == NUM_VERTEX) {
                int total_cost = current_state.cost + graph[current_state.path.get(current_state.path.size() - 1)][0]; // 시작점으로 돌아감
                if (total_cost < best_value) {
                    best_value = total_cost;
                    best_solution = new ArrayList<>(current_state.path);
                }
                continue;
            }

            // 자식 상태 생성
            int last_vertex = current_state.path.get(current_state.path.size() - 1);
            for (int next_vertex = 0; next_vertex < NUM_VERTEX; next_vertex++) {
                if (!current_state.visited[next_vertex] && graph[last_vertex][next_vertex] != Integer.MAX_VALUE) {
                    int new_cost = current_state.cost + graph[last_vertex][next_vertex];

                    List<Integer> new_path = new ArrayList<>(current_state.path);
                    new_path.add(next_vertex);
                    boolean[] new_visited = Arrays.copyOf(current_state.visited, NUM_VERTEX);
                    new_visited[next_vertex] = true;

                    State new_state = new State(new_cost, new_path, new_visited);
                    int bound = calculate_bound(new_state); // 한정값 계산

                    if (bound >= best_value) continue; // 한정값이 최적값 이상이면 가지치기

                    active_nodes.add(new_state);
                }
            }
        }
    }

    public static void main(String[] args) {
        branch_and_bound();

        System.out.print("최적 경로: [");
        for (int vertex : best_solution) {
            System.out.print((char) ('A' + vertex) + " ");
        }
        System.out.println("A]");
        System.out.println("최소 거리: " + best_value);
    }
}
