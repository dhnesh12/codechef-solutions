from bisect import *
from math import *

def main():
    chefnb = int(input())

    chefList = list()
    diff = 0

    for i in range(chefnb):
        inp = input()

        age, val = inp.split(" ")
        chef = int(age), int(val)

        index = bisect(chefList, chef)
        chefList.insert(index, chef)

        mid = ceil(len(chefList) / 2.0)

        if index < mid:
            diff -= int(val)
            
            if len(chefList) % 2 == 0:
                diff += chefList[mid][1]*2
        else:
            diff += int(val)
            
            if len(chefList) % 2 == 1:
                diff -= chefList[mid-1][1]*2
            
        print(abs(diff))

main()