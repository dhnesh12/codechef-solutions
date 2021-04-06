# cook your dish here
test_case = int(input())
for i in range(test_case):
    n,k=[int(x)for x in input().rstrip().split()]
    a=[int(x)for x in input().rstrip().split()]
    count=0
    for i in a:
        if i>1:
            count+=1
    if count<=k:
        print("YES")
    else:
        print("NO")