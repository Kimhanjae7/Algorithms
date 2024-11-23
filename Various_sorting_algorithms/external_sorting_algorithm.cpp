#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

// 버퍼 내 데이터 insertion 정렬
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

// 100개의 데이터를 메모리 버퍼에 읽기
bool read_block(ifstream& infile, vector<int>& buffer, int block_size) {
    buffer.clear();
    int value;
    while (buffer.size() < block_size && infile >> value) {
        buffer.push_back(value);
    }
    return !buffer.empty();
}

void merge_blocks(vector<vector<int>>& blocks, ofstream& outfile) {
    // heap을 사용하여 가장 작은 값을 루트로 유지 
    // pair<값,blocks 인덱스> 저장
    auto cmp = [](pair<int, int> a, pair<int, int> b) { return a.first > b.first; };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> min_heap(cmp);

    vector<int> index(blocks.size(), 0); // 각 블록의 현재 인덱스 저장

    // 각 블록의 첫 번째 값을 힙에 삽입
    for (int i = 0; i < blocks.size(); i++) {
        if (!blocks[i].empty()) { 
            min_heap.push({blocks[i][0], i}); //[i][0]이 i번째 블록의 첫 번째 값을 의미
        }
    }

    // 병합
    while (!min_heap.empty()) {
        // 힙에서 최소값과 해당 값의 인덱스 저장
        auto [value, block_idx] = min_heap.top();
        min_heap.pop();
        // 최소값 기록
        outfile << value << endl;

        // 해당 블록의 다음 값을 힙에 삽입
        index[block_idx]++;
        if (index[block_idx] < blocks[block_idx].size()) { // 블럭이 끝났는지 확인
            min_heap.push({blocks[block_idx][index[block_idx]], block_idx});
        }
    }
}

int main() {
    string input_file = "unsort_input.txt";
    string output_file = "external_output.txt";
    int block_size = 100; // 메모리에서 처리가능한 데이터 수

    ifstream infile(input_file);
    if (!infile.is_open()) {
        cerr << "file error" << endl;
        return 1;
    }

    ofstream outfile(output_file);
    if (!outfile.is_open()) {
        cerr << "file error" << endl;
        return 1;
    }

    vector<vector<int>> blocks; // insertion 정렬로 인해 정렬된 블록들 저장
    vector<int> buffer; // 파일에서 읽어온 수 삽입 배열

    while (read_block(infile, buffer, block_size)) {
        insertion_sort(buffer); // 파일에서 읽은 값 버퍼에 저장
        blocks.push_back(buffer); // 정렬된 배열 blocks에 저장
    }

    infile.close();
    merge_blocks(blocks, outfile);

    outfile.close();
    cout << "정렬 완료" << endl;

    return 0;
}
