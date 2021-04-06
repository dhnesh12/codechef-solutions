T = int(input())
ans = []

for _ in range(T):
    N = int(input())
    A = [int(i) for i in input().split()]

    A.sort()
    deleted = [False for i in range(N)]
    count_min = 0
    i = 1
    while(i<N-1):
        if(A[i-1]+1==A[i] and A[i]+1==A[i+1]):
            count_min += 1
            deleted[i-1] = True
            deleted[i] = True
            deleted[i+1] = True
            i += 3
        else:
            i += 1
    i = 0
    while(i<N):
        if(not deleted[i]):
            count_min += 1
            if(i<N-1 and A[i]+1==A[i+1] and deleted[i+1]==False):
                i += 2
            else:
                i += 1
        else:
            i += 1
    # print(count_min)
    count_max = 0
    i = 0
    while(i<N):
        count_max += 1
        if(i<N-1 and A[i]+1==A[i+1]):
            i += 2
        else:
            i += 1
    ans.append('{} {}'.format(count_min,count_max))

for i in ans:
    print(i)