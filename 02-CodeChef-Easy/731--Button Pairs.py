# cook your dish here
for t in range(int(input())):
    n=int(input())
    a=[int(x)for x in input().rstrip().split()]
    count=0 
    for i in a:
        if i%2==0:
            count+=1 
    s=n-count
    print(s*count)