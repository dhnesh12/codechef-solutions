# cook your dish here
T = int(input())
for _ in range(T):
    A, B = map(int, input().split())

    round_ = 1
    while 1 > 0:
        if round_ % 2 != 0:
            if A >= round_:
                A -= round_
            else:
                print('Bob')
                break
        else:
            if B >= round_:
                B -= round_
            else:
                print('Limak')
                break
        round_ += 1