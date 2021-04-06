for i in range(int(input())):
    s=input()
    c=0
    for i in range(1,len(s)):
        if s[i]!=s[i-1]:
            c=c+1
    if c>2:
        print("non-uniform")
    else:
        print("uniform")