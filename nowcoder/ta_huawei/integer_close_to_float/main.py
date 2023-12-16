import sys

try:
    while True:
        prime_list = []
        line = sys.stdin.readline().strip()
        if line == '':
            break
        pos_dot = line.rfind('.')
        if pos_dot < 0:
            print(line)
        else:
            integer = int(line[:pos_dot])
            if pos_dot < (len(line)-1) and line[pos_dot+1] >= '5':
                integer += 1
            print(integer)
except:
    pass