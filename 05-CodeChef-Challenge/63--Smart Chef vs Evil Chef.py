def mazesolve(maze, x, y, seen=None):
    seen = seen or set()
    if (x, y) in seen:return None
    seen.add((x, y))
    v = validate(maze, x, y)
    if v == END_REACHED:return ""
    elif not v:return None
    ms = (mazesolve(maze, x - 1, y, seen),
    mazesolve(maze, x + 1, y, seen),
    mazesolve(maze, x, y + 1, seen),
    mazesolve(maze, x, y - 1, seen))
    for d, r in zip(("W", "E", "S", "N"), ms):
        if r != None:
            return d + r
END_REACHED = object()
themap = {"W": (-1, 0), "E": (1, 0), "S": (0, 1), "N" : (0, -1)}
def validate(maze, x, y):
    if x < 0 or y < 0:return False
    try:
        mxy = maze[y][x]
    except IndexError:
        return False
    if mxy == "E":return END_REACHED
    if mxy == "#":return False
    return True
def execute(maze, x, y, orders):
    for order in orders:
        nx, ny = themap[order]
        nx, ny = x + nx, y + ny
        v = validate(maze, nx, ny)
        if v == END_REACHED:
            return nx, ny
        elif v:
            x = nx
            y = ny
    return x, y
t = int(input())
for _ in range(t):
    mazes = []
    numm = int(input())
    for __ in range(numm):
        ms, ___ = map(int,input().split())
        maze = []
        for index in range(ms):
            line = list(input().strip())
            if "S" in line:
                sx = line.index("S")
                sy = index
            maze.append(line)
        mazes.append((sx, sy, maze))
    orders = ""
    for x, y, maze in mazes:
        x, y = execute(maze, x, y, orders)
        orders += mazesolve(maze, x, y)
    print (orders)
