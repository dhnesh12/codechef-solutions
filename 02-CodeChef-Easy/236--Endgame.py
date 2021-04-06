def mcal(d,h):
    mi=min(d,h)
    ma=max(d,h)
    diff=ma-mi
    if mi<diff:
        if mi!=0:return 1+mcal(2*mi,ma)
        else:return -1
    if ma==mi:return ma
    else:return int(ma+1)
    
    
def main():
    t=int(input())
    ix=''
    for i in range(t):ix+=input()+' '
    lx=list(map(int,ix.split()))
    D=lx[::2]
    H=lx[1::2]
    for i in range(t):print(mcal(D[i],H[i]))
main()