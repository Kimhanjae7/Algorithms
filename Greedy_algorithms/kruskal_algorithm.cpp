#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

struct Edge {
    int vertex1, vertex2; // 두 정점
    int weight; // 간선의 가중치

    bool operator<(const Edge& other) const {
        return weight < other.weight; // 가중치 기준으로 정렬하기 위한 설정
    }
};

vector<int> parent; // 부모 노드를 저장 변수

// 부모 노드를 찾는 함수
int cycleCheck(int node) {
    if (parent[node] != node)
        parent[node] = cycleCheck(parent[node]); // 부모를 재귀적으로 찾기
    return parent[node];
}

vector<Edge> kruskal(int n, vector<Edge>& tree) {
    vector<Edge> mst; 

    for (int i = 0; i < n; ++i)
        parent[i] = i; // 각 노드를 자기 자신으로 초기화

    sort(tree.begin(), tree.end()); // 간선 가중치 기준으로 정렬

    for (const Edge& edge : tree) {
        int root1 = cycleCheck(edge.vertex1); // vertex1의 부모 찾기
        int root2 = cycleCheck(edge.vertex2); // vertex2의 부모 찾기

        if (root1 != root2) { // 두 노드의 부모가 다르면 (=사이클이 아니면)
            mst.push_back(edge); // MST에 간선 추가
            parent[root2] = root1; // 두 노드를 연결 (부모 노드 병합)
        }
    }

    return mst;
}

int main() {
    int n = 6; // 정점
    int m = 10; // 간선
    parent.resize(n); // 부모 배열 크기 설정
    vector<Edge> tree(m); 

    int edge_count = 1;

    cout << "◎ Enter the edges ◎\n";
    for (int i = 0; i < m; ++i) {
        char vertex1, vertex2;
        int weight;
        cout << "→  edge " << edge_count++ << ": ";
        cin >> vertex1 >> vertex2 >> weight;
        tree[i].vertex1 = vertex1 - 'a';  // 알파벳을 숫자로 변환
        tree[i].vertex2 = vertex2 - 'a';  // 알파벳을 숫자로 변환
        tree[i].weight = weight;
    }

    system_clock::time_point start = system_clock::now();

    vector<Edge> mst = kruskal(n, tree);

    system_clock::time_point end = system_clock::now();
    nanoseconds kruskal_running_time = end - start ;

    cout << "\n◎ Kruskal Minimum Spanning Tree edges:\n";
    for (const Edge& edge : mst) {
        cout << "→  (" << edge.vertex1 << ", " << edge.vertex2 << ", " << edge.weight << ")\n";
    }
    cout << "\n◎ Kruskal running time : " << kruskal_running_time.count()  << "ns \n\n";

    return 0;
}
