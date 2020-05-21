import sys

while True:
    line = sys.stdin.readline().strip()
    if not line:
        break

    max_digit_token_len = 0
    max_digit_token = []

    digit_token_len = 0
    digit_token = []

    for c in line:
        if c.isdigit():
            digit_token.append(c)
            digit_token_len += 1
        else:
            if digit_token_len > max_digit_token_len:
                max_digit_token = []
                max_digit_token.append("".join(digit_token))
                max_digit_token_len = digit_token_len
            elif digit_token_len == max_digit_token_len:
                max_digit_token.append("".join(digit_token))
                
            digit_token = []
            digit_token_len = 0

    if digit_token_len > max_digit_token_len:
        max_digit_token = []
        max_digit_token.append("".join(digit_token))
        max_digit_token_len = digit_token_len
    elif digit_token_len == max_digit_token_len:
        max_digit_token.append("".join(digit_token))
        
    digit_token = []
    digit_token_len = 0

    result = []
    result.append("".join(max_digit_token))
    result.append(str(max_digit_token_len))
    print ",".join(result)