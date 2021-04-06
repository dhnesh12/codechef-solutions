for i in range(int(input())):
    s=list(input())
    c=0
    for i in s:
        if s.count(i)>1:
            c=c+1
    if c>=2:
        print("yes")
    else:
        print('no')