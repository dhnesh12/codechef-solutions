obj = { 0 : 0, 1 : 1}
def coin_exchange_sum(coin):
    coin_sum = coin//2 + coin//3 + coin//4
    if coin in obj:
        return obj[coin]
    elif coin > coin_sum:
        obj[coin] = coin
    else:
        obj[coin] = coin_exchange_sum(coin//2) \
                            + coin_exchange_sum(coin//3) \
                            + coin_exchange_sum(coin//4)
    return obj[coin]
    
for test in range(10):
    try:
        coin = int(input())
        print(coin_exchange_sum(coin))
    except EOFError as e:
        break
