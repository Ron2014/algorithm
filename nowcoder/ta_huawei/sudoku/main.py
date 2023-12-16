import sys

def zone_idx(i, j):
    return ((i-1)/3)*3+(j-1)/3+1

def fill_board(i, j, n):
    global board
    onum = board[i].get(j, 0)
    board[i][j] = n

    if n:
        left_row[i].discard(n)
        left_col[j].discard(n)
        left_zone[zone_idx(i, j)].discard(n)
    if onum:
        left_row[i].add(onum)
        left_col[j].add(onum)
        left_zone[zone_idx(i, j)].add(onum)

def show_board():
    # print("-----------------------")
    for i in xrange(1, 10):
        line = []
        for j in xrange(1, 10):
            line.append(str(board[i][j]))
        print(" ".join(line))

def coor2idx(i, j):
    return (i-1)*9+(j-1)

def idx2coor(idx):
    return idx/9+1, idx%9+1

def solve_board(depth):
    empty_list = []
    for i in xrange(1, 10):
        for j in xrange(1, 10):
            if board[i][j]:
                continue
            possible = set([])
            possible = possible.union(left_row[i])
            possible = possible.intersection(left_col[j])
            possible = possible.intersection(left_zone[zone_idx(i,j)])
            empty_list.append((coor2idx(i,j), possible))
    
    if empty_list:
        sorted(empty_list, key=lambda x: 80-x[0] + len(x[1])*2)
        # print(depth, empty_list)
        last_count = None
        for idx, node in empty_list:
            if last_count:
                if len(node) > last_count:
                    break
            idx, node = empty_list[0]
            i, j = idx2coor(idx)
            for n in node:
                fill_board(i, j, n)
                if solve_board(depth+1):
                    return True
            fill_board(i, j, 0)
            last_count = len(node)
    else:
        show_board()
        return True


while True:
    line = sys.stdin.readline().strip()
    if not line:
        break

    board = {}
    for i in xrange(1, 10):
        board[i] = {}
    
    left_row = {}
    for i in xrange(1, 10):
        left_row[i] = set(xrange(1,10))
    left_col = {}
    for i in xrange(1, 10):
        left_col[i] = set(xrange(1,10))
    left_zone = {}
    for i in xrange(1, 10):
        left_zone[i] = set(xrange(1,10))
    
    for i, s in enumerate(line.split()):
        fill_board(1, i+1, int(s))

    for i in xrange(2, 10):
        line = sys.stdin.readline().strip()
        for j, s in enumerate(line.split()):
            fill_board(i, j+1, int(s))

    solve_board(0)
