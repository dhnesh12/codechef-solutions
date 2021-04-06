for _ in range(int(input())):
    s=input()
    count=0
    for i in range(0,len(s),2):
        if s[i]=="A" and s[i+1]=="B" or s[i]=="B" and s[i+1]=="A":
            count+=2
    if len(s)==count:
        print("yes")
    else:
        print("no")# cook your dish here
