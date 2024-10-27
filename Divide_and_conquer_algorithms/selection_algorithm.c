#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define ARRAY_SIZE 100

// 배열 요소를 교환하는 swap 함수
void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Median-of-Three를 사용하여 피벗을 선택하는 함수 (중앙값을 pivot으로)
int medianOfThree(int arr[], int first, int mid, int last) {
    if (arr[first] > arr[mid]) {
        if (arr[mid] > arr[last])
            return mid;
        else if (arr[first] > arr[last])
            return last;
        else
            return first;
    } else {
        if (arr[first] > arr[last])
            return first;
        else if (arr[mid] > arr[last])
            return last;
        else
            return mid;
    }
}

// 피벗을 기준으로 배열을 분할하는 함수 (퀵정렬 분할과 동일)
int partition(int arr[], int first, int last) {
    int mid = (last - first) / 2;
    int pivotIndex = medianOfThree(arr, first, mid, last);
    swap(arr, first, pivotIndex);  // 피벗을 첫 번째 위치로 이동
    int pivot = arr[first];  // 피벗은 이제 첫 번째 위치에 있음

    int left = first + 1;
    int right = last;

    while (left <= right) {
        // left는 피벗보다 큰 값을 찾을 때까지 이동
        while (left <= last && arr[left] <= pivot) {
            left++;
        }
        // right는 피벗보다 작은 값을 찾을 때까지 이동
        while (right > first && arr[right] >= pivot) {
            right--;
        }
        // left와 right가 교차하지 않았으면, 값을 교환
        if (left < right) {
            swap(arr, left, right);
        }
    }
    // 피벗을 자신의 최종 위치로 이동
    swap(arr, first, right);

    // 피벗 최종 위치 반환
    return right;
}

// selection 알고리즘 구현
int selection(int arr[], int left, int right, int k) {
    if (left <= right) {
        int p = partition(arr, left, right);

        int S = (p-1) - left + 1; // S = Small group의 크기

        if (k <= S)
            return selection(arr, left, p - 1, k); // Small group에서 찾기
        else if (k == S + 1)
            return arr[p]; // pivot = k번째 작은 숫자
        else
            return selection(arr, p + 1, right, k - S - 1); // Large group에서 찾기
               // S가 small group 크기이므로 그만큼 빼기
    }
    return -1; // k가 배열 크기를 벗어난 경우
}

int main(){
    int arr[ARRAY_SIZE];
    FILE *file = fopen("input_sort.txt", "r");

    if (file == NULL) {
        printf("※ 파일을 열 수 없습니다.\n");
        return 1;
    }

    // fscanf를 이용하여 파일의 데이터 읽어와 arr배열에 저장
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (fscanf(file, "%d", &arr[i]) != 1) {
            printf("※ 파일에서 데이터 오류가 발생\n");
            fclose(file);
            return 1;
        }
    }
    fclose(file);

    while (1) {
        // 사용자로부터 k값 입력 받기
        char input[10];
        printf("● 몇 번째로 작은 요소를 찾고 싶으십니까? (1에서 %d 사이, 종료하려면 'Q' 입력): ", ARRAY_SIZE);
        scanf("%s", input);

        // 'Q' 입력 시 프로그램 종료
        if (toupper(input[0]) == 'Q') {
            // toupper을 이용하여 소문자 대문자든 종료
            printf("프로그램 종료.\n");
            break;
        }

        // k값을 숫자로 변환
        int k = atoi(input);

        // 유효한 인덱스가 아닐 경우 에러 메시지
        if (k < 1 || k > ARRAY_SIZE) {
            printf("※ 유효한 k값을 입력해 주세요.\n");
            continue;
        }

        // 시간 측정 시작
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        int result = selection(arr, 0, ARRAY_SIZE - 1, k);

         // 시간 측정 종료
        clock_gettime(CLOCK_MONOTONIC, &end);

        // 경과 시간 계산 (나노초)
        long running_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
        printf("● 배열에서 %d번째로 작은 요소는 %d입니다.\n", k, result);
        printf("● 선택 알고리즘 소요시간: %ld ns\n\n", running_time);
    }
}