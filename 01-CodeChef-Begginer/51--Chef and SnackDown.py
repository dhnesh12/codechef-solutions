# cook your dish here
t=int(input())
while(t):
    t-=1 
    sd=[2010, 2015, 2016, 2017,2019]
    yr=int(input())
    if(yr in sd):
        print("HOSTED")
    else:
        print("NOT HOSTED")