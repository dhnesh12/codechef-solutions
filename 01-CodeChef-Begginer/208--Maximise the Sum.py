# cook your dish here
for _ in range(int(input())):
    n = int(input())
    num = list(map(int, input().split()))
    s = 0
    num.sort()
    for i in range(len(num) // 2):
        s += abs(num[i]-num[len(num)-i-1])
    print(s)
