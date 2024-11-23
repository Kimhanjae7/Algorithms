#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono; 

void insertion_sort(vector<int>& arr) {
    int n = arr.size();
    // 0번째는 정렬된 것으로 간주 ,i는 1부터
    for (int i = 1; i < n; i++) {
        int current_element = arr[i]; // 정렬되지 않은 부분의 가장 왼쪽 원소
        int j = i - 1;

        // 정렬된 부분에서 current_element보다 큰 요소들을 오른쪽으로 이동
        while (j >= 0 && arr[j] > current_element) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        // current_element를 올바른 위치에 삽입
        arr[j + 1] = current_element;
    }
}

// 파일에서 숫자 읽기
vector<int> file_read(const string& filename) {
    ifstream input_file(filename);
    vector<int> numbers;
    int num;

    if (!input_file.is_open()) {
        cerr << "file error" << endl;
        exit(1);
    }

    while (input_file >> num) {
        numbers.push_back(num);
    }

    input_file.close();
    return numbers;
}

// 파일에 정렬된 배열 쓰기
void file_write(const string& filename, const vector<int>& arr) {
    ofstream output_file(filename);

    if (!output_file.is_open()) {
        cerr << "file error" << endl;
        exit(1);
    }

    for (const int& num : arr) {
        output_file << num << endl;
    }

    output_file.close();
}

int main() {
    string input_file = "unsort_input.txt";
    string output_file = "insertion_output.txt";

    vector<int> numbers = file_read(input_file);

    auto start = high_resolution_clock::now();
    insertion_sort(numbers);
    auto end = high_resolution_clock::now();
    auto insertion_time = duration_cast<nanoseconds>(end - start);

    file_write(output_file, numbers);
    cout << "정렬 완료" << endl;
    cout <<"소요시간: " << insertion_time.count() << "ns" << endl;

    return 0;
}
