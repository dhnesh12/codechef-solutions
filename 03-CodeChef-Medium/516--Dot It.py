import math
from sys import stdin, stdout
import random
import array as arr
import numpy as np
from sys import stdin, stdout
from collections import OrderedDict 
from collections import defaultdict
from collections import deque
import heapq as hq


def get_input(): return list(map(int,stdin.readline().strip().split()))
def single_input(): return (int)(input())
def simple_input(): return input()



def solve():
    n,q=get_input()
    a=np.array(get_input());a=np.insert(a,0,0)
    b=np.array(get_input());b=np.insert(b,0,0)
    
    for i in range(q):
        x,y,l=get_input()
        print(np.dot(a[x:x+l],b[y:y+l]))
    

def main():
    temp=get_input()
    t=temp[0]
    for i in range(t):
        solve()
    

if __name__ == "__main__":
    main()