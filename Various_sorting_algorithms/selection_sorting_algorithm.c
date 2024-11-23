#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int array[], int n) {
    // 0번째부터 최소값을 채워넣기
    for (int i = 0; i < n - 1; i++) {
        int min = i; // 비교를 위해 그 인덱스를 최소값으로 지정
        // i번째 다음부터 최소값 탐색시작
        for (int j = i + 1; j < n; j++) { 
            if (array[j] < array[min]) {
                min = j; // 새로운 최소값 인덱스 갱신
            }
        }
        // 최소값과 현재 위치의 값 교환
        int temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
}

// 파일에 정렬된 배열 쓰기
void file_write(const char *file_name, int array[], int n) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        printf("fi;e error");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", array[i]);
    }
    fclose(file);
}

// 파일에서 숫자 읽기
int file_read(const char *file_name, int array[], int max_size) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("file error");
        exit(1);
    }
    int n = 0;
    while (fscanf(file, "%d", &array[n]) != EOF && n < max_size) {
        n++;
    }
    fclose(file);
    return n;
}

int main() {
    const char *input_file = "unsort_input.txt";
    const char *output_file = "selection_output.txt";

    int array[1000];
    int n;

    n = file_read(input_file, array, 1000);
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    selection_sort(array, n);
    clock_gettime(CLOCK_MONOTONIC, &end);

    file_write(output_file, array, n);

    long selection_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);

    printf("정렬 완료\n소요시간: %ldns\n",selection_time);
    return 0;
}
