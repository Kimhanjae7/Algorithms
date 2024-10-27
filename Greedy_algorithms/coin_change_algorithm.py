# def coin_change(coin):
#     global n500,n100,n50,n10,n1
#     while(coin >= 500):
#         coin -= 500
#         n500 += 1
#     while(coin >= 100):
#         coin -= 100
#         n100 += 1
#     while(coin >= 50):
#         coin -= 50
#         n50 += 1
#     while(coin >= 10):
#         coin -= 10
#         n10 += 1
#     while(coin >= 1):
#         coin -= 1
#         n1 += 1
#     return n500+n100+n50+n10+n1    

# n500 = n100 = n50 = n10 = n1 = 0
# change = int(input("Enter a change: "))
# coin_sum = coin_change(change)
# print(f"minimum number of coins: {coin_sum}")
# print(f"{change} Won - 500 Won: {n500}, 100 Won: {n100}, 50 Won: {n50}, 10 Won: {n10}")
    
def coin_change(money):
    coins = [500, 100, 50, 10]

    # 금액과 개수를 딕셔너리로 구현
    coin_count = {
        500:0,
        100:0,
        50:0,
        10:0
    }

    # 금액별 최대 개수를 딕셔너리에 저장
    for coin in coins:
        coin_count[coin] += money // coin
        money -= coin_count[coin] * coin
    return coin_count

min_coin_sum = 0
money = int(input("Enter a change: "))
coin_result = coin_change(money)
print(f"{money} Won - ", end="")

# enumerate를 이용해 index를 부여함으로써 단순히 마지막 인덱스에는 ,를 생략하기 위함(깔끔하게 보이게)
for i,(coin, count) in enumerate(coin_result.items()):
    if i < 3:
        min_coin_sum += count
        print(f"{coin} Won: {count}, ", end="")
    else:
        min_coin_sum += count
        print(f"{coin} Won: {count}")
        
# 최소 코인 개수 출력
print(f"minimum number of coins: {min_coin_sum}")