#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#define MAX 10  // 최대 정점 수 (도시 수)
#define INF 99999 // 무한값 -> INT_MAX는 오버플로우 발생

// 도시 이름 -> 인덱스 변환 함수
int get_city_index(char *city, char cities[MAX][10], int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(city, cities[i]) == 0) {
            return i;
        }
    }
    return -1;
}

// Floyd-Warshall 알고리즘
void floydWarshall(int dist[MAX][MAX], int n) {
    for (int k = 0; k < n; k++) { // k는 중간 경로 정점
        for (int i = 0; i < n; i++) {
            if (i == k) continue; // i != k 
            for (int j = 0; j < n; j++) {
                if (j == k || j == i) continue; // j != k and j != i 
                // i->k->j 와 i->j 즉, 정점을 거친 거리와 다이렉트 거리를 비교하여 더 짧은 거리로 갱신
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

// 표 출력 함수
void print_distance_table(int distances[MAX][MAX], char cities[MAX][10], int n) {
    printf("        ");
    for (int i = 0; i < n; i++) {
        printf("%-8s", cities[i]);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%-8s", cities[i]);
        for (int j = 0; j < n; j++) {
            if (j >= i) {
                if (i == j) {
                    printf("%-8s", "");
                } else if (distances[i][j] == INF) {
                    printf("%-8s", "X");
                } else {
                    printf("%-8d", distances[i][j]);
                }
            } else {
                printf("%-8s", "");
            }
        }
        printf("\n");
    }
}

// 메인 함수
int main() {
    FILE *file = fopen("floyd_warshall_input.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    char cities[MAX][10];
    int graph[MAX][MAX];
    int n = 0;

    // 인접 행렬 초기화
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = INF;
            }
        }
    }

    while (!feof(file)) {
        char city1[10], city2[10];
        int distance;

        fscanf(file, "%s %s %d", city1, city2, &distance);

        int index1 = get_city_index(city1, cities, n);
        if (index1 == -1) {
            strcpy(cities[n], city1);
            index1 = n;
            n++;
        }

        int index2 = get_city_index(city2, cities, n);
        if (index2 == -1) {
            strcpy(cities[n], city2);
            index2 = n;
            n++;
        }

        graph[index1][index2] = distance;
        graph[index2][index1] = distance;
    }

    fclose(file);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    floydWarshall(graph, n);

    clock_gettime(CLOCK_MONOTONIC, &end);
    long floyd_warshall_running_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);

    // 표 출력
    printf("\n");
    print_distance_table(graph, cities, n);

    printf("\n\n\n◎ Floyd-Warshall shortest path running time: %ld ns\n\n", floyd_warshall_running_time);
    return 0;
}
