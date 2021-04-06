# cook your code here
import sys
for _ in range(int(input())):
    n,k,e,m=list(map(int,sys.stdin.readline().split()))
    e_list=[]
    for i in range(n-1):
        l=list(map(int,sys.stdin.readline().split()))
        e_list.append(sum(l))
    e_list.sort()
    e_list.reverse()
    l=list(map(int,sys.stdin.readline().split()))
    s_marks=sum(l)
    if s_marks>e_list[k-1]:
        print(0)
    elif s_marks<=e_list[k-1] and (e_list[k-1]-s_marks+1)<=m:
        print(e_list[k-1]-s_marks+1)
    else:
        print("Impossible")