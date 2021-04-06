# cook your dish here

T = int(input())
for _ in range(T):
    n = int(input())
    d = [int(x) for x in input().split()]

    d_set = []
    for i in range(n):
        if d[i] not in d_set:
            d_set.append(d[i])
    print(len(d_set))