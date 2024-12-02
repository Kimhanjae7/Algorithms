#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define CAPACITY 10 // 통 용량(C) 10

// 최초 적합: 가장 먼저 발견되는 여유있는 통에 넣기
void first_fit(int items[], int n) {
    int bins[MAX][MAX] = {0}; // 각 통에 들어있는 물건 저장 배열
    int bin_sizes[MAX] = {0}; // 각 통에 들어있는 물건 개수 (무게 카운트용)
    int bin_count = 0; // 사용 통 개수

    for (int i = 0; i < n; i++) {
        int placed = 0; // 현재 물건 배치 여부
        // 사용 중인 통 탐색
        for (int j = 0; j < bin_count; j++) {
            int current_sum = 0; // 현재 통 물건 크기 합계
            // 해당 통의 담긴 물건들 무게 합산
            for (int k = 0; k < bin_sizes[j]; k++) {
                current_sum += bins[j][k];
            }
            // 현재 통에 들어있는 용량과 새로 넣을 물건 용량의 합이 용량을 넘지않으면 물건 넣기
            if (current_sum + items[i] <= CAPACITY) {
                bins[j][bin_sizes[j]++] = items[i];
                placed = 1; // 물건 배치
                break;
            }
        }
        // 만약 배치가 안됐다면 새 통에 넣고 개수 ++
        if (!placed) {
            bins[bin_count][bin_sizes[bin_count]++] = items[i];
            bin_count++;
        }
    }

    printf("Output1 (First Fit): ");
    for (int i = 0; i < bin_count; i++) {
        printf("bin%d = [", i + 1);
        for (int j = 0; j < bin_sizes[i]; j++) {
            printf("%d", bins[i][j]);
            if (j < bin_sizes[i] - 1) printf(", ");
        }
        printf("]");
        if (i < bin_count - 1) printf(", ");
    }
    printf("\n\n");
}

// 다음 적합: 직전 통만 확인하여 여유있으면 넣기
void next_fit(int items[], int n) {
    int bins[MAX][MAX] = {0};
    int bin_sizes[MAX] = {0};
    int bin_count = 0;
    int current_sum = 0;

    for (int i = 0; i < n; i++) {
        // 현재 통 용량과 새물건 용량 합이 총용량을 넘어서는 경우
        if (current_sum + items[i] > CAPACITY) {
            bin_count++; // 새 통 사용
            current_sum = 0; // 새 통이므로 용량 0
        }
        // 새 통에 삽입
        bins[bin_count][bin_sizes[bin_count]++] = items[i];
        current_sum += items[i]; // 용량 업데이트
    }

    printf("Output2 (Next Fit): ");
    for (int i = 0; i <= bin_count; i++) {
        printf("bin%d = [", i + 1);
        for (int j = 0; j < bin_sizes[i]; j++) {
            printf("%d", bins[i][j]);
            if (j < bin_sizes[i] - 1) printf(", ");
        }
        printf("]");
        if (i < bin_count) printf(", ");
    }
    printf("\n\n");
}

// 최선 적합: 기존에 사용 중인 통을 탐색하여 새 물건 삽입 후 남는 용량이 가장 적은 통에 삽입
void best_fit(int items[], int n) {
    int bins[MAX][MAX] = {0};
    int bin_sizes[MAX] = {0};
    int bin_count = 0;

    for (int i = 0; i < n; i++) {
        int best_bin = -1; // 적절한 통을 찾지 못한 상태
        int min_remain_capacity = CAPACITY + 1; // 최소 나머지 공간 저장(초기값)

        for (int j = 0; j < bin_count; j++) {
            int current_sum = 0;
            for (int k = 0; k < bin_sizes[j]; k++) {
                current_sum += bins[j][k];
            }
            int remain_capacity = CAPACITY - current_sum; // 현재 통의 남은 공간
            // 물건을 넣을 수 있는지 체크 && 남는 공간 최적 통보다 더 적게 남을 때
            if (items[i] <= remain_capacity && remain_capacity < min_remain_capacity) {
                best_bin = j; // 최적통 갱신
                min_remain_capacity = remain_capacity; // 최소 나머지 공간 갱신
            }
        }

        // 최적의 통이 없는 경우 새 통에 물건 삽입
        if (best_bin == -1) {
            bins[bin_count][bin_sizes[bin_count]++] = items[i];
            bin_count++;
        // 최적의 통이 있는 경우 그 통에 삽입
        } else {
            bins[best_bin][bin_sizes[best_bin]++] = items[i];
        }
    }

    printf("Output3 (Best Fit): ");
    for (int i = 0; i < bin_count; i++) {
        printf("bin%d = [", i + 1);
        for (int j = 0; j < bin_sizes[i]; j++) {
            printf("%d", bins[i][j]);
            if (j < bin_sizes[i] - 1) printf(", ");
        }
        printf("]");
        if (i < bin_count - 1) printf(", ");
    }
    printf("\n\n");
}

// 최악 적합: 기존에 사용 중인 통을 탐색하여 새 물건 삽입 후 남는 용량이 가장 많은 통에 삽입
void worst_fit(int items[], int n) {
    int bins[MAX][MAX] = {0};
    int bin_sizes[MAX] = {0};
    int bin_count = 0;

    for (int i = 0; i < n; i++) {
        int worst_bin = -1; // 적잘한 통을 찾지 못한 상태
        int max_remain_capacity = -1; // 최선 적합과 반대로 남는 용량이 큰 통을 찾으므로 -1로 초기화

        for (int j = 0; j < bin_count; j++) {
            int current_sum = 0;
            for (int k = 0; k < bin_sizes[j]; k++) {
                current_sum += bins[j][k];
            }
            // 현재 통의 공간 계산
            int remain_capacity = CAPACITY - current_sum;
            // 물건을 넣을 수 있고, 남은 용량이 더 클 경우 갱신
            if (items[i] <= remain_capacity && remain_capacity > max_remain_capacity) {
                worst_bin = j;
                max_remain_capacity = remain_capacity;
            }
        }
        // 적절한 통을 찾지 못하면 새 통
        if (worst_bin == -1) {
            bins[bin_count][bin_sizes[bin_count]++] = items[i];
            bin_count++;
        // 적절한 통이 있을 경우 
        } else {
            bins[worst_bin][bin_sizes[worst_bin]++] = items[i];
        }
    }

    printf("Output4 (Worst Fit): ");
    for (int i = 0; i < bin_count; i++) {
        printf("bin%d = [", i + 1);
        for (int j = 0; j < bin_sizes[i]; j++) {
            printf("%d", bins[i][j]);
            if (j < bin_sizes[i] - 1) printf(", ");
        }
        printf("]");
        if (i < bin_count - 1) printf(", ");
    }
    printf("\n\n");
}

int main() {
    int items[] = {7, 5, 6, 4, 2, 3, 7, 5};
    int n = 8;
    printf("\n");

    first_fit(items, n);
    next_fit(items, n);
    best_fit(items, n);
    worst_fit(items, n);

    return 0;
}
