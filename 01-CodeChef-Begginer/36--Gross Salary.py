t=int(input())
for i in range(t):
    bs=int(input())
    if(bs<1500):
        hra=0.1*bs
        da=0.9*bs
        gs=bs+hra+da
        print(gs)
    elif(bs>=1500):
        hra=500
        da=0.98*bs
        gs=bs+hra+da
        print(gs)# cook your dish here
