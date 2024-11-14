#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip> 

using namespace std;

int coin_change_dp(int n, const vector<int>& d, int k) {
    vector<int> C(n + 1, INT_MAX); // C 배열을 무한대로 초기화
    C[0] = 0; // 금액이 0원일 때, 동전 개수 0개

    for (int j = 1; j <= n; ++j) { // j: 거스름돈 액수를 1부터 n까지 
        for (int i = 1; i <= k; ++i) { // 가장 큰 동전부터 1원짜리 동전까지 탐색
            if (d[i - 1] <= j && C[j - d[i - 1]] != INT_MAX && C[j - d[i - 1]] + 1 < C[j]) {
                // 더 적게 사용하는 동전 수로 등록
                C[j] = C[j - d[i - 1]] + 1;
            }
        }
    }

    // 테이블 출력
    cout << "j: ";
    for (int j = 0; j <= n; ++j) {
        cout << setw(3) << j;
    }
    cout << endl;

    cout << "C: ";
    for (int j = 0; j <= n; ++j) {
        if (C[j] == INT_MAX) {
            cout << setw(3) << "-";
        } else {
            cout << setw(3) << C[j];
        }
    }
    cout << endl;

    return C[n];
}

int main() {
    int n = 20; 
    vector<int> d = {16, 10, 5, 1}; 
    int k = d.size();

    coin_change_dp(n, d, k);
}
