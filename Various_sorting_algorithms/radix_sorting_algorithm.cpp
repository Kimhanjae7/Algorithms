#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono; 

void radix_sort_lsd(vector<int>& arr) {
    // 배열에서 가장 큰 값 찾기
    int max_value = *max_element(arr.begin(), arr.end());
    // 1의 자리부터 비교(자리수값)
    int place = 1;

    // 자리수값이 배열의 최대값 자리보다 크면 종료
    while (max_value / place > 0) {
        // 해당 자리수의 값 0~9을 배정할 2차원 벡터
        vector<vector<int>> v(10);

        // 현재 자리수의 값을 계산하여 해당 자리수 v에 숫자 삽입
        for (int num : arr) {
            int digit = (num / place) % 10;
            v[digit].push_back(num);
        }

        int index = 0;
        // 해당 자리수로 정렬된 배열을 원래의 배열에 삽입
        for (int i = 0; i < 10; i++) {
            for (int num : v[i]) {
                arr[index++] = num;
            }
        }
        // 자리수 증가 1의 자리->10의 자리->100의 자리 (*10)
        place *= 10;
    }
}

void radix_sort_msd(vector<int>& arr, int left, int right, int place, int max_digits) {
    // 종료 조건 원소 하나가 남거나, 자리수가 최대값의 자리수를 넘어갔을 때
    if (left >= right || place > max_digits) return;
    // 해당 자리수의 값 0~9을 배정할 2차원 벡터
    vector<vector<int>> v(10);

    for (int i = left; i <= right; i++) {
        // 현재 자리값의 값만 추출하는 연산 후, 그 자릿수의 값을 인덱스로 v에 저장
        int digit = (arr[i] / static_cast<int>(pow(10, max_digits - place))) % 10;
        v[digit].push_back(arr[i]);
    }

    int index = left;
    for (int i = 0; i < 10; i++) {
        // 다음 자리수로 정렬하기 위해 원래의 arr에 복사
        // 최고 자릿수 오름차순으로 정렬된 상태로 arr에 삽입
        for (int num : v[i]) { 
            arr[index++] = num;
        }
        // v가 비어있지않으면 추가 정렬 수행
        if (!v[i].empty()) {
            // 최고 자릿수 끼리 그룹지어 다음 자릿수로 msd 재귀 실행 정렬
            int size = v[i].size();
            radix_sort_msd(arr, index - size, index - 1, place + 1, max_digits);
        }
    }
}

void msd_calc_digits(vector<int>& arr) {
    // 배열에서 가장 큰 값 찾기
    int max_value = *max_element(arr.begin(), arr.end());
    // 가장 큰 값의 자리수 계산하기(log10 이용)
    int max_digits = static_cast<int>(log10(max_value)) + 1;

    radix_sort_msd(arr, 0, arr.size() - 1, 1, max_digits);
}

vector<int> file_read(const string& file_name) {
    ifstream file(file_name);
    vector<int> arr;
    int num;

    if (!file.is_open()) {
        cerr << "file error" << endl;
        exit(EXIT_FAILURE);
    }

    while (file >> num) {
        arr.push_back(num);
    }

    file.close();
    return arr;
}

void file_write(const string& file_name, const vector<int>& arr) {
    ofstream file(file_name);

    if (!file.is_open()) {
        cerr << "file error" << endl;
        exit(EXIT_FAILURE);
    }

    for (int num : arr) {
        file << num << endl;
    }

    file.close();
}

int main() {
    string input_file = "unsort_input.txt";
    string output_file1 = "radix_lsd_output.txt";
    string output_file2 = "radix_msd_output.txt";


    vector<int> arr = file_read(input_file);
    auto start_lsd = high_resolution_clock::now();
    radix_sort_lsd(arr);
    auto end_lsd = high_resolution_clock::now();
    auto radix_lsd_time = duration_cast<nanoseconds>(end_lsd - start_lsd);
    file_write(output_file1, arr);
    
    arr = file_read(input_file); 
    auto start_msd = high_resolution_clock::now();
    msd_calc_digits(arr);
    auto end_msd = high_resolution_clock::now();
    auto radix_msd_time = duration_cast<nanoseconds>(end_msd - start_msd);
    file_write(output_file2, arr);

    cout << "정렬 완료" << endl;
    cout << "소요 시간 [LSD]: " << radix_lsd_time.count() << "ns" << endl;
    cout << "소요 시간 [MSD]: " << radix_msd_time.count() << "ns" << endl;

    return 0;
}
