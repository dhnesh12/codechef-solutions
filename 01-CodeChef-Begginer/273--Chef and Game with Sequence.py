# cook your dish here
num_case=int(input())

for j in range(num_case):
    test_c=[]
    ln_case=[]
    ln_case.append(int(input()))
    test_c=map(lambda x:int(x),input().split())
    even=0
    odd=0
    for i in test_c:
        if i%2==0:
            even=even+1
        else:
            odd=odd+1
    if even==0 and odd==1:
        print(1)
    elif odd%2==1:
        print(2)
    else:
        print(1)