t=input()
t=int(t)
while t!=0 :
    inp=input().split(" ")
    inp=[int(x) for x in inp]
    p=-1
    c=0
    val=input().split(" ")
    val=[int(x) for x in val]
    for i in val :
        if p==-1 :
            p=int(i/inp[1])
            c+=1
        else :
            if int(i/inp[1])!=p :
                c+=1
        p=int(i/inp[1])
    print(c)
    t-=1