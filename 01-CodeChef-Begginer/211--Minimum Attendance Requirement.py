# cook your dish here
for _ in range(int(input())):
    n = int(input())
    att = input()
    if att.count('1')+120-n>=90:print('YES')
    else:
        print('NO')
