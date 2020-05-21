import sys
try:
    while True:
        line = sys.stdin.readline().strip()
        if line == '':
            break
        str_hex = line
        if (str_hex.startswith('0x')):
            str_hex = str_hex[2:]
        len_hex = len(str_hex)
        result = 0
        for i in xrange(len_hex):
            c = str_hex[len_hex - i - 1]
            if (c.isdigit()):
                val = int(c)
            else:
                if (c.isupper()):
                    val = ord(c) - ord('A') + 10
                elif (c.islower()):
                    val = ord(c) - ord('a') + 10
            result += val * (16 ** i)
        print(result)
except:
    pass