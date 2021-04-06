# cook your dish here
t = int(input())
for _ in range(t):
    n = int(input())
    count = 0
    for _ in range(n):
        (s,j) = map(int, input().split(' '))
        difference = j-s
        if difference > 5:
            count +=1
    print(count)