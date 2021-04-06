def calculatePi(k):
    dividend=103993
    divisor=33102
    ans = '3'
    if k ==  0:
        return ans
    else:
        ans = ans + '.'
        for i in range(k):
            dividend = dividend % divisor
            dividend = dividend * 10
            ans = ans + str((dividend//divisor))
    return ans
def main():
    for t in range(int(input())):
        k = int(input())
        print(calculatePi(k))

def test():
    for k in [0,6,20, 100]:
        print(calculatePi(k))

if __name__ == '__main__':
    main()
    # test()
