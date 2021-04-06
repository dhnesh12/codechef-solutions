def main(n, k):
    customers = {}
    allowed = []

    for i in range(n):
        s, f, p = tuple(map(int, input().split()))
        customers.setdefault(p, []).append((s, f))

    for p in customers:
        interested = sorted(customers[p], key=lambda x: x[1])

        allowed.append(interested[0])

        for i in range(1, len(interested)):
            prev = allowed[-1]
            curr = interested[i]

            if curr[0] >= prev[1]:
                allowed.append(curr)

    return len(allowed)


if __name__ == "__main__":
    t = int(input())

    for _ in range(t):
        n, k = map(int, input().split())
        print(main(n, k))
