for _ in range(int(input())):
    s = input()
    t = input()
    ans1,ans2 = s[0],t[0]
    for i in range(1,len(s)):
        if s[i-1]!=s[i]:
            ans1+=s[i]

    for j in range(1,len(t)):
        if t[j-1]!=t[j]:
            ans2+=t[j]

    if ans1==ans2:
        print("Yes")
    else:
        print("No")