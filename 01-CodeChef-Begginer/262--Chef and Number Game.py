t = int(input())
while t > 0:
    t -= 1
    n = int(input())
    nums = list(map(int,input().split()))
    positive=0
    negative=0
    for num in nums:
        if num > 0:
            positive += 1
        else:
            negative += 1
    ans1 = str(positive) + ' ' + str(positive)
    ans2 = str(positive) + ' ' + str(negative)
    print(ans1 if negative == 0 else ans2)