import sys


def is_palindrome(n, base):
    limite_izquierdo = n//base
    limite_derecho = n - base * limite_izquierdo
    if limite_derecho == 0:
        return 0
    cota = limite_izquierdo//base

    while cota > limite_derecho:
        limite_derecho = base * (limite_derecho - cota) + limite_izquierdo
        limite_izquierdo = cota
        cota = limite_izquierdo//base
    if limite_izquierdo == limite_derecho or cota == limite_derecho:
        return True
    return False


def looking_glass_house(n):
    base = 2
    if n == 1 or n == 3:
        return 2
    if n == 2 or n == 4:
        return 3

    while base*base <= n:
        if is_palindrome(n, base):
            return base
        base += 1
    base -= 1
    cota = n//base
    while cota == base + 1 or cota * base != n:
        base -= 1
        cota = n//base
    return cota - 1


entradas = int(sys.stdin.readline())
for line in sys.stdin:
    numero = int(line)
    print(looking_glass_house(numero))