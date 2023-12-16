import sys

def showScreen(screen, idx, cursor):
    return
    print("------ %d" % (cursor))
    for i,v in enumerate(screen):
        if i==idx:
            print("%d%s" % (v, "<------"))
        else:
            print(v)
    print("------")

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    lines = line.split()
    count = int(lines[0])

    if len(lines) > 1:
        commands = lines[1]
    else:
        commands = sys.stdin.readline().strip()
    
    cap = 4

    screen = []
    for i in xrange(1,count+1):
        if i>cap:
            break
        screen.append(i)
    cursor = 1
    idx = 0

    showScreen(screen, idx, cursor)
    if count > cap:
        for c in commands:
            if c=="D":
                cursor += 1
                idx += 1

                if cursor>count:
                    ## rewind
                    cursor = 1
                    idx = 0
                    screen = [1, 2, 3, 4]

                elif idx>=cap:
                    ## page down
                    screen = [screen[0]+1, screen[1]+1, screen[2]+1, screen[3]+1]
                    idx = cap -1

            elif c=="U":
                cursor -= 1
                idx -= 1

                if cursor==0:
                    ## roll back
                    cursor = count
                    idx = cap-1
                    screen = [count-3, count-2, count-1, count]

                elif idx<0:
                    ## page up
                    screen = [screen[0]-1, screen[1]-1, screen[2]-1, screen[3]-1]
                    idx = 0
            showScreen(screen, idx, cursor)
    else:
        for c in commands:
            if c=="D":
                cursor = cursor+1
                idx += 1
            elif c=="U":
                cursor = cursor-1
                idx -= 1
            if idx<0:
                cursor += count
                idx += count
            elif idx>=count:
                cursor -= count
                idx -= count
            showScreen(screen, idx, cursor)
    
    print(" ".join(map(str, screen)))
    print(cursor)
