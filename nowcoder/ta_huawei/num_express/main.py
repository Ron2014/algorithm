import sys
while True:
    line = sys.stdin.readline().strip()
    if not line:
        break

    result = []
    digit_token = []
    for c in line:
        if c.isdigit():
            digit_token.append(c)
        else:
            if digit_token:
                result.append("*")
                result.extend(digit_token)
                result.append("*")
                digit_token = []
            result.append(c)

    if digit_token:
        result.append("*")
        result.extend(digit_token)
        result.append("*")
        digit_token = []
    
    print "".join(result)
        