import sys

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    line = line.replace('{', '(')
    line = line.replace('}', ')')
    line = line.replace('[', '(')
    line = line.replace(']', ')')
    print eval(line)