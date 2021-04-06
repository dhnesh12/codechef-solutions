for _ in range(int(input())):
    n,m = map(int,input().split())
    alice = set(map(int,input().split()))
    berta = set(map(int,input().split()))
    count = 0
    for a in alice:
        if a in berta:
            count+=1
    
    print(count)