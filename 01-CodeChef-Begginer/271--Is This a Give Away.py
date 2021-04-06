# cook your dish here
test_case = int(input())
for i in range(test_case):
    start, end, num = map(int, input().split())
    if start == end:
        print(1)
    else:
        print(num)