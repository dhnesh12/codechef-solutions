for _ in range(int(input())):
    n,m = list(map(int,input().split()))
    deg = [0]*n
    for i in range(m):
        u,v = list(map(int,input().split()))
        deg[u-1]+=1
        deg[v-1]+=1
    #Even Edges
    if m%2==0:
        print(1)
        ans = [1]*n
        print(*ans)
    #Odd Edges
    else:
        ans = [1]*n
        flag = -1
        for i in range(len(deg)):
            if deg[i]%2!=0:
                flag = i
                break
        if flag!=-1:
            print(2)
            ans[flag] = 2
            print(*ans)
        else:
            print(3)
            ans[u-1] = 2
            ans[v-1] = 3
            print(*ans)