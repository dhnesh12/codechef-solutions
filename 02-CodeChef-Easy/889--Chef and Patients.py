for _ in range(int(input())):
    n = int(input())
    
    a = list(map(int,input().split(' ')))
    b = a.copy()
    
    b.sort(reverse = True)
    
    pos = {}
    count = {}
    
    for i in range(n):
        if b[i] in count.keys():
            count[b[i]] += 1
        else:
            count[b[i]] = 1
        pos[b[i]] = i+1
    for i in range(n):
        print(pos[a[i]] - count[a[i]] + 1,end=' ')
        count[a[i]] -= 1