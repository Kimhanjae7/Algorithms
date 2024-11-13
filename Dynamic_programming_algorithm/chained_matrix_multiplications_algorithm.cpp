#include <iostream>
#include <vector>
#include <limits.h>
#include <iomanip>

using namespace std;

int chained_matrix_multiplication(const vector<int>& d, int n) {
    vector<vector<int>> C(n + 1, vector<int>(n + 1, 0));

    // C[i, i] = 0으로 초기화
    for (int i = 1; i <= n; ++i) {
        C[i][i] = 0; // L = 0일 때
    }

    for (int L = 1; L <= n - 1; ++L) { // 부분 문제의 크기
        for (int i = 1; i <= n - L; ++i) { // i는 시작점
            int j = i + L; // j는 끝점
            C[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; ++k) { // k는 쪼개는 기준점 -> if) k=2이면 A2다음 쪼개기
                 // C[i][k]와 C[k+1][j]는 이전 부분문제로 이미 구해진 값
                 // d[i-1]*d[k]*d[j]만 구해서 더해주면 됨
                int temp = C[i][k] + C[k + 1][j] + d[i - 1] * d[k] * d[j];

                // 최소값 구하기
                if (temp < C[i][j]) {
                    C[i][j] = temp;
                }
            }
        }
    }

    cout << "◎ 결과 테이블 출력" << endl;
    cout << setw(4) << "C" << " ";
    for (int i = 1; i <= n; ++i) {
        cout << setw(8) << i;
    }
    cout << endl;

    for (int i = 1; i <= n; ++i) {
        cout << setw(4) << i << " ";
        for (int j = 1; j <= n; ++j) {
            if (i > j) {
                cout << setw(8) << " ";
            } else {
                cout << setw(8) << (C[i][j] == INT_MAX ? 0 : C[i][j]);
            }
        }
        cout << endl;
    }

    return C[1][n];
}

int main() {

    // A1(5x10), A2(10x4), A3(4x20) ...,A10(3x20)
    vector<int> d = {5, 10, 4, 20, 10, 6, 7, 5, 10, 3, 20}; 
    int n = d.size() - 1;

    int minCost = chained_matrix_multiplication(d, n);
    cout << "\n◎ 최소 곱셈 횟수: " << minCost << endl;

    return 0;
}
