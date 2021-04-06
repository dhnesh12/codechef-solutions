# cook your dish here
for _ in range(int(input())):
    n = int(input())
    ele = list(map(int, input().split()))
    res = []
    for i in range(n):
        if ele[i] == 1:
            res.append(ele[i])
        elif len(res) != 0 and ele[i] == 0:
            res.pop(ele[i])
        else:
            print('Invalid')
            break
    else:
        print('Valid')
