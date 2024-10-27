import math
import time

# 두 점 사이의 거리 측정 함수
def distance(p1, p2):
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

# 파일의 데이터 읽은 후 배열에 삽입 함수
def points_create(filename):
    points = []
    with open(filename, 'r') as file:
        for line in file:
            x, y = map(int, line.split())
            points.append((x, y))
            # print(f"pair : {(x, y)}")
    return points

# 두 점 사이의 거리 비교 후 최소 거리 반환 함수 (점 개수가 3개 이하일 경우-분할정복 불가하기 때문)
def find_min_dist(points):
    global closest_points # 최근접 두 점을 저장할 전역변수
    min_dist = float('inf')
    points_len = len(points)
    for i in range(points_len):
        for j in range(i + 1, points_len):
            dist = distance(points[i], points[j])
            # print(f"dist: {dist} (점 {points[i]}, 점 {points[j]})")
            if (min_dist > dist):
                min_dist = dist
                closest_points = (points[i], points[j])
                # print(f"min_dist: {min_dist}")
    return min_dist

# 두 점 사이의 거리 비교 후 최소 거리 반환 함수 (중앙선 근처에서 더 가까운 두 점이 있는지 확인하는 과정)
def center_points_closest(center_points, d):
    global closest_points # 최근접 두 점을 저장할 전역변수
    min_dist = d
    center_points_len = len(center_points)

    # y좌표 기준으로 정렬된 center_points에서 가능한 점들만 비교
    center_points.sort(key=lambda p: p[1])  # y좌표 기준 정렬
    for i in range(center_points_len):
        for j in range(i + 1, center_points_len):
            if (center_points[j][1] - center_points[i][1]) < min_dist:  # 구하는 값이 min_dist이므로, 
                dist = distance(center_points[i], center_points[j])     # y좌표 차이가 d보다 작은 경우만 비교
                closest_points = (center_points[i], center_points[j])
                # print(f"center_points_dist: {dist} (점 {center_points[i]}, 점 {center_points[j]})")
                if dist < min_dist:
                    min_dist = dist
    return min_dist


def closest_pair(points_sorted_x):
    i = len(points_sorted_x)
    # 점이 3개 이하일 경우에 분할 정복이 불가능하므로 모든 거리를 비교하기 위한 함수 호출
    if (i <= 3): 
        return find_min_dist(points_sorted_x)

    mid = i // 2 # 중간 인덱스를 기준으로 분할
    mid_point = points_sorted_x[mid]

    # mid를 기준으로 분할한 배열의 최근접 점의 거리
    CP_L = closest_pair(points_sorted_x[:mid])
    CP_R = closest_pair(points_sorted_x[mid:])

    # 좌,우 배열에서 더 작은 최근접 점의 거리 설정
    d = min(CP_L, CP_R)

    # 중앙선을 기준으로 d 내에 있는 점들 중에서 가장 가까운 쌍을 구하기
    center_points = [p for p in points_sorted_x if abs(p[0] - mid_point[0]) < d]
    d_center = center_points_closest(center_points, d)

    # d와 center부분에서 구한 d 중 더 짧은 거리 반환
    return min(d, d_center)


points = points_create('input_closest_pair.txt')
points = sorted(points, key=lambda p: p[0]) # x-좌표를 기준으로 정렬
closest_points = None # 최근접 두 점의 좌표를 담을 전역 변수

# for point in points:
#    print(point)

start = time.time_ns() #시간 측정 시작
print(f"closest pair of distance: {closest_pair(points)}") # closest_pair_algorithm 시작
end = time.time_ns() #시간 측정 종료
closest_pair_time = end - start

#결과
print(f"closest pair of points: {closest_points[0]}와 {closest_points[1]}")
print(f"running time: {closest_pair_time} ns")