# cook your dish here
for i in range(int(input())):
    (n,m,k) = map(int,input().split(' '))
    l1=list(map(int,input().split(' ')))
    l2=list(map(int,input().split(' ')))
    c=0
    v=0
    for i in l1:
        if i in l2:
            c+=1
    for i in range(1,n+1):
        if i not in l1 and i not in l2:
            v+=1
    
    print(c, v)