#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <set>

using namespace std;
using namespace chrono;

struct Edge {
    int vertex1, vertex2; // 두 정점
    double weight; // 간선의 가중치

    bool operator<(const Edge& other) const {
        return weight < other.weight; // 가중치 기준으로 정렬하기 위한 설정
    }
};

vector<int> parent; // 부모 노드를 저장 변수


// 부모 노드를 찾는 함수
int cycle_check(int node) {
    if (parent[node] != node)
        parent[node] = cycle_check(parent[node]); // 부모를 재귀적으로 찾기
    return parent[node];
}

// Kruskal 알고리즘
vector<Edge> kruskal(int n, vector<Edge>& tree) {
    vector<Edge> mst; 

    parent.resize(n);
    for (int i = 0; i < n; ++i){
        parent[i] = i;
    }

    sort(tree.begin(), tree.end()); // 간선 가중치 기준으로 정렬

    for (const Edge& edge : tree) {
        int root1 = cycle_check(edge.vertex1); // vertex1의 부모 찾기
        int root2 = cycle_check(edge.vertex2); // vertex2의 부모 찾기

        if (root1 != root2) { // 두 노드의 부모가 다르면 (=사이클이 아니면)
            mst.push_back(edge); // MST에 간선 추가
            parent[root2] = root1; // 두 노드를 연결 (부모 노드 병합)
        }
    }

    return mst;
}

// 노드 방문
void traveling(int node, const vector<vector<int>>& tree, vector<bool>& visited, vector<int>& tour) {
    visited[node] = true;
    tour.push_back(node); // 방문한 노드 저장
    for (int neighbor : tree[node]) {
        if (!visited[neighbor])
            // 방문하지 않은 노드 방문
            traveling(neighbor, tree, visited, tour);
    }
}

// 거리 계산
double calc_distance(pair<int, int> a, pair<int, int> b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

// Traveling Salesman Problem 알고리즘
void TSP(int n, const vector<pair<int, int>>& cities, vector<Edge>& tree) {
    // kruskal algorithm을 이용하여 MST 생성
    vector<Edge> mst = kruskal(n, tree);

    // MST를 트리 구조로 변환 -> 탐색을 수월하게 하기 위함
    vector<vector<int>> mst_to_tree(n);
    for (const Edge& edge : mst) {
        mst_to_tree[edge.vertex1].push_back(edge.vertex2);
        mst_to_tree[edge.vertex2].push_back(edge.vertex1);
    }

    vector<int> tour;
    vector<bool> visited(n, false); // 초기화
    traveling(0, mst_to_tree, visited, tour); // A 에서 시작

    // 이동 순서 출력 및 거리 계산
    set<int> visited_cities;
    double total_distance = 0;
    cout << "Order of movement: ";
    for (int i = 0; i < tour.size(); ++i) {
        // 중복 체크
        if (visited_cities.find(tour[i]) == visited_cities.end()) {
            cout << char('A' + tour[i]) << " "; // 도시를 알파벳으로 변환 0-A, 1-B ...
            // 거리 계산 0일 경우에는 첫 번째 도시 이기 때문에 이전 도시가 없음
            if (i > 0) {
                // 이동 거리 갱신
                total_distance += calc_distance(cities[tour[i - 1]], cities[tour[i]]);
            }
            visited_cities.insert(tour[i]); // 방문 도시 기록
        }
    }
    // 마지막 도시에서 출발 도시로 돌아오는 거리 추가
    total_distance += calc_distance(cities[tour.back()], cities[tour[0]]);
    cout << char('A' + tour[0]) << endl;

    cout << "Travel distance: " << total_distance << endl;
}

int main() {
    int n = 8; // 도시 수
    // A ~ H
    vector<pair<int, int>> cities = {
        {0,3}, {7,5}, {6,0}, {4,3}, {1,0}, {5,3}, {4,1}, {2,2}  
    };

    vector<Edge> tree;

    // 모든 도시 간 거리 계산 후 간선 리스트 생성
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double distance = calc_distance(cities[i], cities[j]);
            tree.push_back({i, j, distance});
        }
    }

    TSP(n, cities, tree);
}
