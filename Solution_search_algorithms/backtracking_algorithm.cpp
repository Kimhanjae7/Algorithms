#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int NUM_VERTEX = 5;

// 그래프 (정점별 거리)
int graph[NUM_VERTEX][NUM_VERTEX] = {
    {0, 2, 7, 3, 10},
    {2, 0, 3, 5, 4},
    {7, 3, 0, 6, 1},
    {3, 5, 6, 0, 9},
    {10, 4, 1, 9, 0}
};

// 최소 거리와 경로 저장
int best_solution_distance = INT_MAX;
vector<int> best_solution;

// Backtracking - TSP
void backtrack_tsp(vector<int>& tour, vector<bool>& visited, int current, int distance) {
    // tour가 모든 정점을 방문했을 때
    if (tour.size() == NUM_VERTEX) {
        distance += graph[current][tour[0]]; // 시작점으로 돌아가는 거리 추가
        if (distance < best_solution_distance) {
            best_solution_distance = distance;
            best_solution = tour;
        }
        return;
    }

    // 아직 방문하지 않은 정점을 순회하며 경로 확장
    for (int next = 0; next < NUM_VERTEX; next++) {
        // 방문하지 않았고, 연결된 경우
        if (!visited[next] && graph[current][next] != INT_MAX) { 
            visited[next] = true;
            tour.push_back(next);
            backtrack_tsp(tour, visited, next, distance + graph[current][next]);
            tour.pop_back(); // 백트래킹: 추가한 정점을 제거
            visited[next] = false; // 방문 상태 초기화
        }
    }
}

int main() {
    vector<int> tour;
    vector<bool> visited(NUM_VERTEX, false);

    tour.push_back(0);
    visited[0] = true;

    backtrack_tsp(tour, visited, 0, 0);

    cout << "최적 경로: [";
    for (int i : best_solution) {
        cout << (char)('A' + i) << " ";
    }
    cout << "A]" << endl;
    cout << "최소 거리: " << best_solution_distance << endl;

    return 0;
}
