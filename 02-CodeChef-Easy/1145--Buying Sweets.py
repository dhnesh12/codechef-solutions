T = int(input())
for _ in range(T):
    n, x = map(int, input().split())
    arr = [x for x in map(int, input().split())]
    sum_n = sum(arr)
    count = 0
    for i in arr:
        temp = sum_n
        temp -= i
        if temp//x != sum_n//x:
            count += 1
            # print(sum_n//x)
            # break
    if count == len(arr):
        print(sum_n//x)
    else:
        print(-1)
