import sys

def solve(n,k):

	arr = []
	prefix = []

	for i in range(1, n+1):
		if i % 2:
			arr.append(i)
		else:
			arr.append(-i)

	k_count = n//2 + (n%2)

	diff = abs(k - k_count)
	if k < k_count:
		for i in range(n-1, -1, -1):
			if diff == 0:
				break
			if arr[i] > 0:
				arr[i] *= -1
				diff -= 1
	elif k > k_count:
		for i in range(n-1, -1, -1):
			if diff == 0:
				break
			if arr[i] < 0:
				arr[i] *= -1
				diff -= 1

	print(*arr, sep=" ")





if 1 == 2:
    sys.stdin = open('input.txt', 'r')
    sys.stdout = open('output.txt', 'w')
else:
	input = sys.stdin.readline

T = int(input())
for _ in range(T):
	n,k = list(map(int, input().split()))
	solve(n,k)