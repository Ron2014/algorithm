import sys

def encrypt(str_input):
    newline = []
    for c in str_input:
        if c.isalpha():
            if c.islower():
                nc = chr((ord(c) - ord('a') + 1) % 26 + ord('a')).upper()
            else:
                nc = chr((ord(c) - ord('A') + 1) % 26 + ord('A')).lower()
        elif c.isdigit():
            nc = str((int(c) + 1) % 10)
        else:
            nc = c
        newline.append(nc)
    print "".join(newline)

def decrypt(str_input):
    newline = []
    for c in str_input:
        if c.isalpha():
            if c.islower():
                nc = chr((ord(c) - ord('a') + 25) % 26 + ord('a')).upper()
            else:
                nc = chr((ord(c) - ord('A') + 25) % 26 + ord('A')).lower()
        elif c.isdigit():
            nc = str((int(c) + 9) % 10)
        else:
            nc = c
        newline.append(nc)
    print "".join(newline)

is_encrypt = True

try:
    while True:
        line = sys.stdin.readline().strip()
        if line == "":
            break

        if is_encrypt:
            encrypt(line)
        else:
            decrypt(line)
        
        is_encrypt = not is_encrypt

except:
    pass