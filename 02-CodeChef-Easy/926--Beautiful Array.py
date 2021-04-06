for rep in range(int(input())):
    n = int(input());    a = list(map(int,input().split()));    d = {0:0,1:0,2:0,3:0};count = 0
    for i in range(n):        d[a[i] % 4] += 1    
    if (d[1]+ d[2] * 2 + d[3] * 3) % 4 == 0:
        count += d[2] // 2;   d[2] = d[2] % 2;   temp = min(d[1],d[3]);  count += temp;    d[1] -= temp;   d[3] -= temp
        if d[1]>0:        count += (d[1] // 4)*3;        d[1] = d[1] % 4;        count += d[1]
        elif d[3]>0:      count += (d[3] // 4)*3;    d[3] = d[3] % 4;     count += d[3]
        print(count)
    else:        print(-1)