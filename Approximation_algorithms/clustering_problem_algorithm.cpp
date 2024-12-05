#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

// 좌표 구조체
struct Point {
    int x, y;

    // 중복 제거용 정렬 기준 정의
    bool operator<(const Point& other) const {
        return (x < other.x) || (x == other.x && y < other.y);
    }

    // 비교를 위한 정의
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// 거리 계산
double calc_distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Clustering Problem Algorithm
vector<vector<Point>> approx_k_clusters(const vector<Point>& points, int k, vector<Point>& centers) {
    vector<vector<Point>> clusters(k); // 각 클러스터에 속한 점들

    // 각 점이 가장 가까운 센터까지의 거리를 저장하는 벡터 -> 초기값 무한대
    vector<double> distances(points.size(), INT_MAX);

    centers.push_back(points[0]); // 초기 센터는 input file의 1번째 좌표

    // 새로운 센터 결정
    for (int j = 1; j < k; ++j) {
        int most_distance_idx = -1; // 가장 멀리 떨어진 점의 인덱스 저장 변수
        double max_distance = -1; // 현재 계산된 최대 거리 저장 변수

        // 모든 점에 대해서 반복
        for (size_t i = 0; i < points.size(); ++i) {
            if (find(centers.begin(), centers.end(), points[i]) != centers.end()) {
                continue; // 이미 센터로 선택된 점은 건너뛰기
            }

            // 현재 점과 가장 가까운 센터까지의 거리를 계산하여 업데이트
            double current_distance = calc_distance(points[i], centers.back());
            distances[i] = min(distances[i], current_distance);

            // 가장 멀리 있는 점을 새로운 센터 후보로 저장
            if (distances[i] > max_distance) {
                max_distance = distances[i];
                most_distance_idx = i;
            }
        }

        // 가장 멀리 있는 점을 새로운 센터로 추가
        centers.push_back(points[most_distance_idx]);
    }

    // 각 점을 가장 가까운 센터로 클러스터링
    for (const auto& point : points) {
        int nearest_center_idx = -1; // 현재 점에서 가장 가까운 센터 인덱스 저장 변수
        double min_distance = INT_MAX; // 가장 가까운 거리를 찾기위해 최대값 초기화

        // 모든 센터 탐색하며 최소 거리 센터 찾기
        for (size_t i = 0; i < centers.size(); ++i) {
            double distance = calc_distance(point, centers[i]);
            if (distance < min_distance) {
                min_distance = distance;
                nearest_center_idx = i;
            }
        }
        // 현재 점을 가장 가까운 센터 클러스터에 삽입
        clusters[nearest_center_idx].push_back(point);
    }

    return clusters;
}

int main() {
    ifstream input_file("clustering_input.txt");
    vector<Point> points;

    if (!input_file) {
        cerr << "file error" << endl;
        return 1;
    }

    int x, y;
    while (input_file >> x >> y) {
        Point new_point = {x, y};

        // 중복 제거를 위해 현재 점이 벡터에 없는지 확인
        if (find(points.begin(), points.end(), new_point) == points.end()) {
            points.push_back(new_point);
        }
    }

    int k = 8;
    vector<Point> centers;
    vector<vector<Point>> clusters = approx_k_clusters(points, k, centers);

    for (size_t i = 0; i < clusters.size(); ++i) {
        cout << "Cluster " << i + 1 << ": ";
        for (const auto& point : clusters[i]) {
            cout << "(" << point.x << ", " << point.y << ") ";
        }
        cout << endl;
        cout << "Cluster " << i + 1 << " Center point: (" << centers[i].x << ", " << centers[i].y << ")" << endl;
        cout << endl;
    }
}
