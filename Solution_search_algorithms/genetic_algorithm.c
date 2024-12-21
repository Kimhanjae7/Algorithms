#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_POINTS 8
#define NUM_CANDIDATE 8
#define MAX_GENERATIONS 100 // 최대 세대 수
#define CROSSOVER_RATIO 1.0 // 교차 확률
#define MUTATION_RATIO 0.01 // 돌연변이 확률

typedef struct {
    int path[NUM_POINTS]; // 경로
    double fitness; // 적합도
} genetic;

// 점 좌표표
double points[NUM_POINTS][2] = {
    {0, 3}, {7, 5}, {6, 0}, {4, 3}, {1, 0}, {5, 3}, {4, 1}, {2, 2}
};

char labels[NUM_POINTS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

// 두 점 사이의 거리 계산
double calculate_distance(int a, int b) {
    double dx = points[a][0] - points[b][0];
    double dy = points[a][1] - points[b][1];
    return sqrt(dx * dx + dy * dy);
}

// 경로의 총 거리 계산
double calculate_total_distance(int *path) {
    double total = 0;
    for (int i = 0; i < NUM_POINTS - 1; i++) {
        total += calculate_distance(path[i], path[i + 1]);
    }
    total += calculate_distance(path[NUM_POINTS - 1], path[0]); // 시작점으로
    return total;
}

// 적합도 계산
double calculate_fitness(int *path) {
    return 1.0 / calculate_total_distance(path);
}

// 랜덤한 경로 생성
void generate_random_path(int *path) {
    for (int i = 0; i < NUM_POINTS; i++) {
        path[i] = i;
    }
    for (int i = 0; i < NUM_POINTS; i++) {
        int j = rand() % NUM_POINTS;
        int temp = path[i];
        path[i] = path[j];
        path[j] = temp;
    }
}

// 초기 개체군 생성
void initialize_population(genetic *population) {
    for (int i = 0; i < NUM_CANDIDATE; i++) {
        // 랜덤한 경로로 초기화
        generate_random_path(population[i].path);
        // 경로에 대한 적합도 계산
        population[i].fitness = calculate_fitness(population[i].path);
    }
}

// 선택 (룰렛휠 방법)
genetic select_genetic(genetic *population) {
    double sum_fitness = 0;
    // 전체 개체군 적합도 계산 합
    for (int i = 0; i < NUM_CANDIDATE; i++) {
        sum_fitness += population[i].fitness;
    }
    double r = ((double)rand() / RAND_MAX) * sum_fitness;
    double partial_sum = 0;
    // 개체 선택
    for (int i = 0; i < NUM_CANDIDATE; i++) {
        partial_sum += population[i].fitness;
        if (partial_sum >= r) {
            return population[i];
        }
    }
    return population[NUM_CANDIDATE - 1];
}

// 사이클 교차 연산산
void cycle_crossover(int *parent1, int *parent2, int *child) {
    int used[NUM_POINTS] = {0}; // 교차 과정 사용된 노드 표시
    int start = 0;

    while (used[start] == 0) {
        int current = start;
        do {
            child[current] = parent1[current];
            used[current] = 1;
            current = parent2[current];
        } while (current != start); // 사이클 완성까지 반복

        // 아직 사용되지 않은 시작점 찾기
        for (int i = 0; i < NUM_POINTS; i++) {
            if (!used[i]) {
                start = i;
                break;
            }
        }
    }
    // 사용안된 노드 부모2값으로 복사
    for (int i = 0; i < NUM_POINTS; i++) {
        if (!used[i]) {
            child[i] = parent2[i];
        }
    }
}

// 돌연변이
void mutate(int *path) {
    if (((double)rand() / RAND_MAX) < MUTATION_RATIO) {
        int i = rand() % NUM_POINTS;
        int j = rand() % NUM_POINTS;
        int temp = path[i];
        path[i] = path[j];
        path[j] = temp;
    }
}

// 새로운 세대 생성
// 선택 -> 교차 -> 돌연변이 순서
void create_new_generation(genetic *population, genetic *new_population) {
    for (int i = 0; i < NUM_CANDIDATE; i++) {
        // 1. 후보해 선택
        genetic parent1 = select_genetic(population);
        genetic parent2 = select_genetic(population);

        // 2. 교차연산
        if (((double)rand() / RAND_MAX) < CROSSOVER_RATIO) {
            cycle_crossover(parent1.path, parent2.path, new_population[i].path);
        } else {
            for (int j = 0; j < NUM_POINTS; j++) {
                new_population[i].path[j] = parent1.path[j];
            }
        }
        // 3. 돌연변이
        mutate(new_population[i].path);
        // 4. 적합도 계산
        new_population[i].fitness = calculate_fitness(new_population[i].path);
    }
}

// 최적 개체 찾기
genetic find_best_genetic(genetic *population) {
    genetic best = population[0];
    for (int i = 1; i < NUM_CANDIDATE; i++) {
        if (population[i].fitness > best.fitness) {
            best = population[i];
        }
    }
    return best;
}

int main() {
    srand(time(NULL));

    genetic population[NUM_CANDIDATE];
    genetic new_population[NUM_CANDIDATE];

    initialize_population(population);

    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        create_new_generation(population, new_population);

        // 현재 세대를 새 개체군으로 대체
        for (int i = 0; i < NUM_CANDIDATE; i++) {
            population[i] = new_population[i];
        }
    }

    genetic best = find_best_genetic(population);
    printf("\nPath: ");
    for (int i = 0; i < NUM_POINTS; i++) {
        printf("%c ", labels[best.path[i]]);
    }
    printf("\nDistance: %.2f\n", 1.0 / best.fitness);

    return 0;
}
