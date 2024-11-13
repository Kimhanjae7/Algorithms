import pandas as pd

def knapsack(C, weights, values, n):
    # 초기화
    K = [[0 for _ in range(C + 1)] for _ in range(n + 1)]
    for i in range(n + 1):
        K[i][0] = 0  # 배낭 용량이 0일 때

    for w in range(C + 1):
        K[0][w] = 0  # 물건이 없을 때

    for i in range(1, n + 1):
        for w in range(1, C + 1):
            if weights[i - 1] > w:
                # 물건 ｉ의 무게가 현재 용량을 초과하는 경우, 포함하지 않음
                K[i][w] = K[i - 1][w]
            else:
                # 물건 ｉ를 배낭에 담지 않을 경우 고려하여 최대값 선택
                K[i][w] = max(K[i - 1][w], K[i - 1][w - weights[i - 1]] + values[i - 1])

    # DataFrame으로 테이블 형식 출력
    df = pd.DataFrame(K[1:], index=[f"Item {i}" for i in range(1, n + 1)], columns=[f"W={w}" for w in range(C + 1)])
    print(df)

    return K[n][C]

C = 10  # 배낭의 최대 용량
weights = [5, 4, 6, 3]  # 물건들의 무게
values = [10, 40, 30, 50]  # 물건들의 가치
n = len(weights)

knapsack(C, weights, values, n)
