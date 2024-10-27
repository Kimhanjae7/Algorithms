#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#define MAX 10  // 정점의 개수 (도시 수)

// 도시 이름 -> 인덱스 변환 함수
int get_city_index(char *city, char cities[MAX][10], int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(city, cities[i]) == 0) {
            return i; // 해당 도시 인덱스 반환
        }
    }
    return -1; // 해당 도시가 없다는 뜻
}

// 다익스트라 최단 거리 함수
void dijkstra(int graph[MAX][MAX], int n, int start, int dist[MAX], char cities[MAX][10]) {
    int visited[MAX] = {0};  // 방문 여부
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;  // 처음에는 모든 도시까지의 거리를 무한대로 설정
    }
    dist[start] = 0;  // 시작점은 거리 0으로 설정

    for (int count = 0; count < n - 1; count++) {
        // 방문하지 않은 정점 중 최단 거리를 가진 정점을 선택
        int min = INT_MAX;
        int u;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] <= min) {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = 1;  // 선택된 정점 방문 처리

        // 선택된 정점과 인접한 정점의 거리 갱신
        for (int v = 0; v < n; v++) {
            // 아직 방문하지 않았고, 간선이 존재하고, 경로가 존재해야하고, 현재의 저장경로보다 짧아야 갱신가능 조건
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

// 표 출력 함수
void print_distance_table(int distances[MAX][MAX], char cities[MAX][10], int n) {
    printf("        "); 
    for (int i = 0; i < n; i++) {
        printf("%-8s", cities[i]);  // 도시 이름을 고정 너비로 출력
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%-8s", cities[i]);  // 도시 이름을 고정 너비로 출력
        for (int j = 0; j < n; j++) {
            if (j >= i) {
                if (i == j) {
                    // 자기 자신으로의 거리는 출력 X
                    printf("%-8s", "");
                } else if (distances[i][j] == INT_MAX) {
                    printf("%-8s", "X");  // 연결되지 않은 도시 표시
                } else {
                    printf("%-8d", distances[i][j]);  // 거리 출력
                }
            } else {
                printf("%-8s", "");  // 중복 값은 제외 (하삼각행렬 제외)
            }
        }
        printf("\n");
    }
}

int main() {
    FILE *file = fopen("dijkstra_city_input.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    char cities[MAX][10];  // 도시 이름 저장
    int graph[MAX][MAX] = {0};  // 도시 간의 거리 (인접행렬)
    int distances[MAX][MAX];  // 각 도시 간의 최단 거리 저장
    int n = 0; 

    while (!feof(file)) {
        char city1[10], city2[10];
        int distance;

        fscanf(file, "%s %s %d", city1, city2, &distance);

        // 도시가 이미 목록에 없으면 추가
        int index1 = get_city_index(city1, cities, n);
        if (index1 == -1) { // 배열에 없으면 추가
            strcpy(cities[n], city1);
            index1 = n;
            n++;
        }

        int index2 = get_city_index(city2, cities, n);
        if (index2 == -1) { // 배열에 없으면 추가
            strcpy(cities[n], city2);
            index2 = n;
            n++;
        }

        // 인접 행렬에 간선 저장
        graph[index1][index2] = distance;
        graph[index2][index1] = distance;
    }

    fclose(file);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // 각 도시에서 다익스트라 알고리즘 실행
    for (int i = 0; i < n; i++) {
        dijkstra(graph, n, i, distances[i], cities);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    long dijkstra_running_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    // 표 출력
    printf("\n");
    print_distance_table(distances, cities, n);

    printf("\n\n\n◎  dijkstra shortest path running time: %ld ns\n\n", dijkstra_running_time);
    return 0;
}
