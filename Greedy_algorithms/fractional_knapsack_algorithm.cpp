#include <iostream>
#include <vector>
#include <iomanip> 
#include <algorithm>

using namespace std;

// 물건 구조체 정의
struct Item {
    string name;   // 물건 이름
    int weight;    // 해당 물건 무게
    int value;     // 해당 물건 가치
    int includedWeight = 0; // 배낭에 담을 무게 0으로 초기화

    // 단위 무게당 가치 계산
    double valuePerWeight() const {
        return (double)value / weight;
    }
};

// 단위 무게 당 가치로 내림차순
bool valuePerWeight_compare(const Item &a, const Item &b) {
    return a.valuePerWeight() > b.valuePerWeight();
}

// 부분 배낭 문제 함수
double fractionalKnapsack(int C, vector<Item> &items) {
    // 물건들을 단위 가치가 높은 순으로 정렬
    sort(items.begin(), items.end(), valuePerWeight_compare);

    int w = 0;  // 배낭 무게 초기화
    double v = 0.0;  // 배낭에 담긴 가치 초기화

    for (auto &item : items) {
        // 물건을 전부 담을 수 있는 경우
        if (w + item.weight <= C) {
            item.includedWeight = item.weight;
            w += item.weight;
            v += item.value;
        } else {
            // 물건을 전부 못담는 경우 남은 부분만을 담는 과정
            item.includedWeight = C - w;
            v += item.valuePerWeight() * item.includedWeight;
            item.weight = item.includedWeight;
            break;
        }
    }

    return v;
}

// 표 출력 
void printTable(const vector<Item>& items, double totalValue) {

    cout << left << setw(10) << "Goods" 
         << setw(28) << "Weight of goods in knapsack" 
         << setw(30) << "Value of goods in knapsack" << endl;

    int totalWeight = 0;

    for (const auto &item : items) {
        cout << setw(12) << item.name << setw(28) << to_string(item.includedWeight)+"g" << fixed << setprecision(0) << (item.valuePerWeight() * item.includedWeight)  << "원" << endl;
        totalWeight += item.includedWeight;
    }

    cout << "----------------------------------------------------------------"<< endl;
    cout << setw(12) << "합계"  << setw(28) << to_string(totalWeight) +"g"<< totalValue << "원" << endl;
}

int main() {
    int C = 40;  // 배낭 용량

    // 물건 리스트
    vector<Item> items = {
        {"백금", 10, 600000},  
        {"금　", 15, 750000},   
        {"은　", 25, 100000},    
        {"주석", 50, 50000}   
    };

    double maxValue = fractionalKnapsack(C, items);

    printTable(items, maxValue);

    return 0;
}
