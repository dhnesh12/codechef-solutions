def check_matrix(M,n,m):
	for r, row in enumerate(M):
		for c, cell in enumerate(row):
			if cell == 'B':
				if M[min(n-1,r+1)][c] != 'B':
					return False
			elif cell == 'W':
				if c == 0 or c == m-1 or M[min(n-1,r+1)][c] == 'A' or M[r][c-1] == 'A':
					return False
			elif cell == 'A':
				if M[r][c-1] == 'W':
					return False
	return True		
				
for _ in range(int(input())):
	n,m = map(int,input().split())
	matrix = [input() for _ in range(n)]
	if check_matrix(matrix,n,m):
		print('yes')
	else:
		print('no')