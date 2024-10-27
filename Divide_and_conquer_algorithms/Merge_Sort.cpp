#include <iostream>
#include <chrono> //정밀한 시간 측정을 위한 라이브러리 chrono 사용
#include <fstream>
#include <vector>

using namespace std;
using namespace chrono;

void merge(vector<int> &arr, int first, int mid, int last){
    int* sorted = new int[last - first + 1];
	int i, j, k;
    // mid를 기준으로 좌측arr과 우측arr
	i = first; // 좌측 arr의 첫 번째 인덱스 저장 
	j = mid + 1; // 우측 arr의 첫 번째 인덱스 저장 -> 분할된 첫번 째 인덱스 값을 비교하기 위함
	k = 0; // sorted 배열의 인덱스 역할 변수 

    while (i <= mid && j <= last){ // 각 배열의 인덱스를 증가시키며 값을 비교 (i는 좌측배열의 첫 번째, j는 우측배열의 첫 번째)
        // 두 배열의 가장 작은 값을 비교하여 더 작은값을 sorted 배열에 저장 
		if (arr[i] <= arr[j]){sorted[k++] = arr[i++];}  
		else {sorted[k++] = arr[j++];}
	}

    // 좌측 배열의 요소가 모두 처리되고 우측배열의 원소가 남은 경우
	if (i > mid){
        // 하위 배열들은 이미 정렬되어 있는 상태이므로 그대로 sorted 배열에 추가
		while (j <= last){
            sorted[k++] = arr[j++];
        }
    }
    // 우측 배열의 요소가 모두 처리되고 좌측배열의 원소가 남은 경우
	else{
        // 하위 배열들은 이미 정렬되어 있는 상태이므로 그대로 sorted 배열에 추가
		while (i <= mid){
        sorted[k++] = arr[i++];
        }
    }
    // 정렬이 완료된 배열을 원래 배열로 복사
	for (i = first, k = 0; i <= last; i++, k++){
        arr[i] = sorted[k];
    }

    delete[] sorted;
}

void mergeSort(vector<int> &arr, int first, int last){
    if(first < last){ // 시작 인덱스가 끝 인덱스보다 작을 때 수행(재귀 종료 조건)
        int mid = (first+last) / 2;
        mergeSort(arr, first, mid); // 배열의 좌측 반을 재귀적으로 재분할
        mergeSort(arr, mid+1, last); // 배열의 우측 반을 재귀적으로 재분할
        merge(arr, first, mid, last); // 분할된 배열을 정렬 후 병합
    }
}

int main(){
    int size; // 배열 크기 변수
    ifstream fin("input_sort.txt");
    if (!fin) {
        cerr << "파일을 열 수 없습니다." << endl;
        return 1;
    }

    ofstream fout("output_merge_sort.xlsx");

    // 입력 파일 배열의 크기만큼 동적으로 배열 할당하기 위해 vector사용
    vector<int> arr;
    int input_number;
    while (fin >> input_number){
        arr.push_back(input_number);
    }

    // 정렬 시간 측정 시작
    system_clock::time_point start = system_clock::now();
    // 합병 정렬 함수 호출
    mergeSort(arr, 0, arr.size()-1);
    // 정렬 시간 측정 종료
    system_clock::time_point end = system_clock::now();
    // 나노초 단위로 시간 출력
    nanoseconds sortTime = end - start ;

    // 정렬된 배열 파일을 통해 출력
    fout << "◎ 합병정렬된 배열 출력 결과" <<endl;
    for(const int& element : arr){ 
        fout << element <<endl;
    }
    fout << endl;
    cout << "정렬이 완료되었습니다. 파일을 확인해주세요" << endl;

    // 소요 시간 출력
    cout << "합병정렬 시간: " << sortTime.count() << "ns" << endl;
   
    fout.close(); // 파일 닫기
    fin.close();
}
