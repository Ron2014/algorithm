import sys

COMMANDS = {
    "reset" : "reset what",
    "reset board" : "board fault",
    "board add" : "where to add",
    "board delet" : "no board at all",
    "reboot backplane" : "impossible",
    "backplane abort" : "install first",
}

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break
    lines = line.split()
    count = len(lines)

    matches = []
    for k, v in COMMANDS.iteritems():
        keys = k.split()
        if len(keys) == count:
            matched = True
            for i, s in enumerate(lines):
                if not keys[i].startswith(s):
                    matched = False
                    break
            if matched:
                matches.append(v)

    # print(matches)
    if len(matches) == 1:
        print(matches[0])
    else:
        print("unkown command")