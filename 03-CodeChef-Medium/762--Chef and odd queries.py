import math,sys
#from itertools import permutations, combinations;import heapq,random;
from collections import defaultdict,deque
import bisect as bi
def yes():print('YES')
def no():print('NO')
#sys.stdin=open('input.txt','r');sys.stdout=open('output.txt','w');
def I():return (int(sys.stdin.readline()))
def In():return(map(int,sys.stdin.readline().split()))
def Sn():return sys.stdin.readline().strip()
#sys.setrecursionlimit(1500)
def dict(a):
    d={} 
    for x in a:
        if d.get(x,-1)!=-1:
            d[x]+=1
        else:
            d[x]=1
    return d
def find_gt(a, x):
    'Find leftmost value greater than x'
    i = bi.bisect_left(a, x)
    if i != len(a):
        return i
    else:            
        return -1
def update(l,r,arr,i):
    while l<r and l%buksz!=0 and l!=0:
        arr[l].add(i)
        l+=1
    while l+buksz<r:
        block[l//buksz].add(i)
        l+=buksz

    while l<=r:
        arr[l].add(i)
        l+=1

def main():
    try:
        global block ,buksz,N
        n=I()
        N=(2*10**5)
        buksz=int(math.sqrt(N))
        block=[set() for i in range(buksz+2)]
        arr=[set() for i in range(N+1)]
        for i in range(n):
            a,b=In()
            update(a,b,arr,i)
        nQ=I()
        for x in range(nQ):
            Q=list(In())
            d={}
            for i in range(Q[0]):
                for y in arr[Q[i+1]]:
                    if d.get(y,-1)!=-1:
                        d[y]+=1
                    else:
                        d[y]=1
                for y in block[(Q[i+1]//buksz)]:
                    if d.get(y,-1)!=-1:
                        d[y]+=1
                    else:
                        d[y]=1
            cnt=0
            for i in d.values():
                if i&1:
                    cnt+=1
            print(cnt)
    except:
        pass
        
M = 998244353
P = 1000000007
 
if __name__ == '__main__':
    for _ in range(I()):main()
    # for _ in range(1):main()
#End#

#        ******************* All The Best *******************   #