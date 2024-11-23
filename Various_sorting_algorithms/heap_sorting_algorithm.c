#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void build_heap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        down_heap(arr, n, i);
    }
}

void down_heap(int arr[], int n, int i) {
    int largest = i; // 루트를 큰 값으로 초기화
    int left_child = 2 * i + 1; // 왼쪽 자식 노드
    int right_child = 2 * i + 2; // 오른쪽 자식 노드

    // 왼쪽 자식이 루트보다 크다면
    if (left_child < n && arr[left_child] > arr[largest])
        largest = left_child;

    // 오른쪽 자식이 현재 가장 큰 노드보다 크다면
    if (right_child < n && arr[right_child] > arr[largest])
        largest = right_child;

    // 가장 큰 노드가 루트가 아니면 교환하고 재귀 호출
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // 재귀 호출
        down_heap(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    build_heap(arr, n);

    int heap_size = n; // 힙 크기 관리
    for (int i = 1; i < n; i++) { 
        int temp = arr[0];
        arr[0] = arr[heap_size - 1];
        arr[heap_size - 1] = temp;

        heap_size--;

        down_heap(arr, heap_size, 0); // 힙 조건 조정
    }
}

// 파일에서 숫자 읽기
int file_read(const char* file_name, int arr[], int max_size) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        perror("file error");
        exit(EXIT_FAILURE);
    }

    int n = 0;
    while (n < max_size && fscanf(file, "%d", &arr[n]) != EOF) {
        n++;
    }

    fclose(file);
    return n;
}

// 파일에 정렬된 배열 쓰기
void file_write(const char* file_name, int arr[], int n) {
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        perror("file error");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", arr[i]);
    }

    fclose(file);
}

int main() {
    const char* input_file = "unsort_input.txt";
    const char* output_file = "heap_output.txt";
    int arr[1000]; 
    int n;

    n = file_read(input_file, arr, 1000);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    heap_sort(arr, n);
    clock_gettime(CLOCK_MONOTONIC, &end);

    file_write(output_file, arr, n);

    long heap_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);

    printf("정렬 완료\n소요시간: %ldns\n",heap_time);

    return 0;
}
